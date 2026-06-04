#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CBlock.h"
#include "CMouse.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CTileMgr.h"
CMainGame::CMainGame() :m_iFPS(0), m_dwTime(GetTickCount())
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	//CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Player/Playermove_Up.bmp", L"Back");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/BackBuffer.bmp", L"Back");
	

	CSceneMgr::GetInstance()->SceneChange(SC_LOGO);
	
}

void CMainGame::Update()
{
	CKeyMgr::GetInstance()->KeyUpdate();
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		m_dwTime = GetTickCount();

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
	}
	HDC hBack = CBmpMgr::GetInstance()->FindImage(L"Back");

	CSceneMgr::GetInstance()->Render(hBack);

	//POINT		ptMouse;
	//GetCursorPos(&ptMouse);
	//ScreenToClient(g_hWnd, &ptMouse);
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"MouseX : %ld", ptMouse.x);
	//TextOut(hBack, 50, 50, szBuff, lstrlen(szBuff));
	//
	//swprintf_s(szBuff, L"MouseX : %ld", ptMouse.y);
	//TextOut(hBack, 50, 75, szBuff, lstrlen(szBuff));
	
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);


	//CObjMgr::GetInstance()->DestroyInstance();
	//CKeyMgr::GetInstance()->DestroyInstance();
	//CSceneMgr::GetInstance()->DestroyInstance();
	//CBmpMgr::GetInstance()->DestroyInstance();


	CTileMgr::DestroyInstance();
	CSceneMgr::DestroyInstance();
	CBmpMgr::DestroyInstance();
	CKeyMgr::DestroyInstance();
	CObjMgr::DestroyInstance();
}
