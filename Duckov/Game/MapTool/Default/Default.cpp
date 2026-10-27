// Default.cpp : MapTool 진입점
#include "framework.h"
#include "Default.h"

#include "ToolApp.h"
#include "imgui.h" //ImGui::GetIO()를 사용하기 위해

#define MAX_LOADSTRING 100

HINSTANCE hInst;            // Client_Defines.h의 extern 정의
HWND      g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

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

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    MSG msg{};

    unique_ptr<CToolApp> pToolApp = CToolApp::Create();
    if (nullptr == pToolApp)
        return FALSE;
    if (FAILED(CGameInstance::Get().Add_Timer(TEXT("Timer_Default"))))
        return FALSE;
    if (FAILED(CGameInstance::Get().Add_Timer(TEXT("Timer_60"))))
        return FALSE;

    f32_t fTimeDeltaAcc = {};

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        CGameInstance::Get().Update_TimeDelta(TEXT("Timer_Default"));
        fTimeDeltaAcc += CGameInstance::Get().Get_TimeDelta(TEXT("Timer_Default"));
        if (fTimeDeltaAcc >= 1.f / 60.f)
        {
            CGameInstance::Get().Update_TimeDelta(TEXT("Timer_60"));
            pToolApp->Update(CGameInstance::Get().Get_TimeDelta(TEXT("Timer_60")));
            pToolApp->Render();
            fTimeDeltaAcc = 0.f;
        }
    }

    pToolApp.reset();
    return (int)msg.wParam;
}

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
    hInst = hInstance;

    RECT rc{ 0, 0, g_iWinSizeX, g_iWinSizeY };              // 클라이언트 영역을 정확히 1280x720으로
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindowW(szWindowClass, L"MapTool", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top,
        nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
        return FALSE;

    g_hWnd = hWnd;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

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