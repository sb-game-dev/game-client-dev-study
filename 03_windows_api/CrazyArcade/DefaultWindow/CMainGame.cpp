#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
CMainGame::CMainGame() 
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/BackBuffer.bmp", L"Back");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Stage1.bmp", L"Ground");
}

void CMainGame::Update()
{
	CKeyMgr::GetInstance()->KeyUpdate();
	CObjMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	HDC hBack = CBmpMgr::GetInstance()->FindImage(L"Back");
	HDC	hGround = CBmpMgr::GetInstance()->FindImage(L"Ground");
	BitBlt(hBack, 0, 0, WINCX, WINCY, hGround, 0, 0, SRCCOPY);
	CObjMgr::GetInstance()->Render(hBack);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CBmpMgr::GetInstance()->DestroyInstance();
}
