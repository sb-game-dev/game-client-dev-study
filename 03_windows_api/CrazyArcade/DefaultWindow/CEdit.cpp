#include "pch.h"
#include "CEdit.h"
#include "CTileMgr.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"

CEdit::CEdit()
{
}

CEdit::~CEdit()
{
}

void CEdit::Initialize()
{
    CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Stage1.bmp", L"Ground");
    CTileMgr::GetInstance()->Initialize();
}

int CEdit::Update()
{
    CTileMgr::GetInstance()->Update();
    KeyInput();
    return 0;
}

void CEdit::LateUpdate()
{
    CTileMgr::GetInstance()->LateUpdate();
}

void CEdit::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::GetInstance()->FindImage(L"Ground");
    BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
    CTileMgr::GetInstance()->Render(hDC);
}

void CEdit::Release()
{

}

void CEdit::KeyInput()
{
    if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
    {
        POINT ptMouse{};
        GetCursorPos(&ptMouse);
        ScreenToClient(g_hWnd, &ptMouse);
        CTileMgr::GetInstance()->PickingTile(ptMouse);
    }

    if (CKeyMgr::GetInstance()->KeyDown('S'))
        CTileMgr::GetInstance()->SaveTile();
    if (CKeyMgr::GetInstance()->KeyDown('L'))
        CTileMgr::GetInstance()->LoadTile();
}
