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

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}

	if (!m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}

	dynamic_cast<CMonster*>(m_pMonster)->SetPlayer(m_pPlayer);

}

void CMainGame::Update()
{
	m_pPlayer->Update();
	m_pMonster->Update();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	m_pPlayer->Render(m_hDC);
	m_pMonster->Render(m_hDC);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);

	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CObj*>(m_pMonster);

}
