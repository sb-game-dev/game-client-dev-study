#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CBomb.h"
#include "CMonster.h"
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
	

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 12; ++j)
		{
			if(rand()%10 < 1)
				CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(float(i * 40 + 20), float(j * 40 + 20), 100, 100));
			//else
			//	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(900+ 20, j * 700 + 20, 100, 100));
		}
	}
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

		m_iFPS = 0;

		m_dwTime = GetTickCount();

		SetWindowText(g_hWnd, m_szFPS);
	}

	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CObjMgr::GetInstance()->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::DestroyInstance();
}
