#include "imgui.h" 
#include "MapTool_Defines.h"
#include "ToolMainApp.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Level_MapTool.h"
#include "Tool.h"
#include "MapTool_Cam.h"
CToolMainApp::~CToolMainApp()
{
    m_pTool.reset();
    Shutdown_ImGui();
    CGameInstance::Get().Release_Engine();
}

HRESULT CToolMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비 */

    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iToolWinSizeX;
    EngineDesc.iWinSizeY = g_iToolWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);
    EngineDesc.hInstance = hInst;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;
    
    if (FAILED(Ready_ImGui()))
        return E_FAIL;

    m_pTool = CTool::Create();
    if (nullptr == m_pTool)
        return E_FAIL;
    
    // 씬 생성
    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::MAPTOOL),
        CLevel_MapTool::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    CGameInstance::Get().Set_DrawToBackBuffer(false);

    return S_OK;
}

void CToolMainApp::Update(f32_t fDeltaTime)
{
    if (FAILED(Begin_ImGui()))
        return;
    m_pTool->Update(fDeltaTime);
    //Sync_SceneView();
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

HRESULT CToolMainApp::Render()
{
    // Clear
    float4_t    vClearColor = float4_t{ 0.f, 0.f, 0.f, 1.f };
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Draw();
    
    if (FAILED(Render_ImGui()))
        return E_FAIL;

    CGameInstance::Get().Present();
    return S_OK;
}



HRESULT CToolMainApp::Ready_ImGui()
{
    // 1. 컨텍스트 생성
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGui와 애플리케이션이 정보를 주고받는 구조체
    // 설정, 입력, 출력, 폰트가 있음
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // 키보드로 위젯 이동
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // docking 브랜치 기능

    // 2. 한글 폰트 (1.92 이상은 글리프를 필요할 때 만들기 때문에 범위 지정 불필요)
    if (nullptr == io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 16.f))
        io.Fonts->AddFontDefault();                         // 실패하면 기본 폰트 (영문만)

    // 3. 스타일
    ImGui::StyleColorsDark();

    // 4. 플랫폼/렌더러 백엔드
    if (!ImGui_ImplWin32_Init(g_hWnd))
        return E_FAIL;
    if (!ImGui_ImplDX11_Init(m_pDevice.Get(), m_pContext.Get()))
        return E_FAIL;

    m_bReadyImGui = true;
    return S_OK;
}

HRESULT CToolMainApp::Begin_ImGui()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    return S_OK;
}

HRESULT CToolMainApp::Render_ImGui()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return S_OK;
}

HRESULT CToolMainApp::Shutdown_ImGui()
{
    if (!m_bReadyImGui)
        return E_FAIL;
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return S_OK;
}

void CToolMainApp::Sync_SceneView()
{
    auto pCamera = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Get_MainCamera());
    if (nullptr == pCamera)
        return;
    pCamera->Set_SceneClicked(m_pTool->GetSceneCliked());

}

unique_ptr<CToolMainApp> CToolMainApp::Create()
{
    auto    pInstance = unique_ptr<CToolMainApp>(new CToolMainApp());

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CToolMainApp");
        pInstance.reset();
    }
    return pInstance;
}
