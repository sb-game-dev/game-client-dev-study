#include "pch.h"
#include "CMainGame.h"
#include "CMonster.h"

CMainGame::CMainGame() : m_pPlayer(nullptr), m_pMonster(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}



}

void CMainGame::Update()
{
	m_pPlayer->Update();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	m_pPlayer->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);

	Safe_Delete<CObj*>(m_pPlayer);

}
