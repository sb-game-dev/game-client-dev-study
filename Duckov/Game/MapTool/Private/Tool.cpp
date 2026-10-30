#include "imgui.h"
#include "Tool.h"
namespace
{
    constexpr ImGuiWindowFlags g_FixedPanelFlags =
        ImGuiWindowFlags_NoMove                 // 제목 표시줄을 드래그해도 안 움직임
        | ImGuiWindowFlags_NoResize             // 모서리를 끌어도 크기 안 바뀜
        | ImGuiWindowFlags_NoCollapse           // 제목 표시줄의 접기 버튼 제거
        | ImGuiWindowFlags_NoSavedSettings;     // 창 정보를 저장하지 않음

    void Set_NextPanelRect(f32_t fX, f32_t fY, f32_t fW, f32_t fH)
    {
        ImGui::SetNextWindowPos(ImVec2(fX, fY), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(fW, fH), ImGuiCond_Always);
    }
}

HRESULT CTool::Initialize()
{
	return S_OK;
}

void CTool::Update(const f32_t& fDeltaTime)
{
    Render_MenuBar();
    Calc_Layout();

    Render_Hierachy();
    Render_Scene();
    Render_Inspector();

    if (m_bShowDemo)
        ImGui::ShowDemoWindow(&m_bShowDemo);
}

void CTool::Calc_Layout()
{
    // 현재 창 영역 크기
    const ImVec2 vDisplay = ImGui::GetIO().DisplaySize;

    // 메뉴바 바로 아래부터의 시작 좌표
    const f32_t fTop    = m_fMenuBarHeight;
    const f32_t fHeight = vDisplay.y - fTop;
    
    // 최소 씬 폭 보정
    f32_t fSide = m_fSidePamelWidth;
    const f32_t fMinScene = 200.f;
    if (vDisplay.x - fSide * 2.f < fMinScene)
        fSide = max(0.f, (vDisplay.x - fMinScene) * 0.5f);

    // 세 창의 Rect 정보
    m_tHierarchy    = { 0.f, fTop, fSide, fHeight };
    m_tScene        = { fSide, fTop, vDisplay.x - fSide * 2.f, fHeight };
    m_tInspector    = { vDisplay.x - fSide, fTop, fSide, fHeight };
}

void CTool::Render_MenuBar()
{
    // 화면 맨 위에 꽉 차게 붙는 메뉴 바.
    // 일반 창(Begin) 안이 아니라 바깥에서 호출한다.
    // 일반 창(Begin)과는 다르게 false를 반환하면 EndMainMenuBar를 호출하지 않고 빠져나간다.
    if (!ImGui::BeginMainMenuBar())
        return;

    m_fMenuBarHeight = ImGui::GetWindowHeight();

    // 펼쳐지는 메뉴
    // true일 때만 EndMenu를 호출.
    if (ImGui::BeginMenu("File"))
    {   
        // MenuItem(라벨, 단축키표시, 선택됨, 활성화);
        // 단축키는 오른쪽에 보이는 글자일 뿐이고 실제 동작은 따로 만들어야 함.
        ImGui::MenuItem("New Scene", nullptr, false, false);
        ImGui::MenuItem("Open Scene", "Ctrl + O", false, false);
        ImGui::MenuItem("Save", "Ctrl + S", false, false);
        ImGui::MenuItem("Save As", nullptr, false, false);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Veiw"))
    {
        ImGui::MenuItem("ImGui Demo", nullptr, &m_bShowDemo);
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

void CTool::Render_Hierachy()
{
    Set_NextPanelRect(m_tHierarchy.fX, m_tHierarchy.fY, m_tHierarchy.fW, m_tHierarchy.fH);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        ImGui::TextDisabled("(empty)");
    }
    ImGui::End();
}

void CTool::Render_Scene()
{
    // 창의 크기와 위치 지정
    Set_NextPanelRect(m_tScene.fX, m_tScene.fY, m_tScene.fW, m_tScene.fH);

    // 창 옵션
    constexpr ImGuiWindowFlags eSceneFlags = g_FixedPanelFlags
        | ImGuiWindowFlags_NoScrollbar 
        | ImGuiWindowFlags_NoScrollWithMouse;

    // 스타일 스택 호출
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::Begin("Scene", nullptr, eSceneFlags);
    // 스타일 스택 복구
    ImGui::PopStyleVar();
    const ImVec2 vAvail = ImGui::GetContentRegionAvail();
    const f32_t fAspect = static_cast<f32_t>(g_iToolWinSizeX) / g_iToolWinSizeY;
    ImVec2 vSize = vAvail;

    if (vAvail.x <= 0.f || vAvail.y <= 0.f)
    {
        ImGui::End();
        return;
    }
    if (vAvail.x / vAvail.y > fAspect)  
        vSize.x = vAvail.y * fAspect;   
    else                               
        vSize.y = vAvail.x / fAspect;   

    const ImVec2 vCursor = ImGui::GetCursorPos();   // 창 기준 좌표
    ImGui::SetCursorPos(ImVec2(vCursor.x + (vAvail.x - vSize.x) * 0.5f,
        vCursor.y + (vAvail.y - vSize.y) * 0.5f));

    
    ID3D11ShaderResourceView* pSRV = CGameInstance::Get().Get_SceneSRV();
    ImGui::Image((ImTextureID)pSRV, vSize);

    //// (6) 나중 단계에서 쓸 정보 저장
    m_vImageMin     = ImGui::GetItemRectMin();  // 화면 기준 좌상단 좌표
    m_vImageSize    = vSize;                    // 같은 곳
    m_bHovered      = ImGui::IsItemHovered();   // 카메라 드래그 + 카메라 피킹
    m_bFocused      = ImGui::IsWindowFocused(); // 카메라 조작 허용

    ImGui::End();
}

void CTool::Render_Inspector()
{
    Set_NextPanelRect(m_tInspector.fX, m_tInspector.fY, m_tInspector.fW, m_tInspector.fH);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        ImGui::TextDisabled("No object selected");
    }
    ImGui::End();
    
}

unique_ptr<CTool> CTool::Create()
{
    auto pInstance = unique_ptr<CTool>(new CTool());
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CTool");
        pInstance.reset();
    }
    return pInstance;
}
