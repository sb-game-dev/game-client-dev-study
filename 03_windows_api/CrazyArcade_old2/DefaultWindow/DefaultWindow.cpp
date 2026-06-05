// DefaultWindow.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DefaultWindow.h"
#include "CMainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);   // 창 스타일 지정 옵션
BOOL                InitInstance(HINSTANCE, int);           // 창 생성 관련 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);    // 메세지 처리기
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);      // 쓸데 없음

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 창이 생성되면서 발생한 인스턴스 정보를 저장하는 곳
                     _In_opt_ HINSTANCE hPrevInstance,  // 이 프로그램이 시작되기 전에 이전 프로그램의 인스턴스를 받는 곳(없으면 NULL)
                     _In_ LPWSTR    lpCmdLine,          // LP(포인터) W(유니코드) STR(문자열)
                     _In_ int       nCmdShow)           // 창 생성 옵션
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);

    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
    msg.message = WM_NULL;

    CMainGame       MainGame;
    MainGame.Initialize();

    DWORD   dwTime = GetTickCount();    // 1000


    // 기본 메시지 루프입니다:
    while (true)
    {
        // PM_REMOVE   : 메세지 큐에 메세지가 있을 경우, 가지고 오면서 큐로부터 메세지를 삭제
        // PM_NOREMOVE : 메세지 큐에 메세지 유무 상태만 파악, 만약 큐에 있는 메세지를 가져오려면 개별적으로 GetMessage 함수를 다시 호출해야 함

        // PeekMessage : 메세지가 없을 경우 거짓을 반환

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }     

        else
        {
            if (dwTime + 10 < GetTickCount())
            {
                MainGame.Update();
                MainGame.LateUpdate();
                MainGame.Render();

                dwTime = GetTickCount();
            }            
        }
    }

    return (int) msg.wParam;
}   // 창 생성 옵션



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;       // 윈도우 창 만들 때, 필요한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);       // 자기 자신의 사이즈를 저장해 놓음

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    // 윈도우 창의 스타일을 정의, 어떤 형태를 가질 것인지 지정

    // CS_HREDRAW : 가로 다시 그리기
    // CS_VREDRAW : 세로 다시 그리기


    wcex.lpfnWndProc    = WndProc;  // 저장해둔 함수가 호출되어 메세지를 처리

    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    // 윈도우가 특수한 목적으로 사용하는 여분의 공간

    wcex.hInstance      = hInstance;

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
    // 윈도우 창이 사용할 아이콘 지정
    
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    // 마우스 커서

    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    // 윈도우 창 배경 색상

    wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);

    wcex.lpszClassName  = szWindowClass;
    // 실행파일 이름 문자열(대개 프로젝트 이름을 기본 값 설정)

    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    // 창 상단에 출력하는 아이콘 모양

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 핸들(HANDLE) : 리소스마다 부여되는 고유 식별 번호, 16진수 형태의 정수로 제공
   RECT rcWindow{ 0, 0, WINCX, WINCY };

   AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW, FALSE);

   // rcWindow = rcWindow + 기본 창 옵션을 고려한 사이즈 적용 + 메뉴 바의 크기 고려 여부

   HWND hWnd = CreateWindowW(szWindowClass, 
                            szTitle, 
                            WS_OVERLAPPEDWINDOW,        // 만들고자 하는 윈도우 창의 형태(스타일) 지정 옵션, 현재 값은 기본 창의 형태 옵션을 의미
                            CW_USEDEFAULT, 0,           // LEFT, TOP 좌표
                            rcWindow.right - rcWindow.left, 
                            rcWindow.bottom - rcWindow.top,                   // 가로, 세로 사이즈
                            nullptr,                    // 만약 부모 윈도우가 있다면 부모 윈도우의 핸들을 지정, 없을 경우 NULLPTR
                            nullptr,                    // 윈도우에서 사용할 메뉴의 핸들 지정  
                            hInstance, 
                            nullptr);                   // 운영체제가 특수한 목적으로 사용

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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

// 1. KERNEL : 메모리르 관리하고 프로그램을 실행시키는 명령어들의 집합
// 2. USER : 유저 인터페이스, 윈도우 창 관리 명령어들의 집합
// 3. GDI : 화면 처리와 그래픽 담당 명령어 집합

RECT        rc{ 100, 100, 200, 200 };
list<RECT>  BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
  //  case WM_CREATE:
  //      SetTimer(hWnd, 0, 0, 0);
  //
  //      // 타이머 설치 함수(안 중요함)
  //
  //      // 2인자 : 타이머의 id번호
  //      // 3인자 : 타이머 주기, 기본 값으로 1 / 1000초 꼴로 주기 설정
  //      // 4인자 : null일 경우 설정한 주기(3인자)대로 WM_TIMER 메세지 발생
  //      break;
  //
  //  case WM_TIMER:
  //
  //      InvalidateRect(hWnd, NULL, true);
  //
  //      // 윈도우 갱신 함수(WM_PAINT 메세지 발생)
  //
  //      // 2인자 : 윈도우 안에서 갱신할 범위를 지정(null인 경우 전체화면 모두)
  //      // 3인자 : true인경우 그려져있지 않는 부분도 갱신, false 인 경우 새로 그리는 부분만 갱신
  //      break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;

      //  case VK_RIGHT:
      //      rc.left  += 10;
      //      rc.right += 10;
      //      break;
      //
      //  case VK_LEFT:
      //      rc.left  -= 10;
      //      rc.right -= 10;
      //      break;
      //
      //  case VK_UP:
      //      rc.top    -= 10;
      //      rc.bottom -= 10;
      //      break;
      //
      //  case VK_DOWN:
      //      rc.top    += 10;
      //      rc.bottom += 10;
      //      break;
      //
      //  case VK_SPACE:
      //      BulletList.push_back(rc);
      //      break;
        }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    //case WM_PAINT:
    //    {
    //        PAINTSTRUCT ps;
    //       
    //
    //        // DC : 출력에 관한 정보를 갖고 있는 데이터 구조체
    //
    //        // 화면 DC를 얻는 방법
    //        // 
    //        // 1. BeginPaint
    //        // 2. GetDC
    //
    //        HDC hdc = BeginPaint(hWnd, &ps);
    //
    //        // 그리기 함수 호출
    //
    //        // 커서의 위치를 이동시키는 함수
    //        //MoveToEx(hdc, 100, 100, nullptr);
    //        //
    //        //LineTo(hdc, 200, 100);
    //        //LineTo(hdc, 200, 200);
    //        //LineTo(hdc, 100, 200);
    //        //LineTo(hdc, 100, 100);
    //        //LineTo(hdc, 200, 200);
    //        //
    //        //MoveToEx(hdc, 200, 100, nullptr);
    //        //LineTo(hdc, 100, 200);
    //
    //        // 선 그리기 함수
    //        //LineTo(hdc, 200, 200);
    //        //LineTo(hdc, 200, 300);
    //
    //        // 사각형 그리기 함수
    //        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    //
    //        // 원 그리기 함수
    //       // Ellipse(hdc, 300, 300, 400, 400);
    //
    //        // 총알 그리기
    //
    //        for (auto& Bullet : BulletList)
    //        {
    //            Ellipse(hdc, Bullet.left, Bullet.top, Bullet.right, Bullet.bottom);
    //
    //            Bullet.top    -= 10;
    //            Bullet.bottom -= 10;
    //        }
    //
    //        EndPaint(hWnd, &ps);
    //    }
    //    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// 함수 호출 규약 : caller(호출자, 호출원), callee(피호출자)

// __cdecl     : c / c++ 언어의 기본 호출 규약, '호출자가 stack을 정리', 가변인자 함수
// __stdcall   : winapi 기본 호출 규약, 피호출자가 stack을 정리, 고정인자 함수
 
// __fastcall  : 함수 호출을 빠르게 처리하기 위한 호출 규약, 피호출자가 stack을 정리
// __thiscall  : this 포인터로 매개 변수를 전달 받을 때 사용하는 규약, 피호출자가 stack을 정리




// 1. 함수 호출 규약이 무엇인지 알아와라.(343p) 
// 2. 각종 그리기 함수를 이용하여 무엇이든지 그려와라.
// 3. 스페이스 바를 누르면 위로 나가는 총알을 구현하라.(조건) stl 컨테이너 활용 할 것
