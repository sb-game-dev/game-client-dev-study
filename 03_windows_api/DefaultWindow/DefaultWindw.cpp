// DefaultWindw.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DefaultWindw.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);   //창 스타일 지정 옵션
BOOL                InitInstance(HINSTANCE, int);           // 창 생성 관련 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);    // 메세지 처리기
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);      // 쓸 데 없음

void RenderRobot(HDC hdc);
void Shoot(HDC hdc, RECT ,RECT);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,             // 창이 생성되면서 발생한 인스턴스 정보를 저장하는 곳
                     _In_opt_ HINSTANCE hPrevInstance,      // 이 프로그램이 시작되기 전에 이전 프로그램의 인스턴스를 받는 곳(없으면 NULL)
                     _In_ LPWSTR    lpCmdLine,              // LP(포인터), W(유니코드), STR(문자열)
                     _In_ int       nCmdShow)               // 창 생성 옵션
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDW));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEFAULTWINDW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

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

RECT rc{ 350,400,450,500 };
//RECT bullet{(rc.left+rc.right)/2, rc.top+10,(rc.left + rc.right) / 2 + 10,rc.top};

vector<RECT> vecBullts;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 0, 0);
        break;
    
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, true);

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        case VK_RIGHT:
            rc.left += 10;
            rc.right += 10;
            break;
        case VK_LEFT:
            rc.left -= 10;
            rc.right -= 10;
            break;
        case VK_UP:
            rc.top -= 10;
            rc.bottom -= 10;
            break;
        case VK_DOWN:
            rc.top += 10;
            rc.bottom += 10;
            break;

        case VK_SPACE:
            if(vecBullts.size()<3)
                vecBullts.push_back({ (rc.left + rc.right) / 2, rc.top + 10,(rc.left + rc.right) / 2 + 10,rc.top });
            break;
        default:
            break;
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            //과제 2
            RenderRobot(hdc);

            //과제 3
            vecBullts.reserve(10);
            Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
            for_each(vecBullts.begin(), vecBullts.end(),
                [&hdc](RECT& bullet) {
                    bullet.top -= 5;
                    bullet.bottom -= 5;
                    Rectangle(hdc, bullet.left, bullet.top, bullet.right, bullet.bottom);
                    if (bullet.top <= 0)
                    {
                        auto iter = vecBullts.begin();
                        vecBullts.erase(iter);
                    }
                });
            EndPaint(hWnd, &ps);
        }
        break;
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

void RenderRobot(HDC hdc)
{
    int i_xZero = 400;
    int i_yZero = 300;

    // 모자
    Rectangle(hdc, i_xZero - 35, i_yZero - 200, i_xZero + 35, i_yZero - 130);

    MoveToEx(hdc, i_xZero - 80, i_yZero - 130, nullptr);
    LineTo(hdc, i_xZero + 80, i_yZero - 130);

    MoveToEx(hdc, i_xZero, i_yZero - 130, nullptr);
    LineTo(hdc, i_xZero, i_yZero - 120);

    // 얼굴
    Ellipse(hdc, i_xZero - 60, i_yZero - 120, i_xZero + 60, i_yZero); 

    Ellipse(hdc, i_xZero - 35, i_yZero - 80, i_xZero - 15, i_yZero - 60);//왼쪽 눈
    Ellipse(hdc, i_xZero + 15, i_yZero - 80, i_xZero + 35, i_yZero - 60);//오른쪽 눈

    Rectangle(hdc, i_xZero - 15, i_yZero - 45, i_xZero + 15, i_yZero - 25);// 입

    Rectangle(hdc, i_xZero - 60, i_yZero, i_xZero + 60, i_yZero + 120);// 몸

    //왼팔
    MoveToEx(hdc, i_xZero - 60, i_yZero, nullptr);
    LineTo(hdc, i_xZero - 120, i_yZero - 60);
    Ellipse(hdc, i_xZero - 140, i_yZero - 85, i_xZero - 110, i_yZero - 55);

    //오른팔
    MoveToEx(hdc, i_xZero + 60, i_yZero, nullptr);
    LineTo(hdc, i_xZero + 120, i_yZero + 60);
    Ellipse(hdc, i_xZero + 110, i_yZero + 55, i_xZero + 140, i_yZero + 85);

    //왼발
    MoveToEx(hdc, i_xZero - 30, i_yZero + 120, nullptr);
    LineTo(hdc, i_xZero - 30, i_yZero + 160);
    Rectangle(hdc, i_xZero - 60, i_yZero + 160, i_xZero - 20, i_yZero + 200);

    //오른발
    MoveToEx(hdc, i_xZero + 30, i_yZero + 120, nullptr);
    LineTo(hdc, i_xZero + 30, i_yZero + 160);
    Rectangle(hdc, i_xZero + 20, i_yZero + 160, i_xZero + 60, i_yZero + 200);
}

void Shoot(HDC hdc, RECT rObj, RECT rBullet)
{

}
