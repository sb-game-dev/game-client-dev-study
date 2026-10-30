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

    if (ImGui::BeginMenu("View"))
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
    vSize.y = vAvail.x / fAspect;   

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
    m_vImageMin     = float2_t(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y);  // 화면 기준 좌상단 좌표
    m_vImageSize    = float2_t(vSize.x, vSize.y);   // 씬 화면 크기 -> 피킹에서 NDC로 바꿀 때 나누는 값
    m_bHovered      = ImGui::IsItemHovered();       // 카메라 드래그 + 카메라 피킹에 사용
    m_bFocused      = ImGui::IsWindowFocused();     // 마지막으로 클릭된 창일 때 true 카메라 조작 허용 
                                                    // (Begin과 End 사이에서 불려야 이 창에 대한 값이 나옴)
    cout << m_bFocused << endl;
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
