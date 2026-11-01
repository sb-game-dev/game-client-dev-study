#include "EditorUI_Utils.h"
#include "Panel_Scene.h"

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

    // 사용할 수 있는 공간 계산
    // 현재 커서위치부터 창 오른쪽 아리까지 실제 위젯을 놓을 수 있는 공간 -> vAvail = (1040,854)
    const ImVec2 vAvail = ImGui::GetContentRegionAvail();

    // 씬 텍스처의 가로세로 비율
    float2_t vpSize = CGameInstance::Get().Get_ViewportSize();
    const f32_t fAspect = static_cast<f32_t>(vpSize.x) / vpSize.y;

    // 비율 맞추기
    ImVec2 vSize = vAvail;
    if (vAvail.x / fAspect <= vAvail.y)
        vSize.y = vAvail.x / fAspect;
    else
        vSize.x = vAvail.y * fAspect;

    // 가운데 정렬
    // ImGui의 "커서"
    // 위젯을 커서 위치에 놓고, 놓을 때마다 커서를 다음 줄로 옮긴다.

    // 커서의 위치를 설정한다.
    // 왼쪽 위에서 y좌표만 아래로 내린다.
    const ImVec2 vCursor = ImVec2(0, (vAvail.y - vSize.y) * 0.5f);
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
    ImGui::End();
}

unique_ptr<CPanel_Scene> CPanel_Scene::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Scene>(new CPanel_Scene(Context));
}
