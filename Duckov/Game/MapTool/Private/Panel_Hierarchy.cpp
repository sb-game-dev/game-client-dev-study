#include "EditorUI_Utils.h"
#include "Panel_Hierarchy.h"
#include "StaticProp.h"

void CPanel_Hierarchy::Render(const PANEL_RECT& tRect)
{
    // 1. 창 크기 설정 밑 창 열기
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        // 항목 위가 아닌 창의 빈 곳을 우클릭했을 때만 열림
        if (ImGui::BeginPopupContextWindow("HierarchyMenu", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            for (auto& Item : s_Placeables)
            {
                if (ImGui::MenuItem(Item.pName))      // "Add Static_Prop"
                    Create_Object(Item.pPrototypeTag);
            }
            ImGui::EndPopup();
        }
        // 맵 객체목록 가져오기
        auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
        if (nullptr != pObjects)
        {
            for (auto& [strTag, pObject] : *pObjects)
            {
                if (nullptr == pObject || pObject->Is_Dead())
                    continue;

                // 객체가 살아있다면
                // Selectable -> 그리기. 이름을 한 줄로 + 두 번째 인자가 true면 하이라이트해서 그리기
                //            -> 클릭 감지: 이름에 해당하는 Rect가 좌클릭됐는지를 인식한다.
                //                          그래서 클릭한 프레임에서는 strTag == m_Context.strSelectedTag 조건이 false이고
                //                          다음 프레임 부터 true가 되어서 하이라이트가 된다.  
                //                          물론 strTag == m_Context.strSelectedTag 조건의 값과 별개로 클릭은 Selectable() 함수가 반환
                if (ImGui::Selectable(To_UTF8(strTag).c_str(), strTag == m_Context.strSelectedTag))
                    m_Context.Select(strTag, pObject);

                // 마우스 우클릭을 뗀 순간 마우스가 바로 앞 위젯 위에 있었나를 검사한다.
                // 바로 앞 Selectable 위젯 전용
                if (ImGui::BeginPopupContextItem())
                {
                    // 우클릭한 항목을 선택 상태로
                    m_Context.Select(strTag, pObject);

                    // MenuItem -> 그리기와 좌클릭을 동시에 하는 위젯 + 마우스를 올리면 하이라이트
                    if (ImGui::MenuItem("Delete", "Del"))
                        m_bRequestDelete = true;             // 루프 끝난 뒤 처리

                    ImGui::EndPopup();
                }
            }
        }
        // 우클릭 삭제
        if (m_bRequestDelete)
        {
            Delete_Selected();
            m_bRequestDelete = false;
        }
        // Delete 키 삭제
        // IsWindowFocused 함수는 지금 그리고있는 ImGui창이 포커스인가를 알려주는 함수 -> bool 반환
        if (ImGui::IsWindowFocused() && ImGui::IsKeyPressed(ImGuiKey_Delete))
            Delete_Selected();

    }
    ImGui::End();
}

void CPanel_Hierarchy::Create_Object(const wstring_t& pPrototypeTag)
{
    CStaticProp::STATICPROP_DESC Desc{};
    Desc.iLevelIndex = ETOUI(LEVEL::MAPTOOL);
    Desc.strMeshPath = g_Meshes[0].pPath;           // 기본: cube
    Desc.strTexturePath = g_Textures[0].pPath;      // 기본: 첫 텍스처
    Desc.bEditorMode = true;

    wstring_t strTag;

    do {
        if (m_iNextID < 10)
            strTag = L"Prop_0" + to_wstring(m_iNextID++);
        else
            strTag = L"Prop_" + to_wstring(m_iNextID++);
    }
    while (nullptr != CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), pPrototypeTag,
        ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag, &Desc)))
    {
        MSG_BOX("Create Failed");
        return;
    }

    // 만든 객체를 바로 선택
    m_Context.Select(strTag, CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
}

void CPanel_Hierarchy::Delete_Selected()
{
    auto pSelected = m_Context.pSelected.lock();
    if (nullptr == pSelected)
        return;

    pSelected->Set_Dead();          // 실제 erase는 엔진 Priority_Update에서
    m_Context.Clear_Selection();    // 선택은 바로 해제
}

unique_ptr<CPanel_Hierarchy> CPanel_Hierarchy::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Hierarchy>(new CPanel_Hierarchy(Context));
}
