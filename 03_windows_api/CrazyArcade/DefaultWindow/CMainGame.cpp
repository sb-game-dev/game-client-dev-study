#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CBlock.h"
#include "CMouse.h"

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
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::GetInstance()->AddObject(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());
	//CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(300.f, 200.f));
	
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 12; ++j)
		{
			if (rand() % 10 < 1)
				CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 20), float(j * 40 + 60), BT_PUSH));
		}
	}
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 12; ++j)
		{
			if (rand() % 10 < 1)
				CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 20), float(j * 40 + 60),BT_BREAK));
		}
	}
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
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		m_dwTime = GetTickCount();

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
	}
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
