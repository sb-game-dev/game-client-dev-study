#include "ImGui_Manager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

CImGui_Manager::~CImGui_Manager()
{
    if (!m_bInitialized)
        return;
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

HRESULT CImGui_Manager::Initialize(HWND hWnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
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

    // 4. 플랫폼/렌더러 백엔드 (영상의 Win32_Init + DX9_Init 자리를 DX11로)
    if (!ImGui_ImplWin32_Init(hWnd))
        return E_FAIL;
    if (!ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get()))
        return E_FAIL;

    m_bInitialized = true;
    return S_OK;
}

void CImGui_Manager::Begin_Frame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void CImGui_Manager::Render()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}



unique_ptr<CImGui_Manager> CImGui_Manager::Create(HWND hWnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = unique_ptr<CImGui_Manager>(new CImGui_Manager());

    if (FAILED(pInstance->Initialize(hWnd, pDevice, pContext)))
    {
        MSG_BOX("Failed to Created : CImGui_Manager");
        pInstance.reset();
    }
    return pInstance;
}