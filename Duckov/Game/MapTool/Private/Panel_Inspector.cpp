#include "EditorUI_Utils.h"
#include "Panel_Inspector.h"
#include "StaticProp.h"

void CPanel_Inspector::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        m_Context.Validate_Selection();
        auto pSelected = m_Context.pSelected.lock();
        if (nullptr == pSelected)
            ImGui::TextDisabled("No object selected");
        else
        {
            // ---------- 이름 ----------
            ImGui::TextUnformatted(To_UTF8(m_Context.strSelectedTag).c_str());
            ImGui::Separator();

            // ---------- Transform ----------
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                float3_t vPos = pSelected->Get_Position();
                if (ImGui::DragFloat3("Position", &vPos.x, 0.1f))
                    pSelected->Set_Position(vPos);

                float3_t vRot = pSelected->Get_Rotation();
                if (ImGui::DragFloat3("Rotation", &vRot.x, 1.f))
                    pSelected->Set_Rotation(vRot);

                float3_t vScale = pSelected->Get_Scale();
                if (ImGui::DragFloat3("Scale", &vScale.x, 0.05f, 0.01f, 100.f))
                    pSelected->Set_Scale(vScale);
            }

            if (auto pProp = dynamic_pointer_cast<CStaticProp>(pSelected))
            {
                if (ImGui::CollapsingHeader("Static Prop", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    Render_AssetCombo("Mesh", g_Meshes, pProp->Get_MeshPath(),
                        [&](const wchar_t* pPath) { if (FAILED(pProp->Change_Mesh(pPath)))       MSG_BOX("Mesh Change Failed"); });
                    Render_AssetCombo("Texture", g_Textures, pProp->Get_TexturePath(),
                        [&](const wchar_t* pPath) { if (FAILED(pProp->Change_Texture(pPath))) MSG_BOX("Texture Change Failed"); });
                }
            }
        }
    }
    ImGui::End();
}

unique_ptr<CPanel_Inspector> CPanel_Inspector::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Inspector>(new CPanel_Inspector(Context));
}
