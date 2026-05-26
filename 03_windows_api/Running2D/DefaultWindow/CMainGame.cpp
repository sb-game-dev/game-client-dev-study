#include "pch.h"
#include "CMainGame.h"
#include "CObjMgr.h"
#include "CAbstactFactory.h"
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

	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstactFactory<CPlayer>::Create());
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
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	MoveToEx(m_hDC, 0, 400, nullptr);
	LineTo(m_hDC, 250, 400);
	MoveToEx(m_hDC, 250, 400, nullptr);
	LineTo(m_hDC, 550, 200);
	MoveToEx(m_hDC, 550, 200, nullptr);
	LineTo(m_hDC, 800, 200);

	CObjMgr::GetInstance()->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::GetInstance()->DestroyInstance();
}
