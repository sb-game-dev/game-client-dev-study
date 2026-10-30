#include "imgui.h" //ImGui::GetIO()를 사용하기 위해
#include "imgui_impl_win32.h"
#include "framework.h"
#include "Default.h"

#include "ToolMainApp.h"

#define MAX_LOADSTRING 100
// 전역 변수:
HINSTANCE hInst;            // 현재 인스턴스입니다.
HWND      g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];           // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];     // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// imgui_impl_win32.h에서 #if 0으로 막혀 있으므로 직접 선언
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // TODO: 여기에 코드를 입력합니다.
    // 
    // DPI 인식 설정
    ImGui_ImplWin32_EnableDpiAwareness();
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    MSG msg{};

    unique_ptr<CToolMainApp> pToolMainApp = CToolMainApp::Create();
    if (nullptr == pToolMainApp)
        return FALSE;
    if (FAILED(CGameInstance::Get().Add_Timer(TEXT("Timer_Default"))))
        return FALSE;
    if (FAILED(CGameInstance::Get().Add_Timer(TEXT("Timer_60"))))
        return FALSE;

    f32_t fTimeDeltaAcc = {};
    bool_t bDone = false;
    while (!bDone)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                bDone = true;
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        if (bDone)
            break;
        CGameInstance::Get().Update_TimeDelta(TEXT("Timer_Default"));
        fTimeDeltaAcc += CGameInstance::Get().Get_TimeDelta(TEXT("Timer_Default"));
        if (fTimeDeltaAcc >= 1.f / 60.f)
        {
            CGameInstance::Get().Update_TimeDelta(TEXT("Timer_60"));
            pToolMainApp->Update(CGameInstance::Get().Get_TimeDelta(TEXT("Timer_60")));
            pToolMainApp->Render();
            fTimeDeltaAcc = 0.f;
        }
    }

    pToolMainApp.reset();
    return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;  // 인스턴스 핸들을 전역 변수에 저장합니다.

    RECT rc{ 0, 0, g_iToolWinSizeX, g_iToolWinSizeY };
    AdjustWindowRectExForDpi(&rc, WS_OVERLAPPEDWINDOW, FALSE, 0, GetDpiForSystem());

    const int iWinW = rc.right - rc.left;
    const int iWinH = rc.bottom - rc.top;
    RECT rcWork{};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcWork, 0);
    const int iPosX = rcWork.left + ((rcWork.right - rcWork.left) - iWinW) / 2;
    const int iPosY = rcWork.top + ((rcWork.bottom - rcWork.top) - iWinH) / 2;

    HWND hWnd = CreateWindowW(szWindowClass, L"MapTool", WS_OVERLAPPEDWINDOW,
        iPosX, iPosY, iWinW, iWinH, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    g_hWnd = hWnd;
    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // ImGui가 먼저 메시지를 받음. true면 ImGui가 처리한 것
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_KEYDOWN:
        // ImGui 입력창에서 ESC를 눌러도 툴이 꺼지지 않게
        if (VK_ESCAPE == wParam && (nullptr == ImGui::GetCurrentContext() || !ImGui::GetIO().WantCaptureKeyboard))
            DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}