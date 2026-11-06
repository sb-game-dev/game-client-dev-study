#include "EditorUI_Utils.h"
#include "Panel_Scene.h"
#include "Camera.h"
#include "Hill.h"

namespace
{
    struct GIZMO_OP_ITEM
    {
        const char* pLabel;         // 글자
        ImGuizmo::OPERATION eOp;    // 바뀔 모드
    };

    static constexpr GIZMO_OP_ITEM g_GizmoOps[] =
    {
        { "Move",   ImGuizmo::TRANSLATE },
        { "Rotate", ImGuizmo::ROTATE    },
        { "Scale",  ImGuizmo::SCALE     },
    };
}

void CPanel_Scene::Render(const PANEL_RECT& tRect)
{
    // 창의 크기와 위치 지정
    Set_NextPanelRect(tRect);

    // 창 옵션
    constexpr ImGuiWindowFlags eSceneFlags = g_FixedPanelFlags
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse;

    // 스타일 스택 호출 -> 여백 없애기
    // 매개변수 1 -> ImGuiStyleVar idx : 바꿀 스타일 항목
    // ImGuiStyleVar_WindowPadding : 창 테두리와 그 안의 내용 사이 안쪽 여백을 바꾸겠다 (기본값은 8,8)
    // 매개변수 2 -> val : 새로운 값
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

    // 스타일 스택이 호출된 창 열기
    // 두 번째 매개변수를 nullptr로 받아서 X 버튼을 생성하지 않는다.
    ImGui::Begin("Scene", nullptr, eSceneFlags);

    // 스타일 스택 복구
    ImGui::PopStyleVar();
    
    // 씬 텍스처의 가로세로 비율
    float2_t vpSize = CGameInstance::Get().Get_ViewportSize();
    const f32_t fAspect = static_cast<f32_t>(vpSize.x) / vpSize.y;

    ImVec2 vSize = { tRect.fW,tRect.fH };
    vSize.y = tRect.fW / fAspect;

    // 가운데 정렬
    // ImGui의 "커서"
    // 위젯을 커서 위치에 놓고, 놓을 때마다 커서를 다음 줄로 옮긴다.

    // 커서의 위치를 설정한다.
    // 왼쪽 위에서 y좌표만 아래로 내린다.
    const ImVec2 vCursor = ImVec2(0, (tRect.fH - vSize.y) * 0.5f);
    ImGui::SetCursorPos(vCursor);

    // 씬 텍스처 그리기
    // Renderer의 SRV를 가져와서 그린다
    ID3D11ShaderResourceView* pSRV = CGameInstance::Get().Get_SceneSRV();

    // (ImTextureID)pSRV -> 포인터를 ImGui의 텍스처 ID로 바꿔 담는다.
    // DX11 백엔드가 그릴 때 다시 ID3D11ShaderResourceView로 되돌려서 PS 0번 슬롯에 바인딩함.
    // vSize -> 화면에 그릴 크기
    // 실제로 그리는 것이 아닌 그리기 명령만 기록한다.
    // Image도 하나의 아이템으로 등록된다.
    ImGui::Image((ImTextureID)pSRV, vSize);

    // 나중에 쓸 정보 저장
    // Item 함수들은 바로 앞 아이템에대한 값을 준다. (다른 위젯을 넣으면 안됨)
    m_Context.vImageMin     = float2_t(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y);  // 화면 기준 좌상단 좌표
    m_Context.vImageSize    = float2_t(vSize.x, vSize.y);   // 씬 화면 크기 -> 피킹에서 NDC로 바꿀 때 나누는 값
    m_Context.bSceneHovered = ImGui::IsItemHovered();       // 카메라 드래그 + 카메라 피킹에 사용
    m_Context.bSceneFocused = ImGui::IsWindowFocused();     // 마지막으로 클릭된 창일 때 true 카메라 조작 허용
                                                            // (Begin과 End 사이에서 불려야 이 창에 대한 값이 나옴)
    // 카메라 -> 원근투영
    ImGuizmo::SetOrthographic(false);
    
    // Scene에 기즈모를 그리게 한다.
    ImGuizmo::SetDrawlist();

    // 기즈모가 뷰포트로 생각할 화면 -> Scene의 Rect
    ImGuizmo::SetRect(m_Context.vImageMin.x, m_Context.vImageMin.y,
        m_Context.vImageSize.x, m_Context.vImageSize.y);

    ImGui::SetCursorPos(vCursor);
    ImGui::BeginGroup();
    for (size_t i = 0; i < 3; ++i)
    {
        if (0 != i)
            ImGui::SameLine();
        // 현재 그려야 하는 버튼이 선택된 기즈모 방식인지 확인 -> 스타일 변경 후 그리기
        const bool_t bActive = (m_eGizmoOp == g_GizmoOps[i].eOp);
        if (bActive)
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
        
        // 버튼 그리기
        if (ImGui::Button(g_GizmoOps[i].pLabel))
            m_eGizmoOp = g_GizmoOps[i].eOp;
        // 스타일 복구
        if (bActive)
            ImGui::PopStyleColor();
    }
    ImGui::EndGroup();

    auto pObject = m_Context.pSelected.lock();
    if (nullptr != pObject && !dynamic_pointer_cast<CHill>(pObject))
    {
        float4x4_t ViewMatrix, ProjMatrix, WorldMatrix;
        XMStoreFloat4x4(&ViewMatrix, CGameInstance::Get().Get_Perspective_Transform(D3DTS::VIEW));
        XMStoreFloat4x4(&ProjMatrix, CGameInstance::Get().Get_Perspective_Transform(D3DTS::PROJ));
        WorldMatrix = *pObject->Get_Transform()->Get_WorldMatrixPtr();

        if (ImGuizmo::Manipulate(&ViewMatrix._11, &ProjMatrix._11,
            m_eGizmoOp, ImGuizmo::WORLD,
            &WorldMatrix._11))
        {
            vector_t vS, vQ, vT;
            if (XMMatrixDecompose(&vS, &vQ, &vT, XMLoadFloat4x4(&WorldMatrix)))
            {
                float3_t vPos, vScale; 
                float4_t vQuat;
                XMStoreFloat3(&vPos, vT); 
                XMStoreFloat3(&vScale, vS); 
                XMStoreFloat4(&vQuat, vQ);
                pObject->Set_Transform(vPos, vQuat, vScale);
            }
        }
    }

    // 피킹 요청: 씬 이미지 위에서 왼쪽 버튼을 누른 프레임
    if (m_Context.bSceneHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGuizmo::IsOver() && !ImGuizmo::IsUsing())
    {
        // 1. Scene 창에 그려진 이미지의 중심 (ImGui 화면 좌표)
        const float2_t vImageCenter = {
            m_Context.vImageMin.x + m_Context.vImageSize.x * 0.5f,
            m_Context.vImageMin.y + m_Context.vImageSize.y * 0.5f };

        // 2. 실제 Level 화면(뷰포트)의 크기와 중심
        const float2_t vViewportCenter = { vpSize.x * 0.5f, vpSize.y * 0.5f };

        // 3. 배율: Scene 창에서 1픽셀 움직이면 실제 Level에서는 몇 픽셀인가
        const f32_t fScaleX = vpSize.x / m_Context.vImageSize.x;
        const f32_t fScaleY = vpSize.y / m_Context.vImageSize.y;

        // 4. 마우스가 이미지 중심에서 얼마나 떨어져 있나 (맵툴 상의 변화량)
        const ImVec2 vMouse = ImGui::GetIO().MousePos;
        const f32_t fDeltaX = vMouse.x - vImageCenter.x;
        const f32_t fDeltaY = vMouse.y - vImageCenter.y;

        // 5. 실제 Level 좌표 = Level 중심 + 변화량 × 배율
        POINT ptPick{
            static_cast<LONG>(vViewportCenter.x + fDeltaX * fScaleX),
            static_cast<LONG>(vViewportCenter.y + fDeltaY * fScaleY) };

        // 6. 레이 만들기
        vector_t vRayOrigin, vRayDir;
        if (auto pCamera = CGameInstance::Get().Get_MainCamera())
            pCamera->Compute_PickingRay(ptPick, vRayOrigin, vRayDir);

        // 이 레이로 Layer_Map 객체 충돌 검사
        auto GameObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), L"Layer_Map");
        if (nullptr == GameObjects)
        {
            ImGui::End();
            return;
        }
        f32_t fMinDist = D3D11_FLOAT32_MAX;
        wstring_t               strPickedTag = {};
        shared_ptr<CGameObject> pPicked = { nullptr };
        for (auto& [strTag, pObject] : *GameObjects)
        {
            if (nullptr == pObject || pObject->Is_Dead())
                continue;
            if (nullptr != dynamic_pointer_cast<CHill>(pObject))          // 지형 제외 (박스가 맵 전체)
                continue;
            auto pModel = static_pointer_cast<CModel>(pObject->Find_Component(L"Com_Model"));
            if (nullptr == pModel)
                continue;

            BoundingOrientedBox tWorldBox;
            BoundingOrientedBox::CreateFromBoundingBox(tWorldBox, pModel->GetBoundinBox());
            tWorldBox.Transform(tWorldBox, pObject->Get_Transform()->Get_World());

            f32_t fOutDist = {};
            if (tWorldBox.Intersects(vRayOrigin, vRayDir, fOutDist) && fMinDist > fOutDist)
            {
                fMinDist = fOutDist;     
                strPickedTag = strTag;
                pPicked = pObject;
            }
        }
        if (nullptr != pPicked)
            m_Context.Select(strPickedTag, pPicked);
    }
    
    ImGui::End();
}

unique_ptr<CPanel_Scene> CPanel_Scene::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Scene>(new CPanel_Scene(Context));
}
