#include "EditorUI_Utils.h"
#include "Panel_Hierarchy.h"
#include "StaticProp.h"

void CPanel_Hierarchy::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        // ---------- 목록 (이름만) ----------
        auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
        if (nullptr != pObjects)
        {
            for (auto& [strTag, pObject] : *pObjects)
            {
                if (nullptr == pObject || pObject->Is_Dead())
                    continue;
                if (ImGui::Selectable(To_UTF8(strTag).c_str(), strTag == m_Context.strSelectedTag))
                    m_Context.Select(strTag, pObject);

                // 항목 우클릭 메뉴
                if (ImGui::BeginPopupContextItem())          // 바로 앞 Selectable 전용
                {
                    // 우클릭한 항목을 선택 상태로
                    m_Context.Select(strTag, pObject);

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
        if (ImGui::IsWindowFocused() && ImGui::IsKeyPressed(ImGuiKey_Delete))
            Delete_Selected();

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
    }
    ImGui::End();
}

void CPanel_Hierarchy::Create_Object(const wchar_t* pPrototypeTag)
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
