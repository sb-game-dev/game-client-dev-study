#include "pch.h"
#include "CMainGame.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CMouse.h"
#include "CMonster.h"
#include "CWall.h"
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

	//CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	//CObjMgr::GetInstance()->AddObject(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());
	//CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create());
	//
	//for (int i = 0; i < 5; i++)
	//{
	//	CObjMgr::GetInstance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(150.f, i * 40.f + 20.f, 40.f, 40.f, INF, 2));
	//	CObjMgr::GetInstance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(650.f, i * 40.f + 20.f, 40.f, 40.f, INF, 2));
	//}
	//
	//for (int i = 1; i <= 3; i++)
	//{
	//	CObjMgr::GetInstance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(150.f + i*40.f, 180.f, 40.f, 40.f, INF, 2));
	//	CObjMgr::GetInstance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(650.f - i*40.f, 180.f, 40.f, 40.f, INF, 2));
	//}
	//
	////OBJ_SANDWALL
	//for (int i = 1; i <= 4; i++)
	//{
	//	CObjMgr::GetInstance()->AddObject(OBJ_SANDWALL1, CAbstractFactory<CWall>::Create(180.f + i * 40.f, 320.f, 40.f, 40.f, 30, 2));
	//	CObjMgr::GetInstance()->AddObject(OBJ_SANDWALL2, CAbstractFactory<CWall>::Create(620.f - i * 40.f, 320.f, 40.f, 40.f, 30, 2));
	//}
}

void CMainGame::Update()
{
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
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CObjMgr::GetInstance()->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::GetInstance()->DestroyInstance();
}
