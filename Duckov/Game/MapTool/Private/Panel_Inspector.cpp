#include "EditorUI_Utils.h"
#include "Panel_Inspector.h"
#include "StaticProp.h"

void CPanel_Inspector::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        // 선택된 부분이 있는지 확인
        // 선택된 부분이 없다면 "No object selected"만 출력하고 선택된 부분이 있는 경우만 토글목록 출력
        m_Context.Validate_Selection();
        auto pSelected = m_Context.pSelected.lock();
        if (nullptr == pSelected)
            ImGui::TextDisabled("No object selected");
        else
        {
            // 이름
            ImGui::TextUnformatted(To_UTF8(m_Context.strSelectedTag).c_str());
            ImGui::Separator();

            // Transform
            // CollapsingHeader: 토글창 생성
            // 반환값 : 펼쳐져 있으면 true -> 펼쳐져 있을 때만 아래 위젯을 그린다.
            // 첫 번째 매개변수는 label
            // 두 번째 매개변수는 flag -> 기본값으로 펼쳐진 것을 사용한다.
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                float3_t vPos = pSelected->Get_Position();
                if (ImGui::DragFloat3("Position", &vPos.x, 0.1f))
                    pSelected->Set_Position(vPos);

                float3_t vRot = pSelected->Get_EulerHint();
                if (ImGui::DragFloat3("Rotation", &vRot.x, 1.f))
                    pSelected->Set_RotationEuler(vRot);

                float3_t vScale = pSelected->Get_Scale();
                if (ImGui::DragFloat3("Scale", &vScale.x, 0.05f, 0.01f, 100.f))
                    pSelected->Set_Scale(vScale);
            }

            if (auto pProp = dynamic_pointer_cast<CStaticProp>(pSelected))
            {
                if (ImGui::CollapsingHeader("Static Prop", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (auto pPath = Render_AssetCombo("Mesh", g_Meshes, _countof(g_Meshes), pProp->Get_MeshPath()))
                    {
                        if (FAILED(pProp->Change_Mesh(pPath)))
                            MSG_BOX("Mesh Change Failed");
                    }

                    if (auto pPath = Render_AssetCombo("Texture", g_Textures, _countof(g_Textures), pProp->Get_TexturePath()))
                    {
                        if (FAILED(pProp->Change_Texture(pPath)))
                            MSG_BOX("Texture Change Failed");
                    }
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
