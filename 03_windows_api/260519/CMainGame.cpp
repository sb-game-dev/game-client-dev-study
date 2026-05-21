#include "pch.h"
#include "CMainGame.h"
#include "Define.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CMouse.h"
#include "CObjMgr.h"
CMainGame::CMainGame():m_hDC(WM_NULL)
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
	for (int i = 0; i < 5; i++)
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER,CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY));
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
	CObjMgr::GetInstance()->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::DestroyInstance();
}

