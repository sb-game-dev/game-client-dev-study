#include "pch.h"
#include "CMainGame.h"
#include "CObjMgr.h"
#include "CAbstactFactory.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"
#include "CObstacle.h"
#include "CKeyMgr.h"
CMainGame::CMainGame() :m_dwTime1(GetTickCount()), m_dwTime2(GetTickCount()), m_dwTime3(GetTickCount()), m_dwTime4(GetTickCount()), m_dwTime5(GetTickCount()), m_dwTime6(GetTickCount()), m_dwTime7(GetTickCount())

{
	m_hDC = NULL;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CLineMgr::GetInstance()->Initialize();
	float fTemp = 0.f;
	CScrollMgr::GetInstance()->SetScrollX(fTemp);
	//CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstactFactory<CPlayer>::Create(fTemp, 0.f));
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstactFactory<CPlayer>::Create());

	//CScrollMgr::GetInstance()->SetScrollY(0.f);
}

void CMainGame::Update()
{
	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).empty())
		Restart();
	CKeyMgr::GetInstance()->KeyUpdate();

	if (m_dwTime1 + 1300 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, CAbstactFactory<CObstacle>::Create(175.f + 300.f, 0.f));
		m_dwTime1 = GetTickCount();
	}
	if (m_dwTime2 + 2250 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, CAbstactFactory<CObstacle>::Create(175.f + 400.f, 0.f));
		m_dwTime2 = GetTickCount();
	}
	if (m_dwTime3 + 1000 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, CAbstactFactory<CObstacle>::Create(175.f + 700.f, 0.f));
		m_dwTime3 = GetTickCount();
	}
	if (m_dwTime4 + 1300 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, CAbstactFactory<CObstacle>::Create(175.f + 1000.f, 0.f));
		m_dwTime4 = GetTickCount();
	}
	if (m_dwTime5 + 1650 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, CAbstactFactory<CObstacle>::Create(175.f + 1100.f, 0.f));
		m_dwTime5 = GetTickCount();
	}
	if (m_dwTime6 + 1000 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, CAbstactFactory<CObstacle>::Create(175.f + 1700.f, 0.f));
		m_dwTime6 = GetTickCount();
	}
	if (m_dwTime7 + 1300 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_OBSTACLE, CAbstactFactory<CObstacle>::Create(175.f + 1800.f, 0.f));
		m_dwTime7 = GetTickCount();
	}
	CObjMgr::GetInstance()->Update(); 
	CLineMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CLineMgr::GetInstance()->Render(m_hDC);
	CObjMgr::GetInstance()->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::GetInstance()->DestroyInstance();
	CLineMgr::GetInstance()->DestroyInstance();
	CScrollMgr::GetInstance()->DestroyInstance();
}

void CMainGame::Restart()
{
	Release();
	Initialize();
	CScrollMgr::GetInstance()->SetScrollX(-CScrollMgr::GetInstance()->GetScrollX());
}
