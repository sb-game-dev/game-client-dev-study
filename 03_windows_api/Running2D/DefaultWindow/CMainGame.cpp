#include "pch.h"
#include "CMainGame.h"
#include "CObjMgr.h"
#include "CAbstactFactory.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"
CMainGame::CMainGame()
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

	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstactFactory<CPlayer>::Create());
	CLineMgr::GetInstance()->Initialize();
}

void CMainGame::Update()
{
	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).empty())
		Restart();
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
