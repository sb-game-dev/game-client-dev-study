#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame():m_pPlayer(nullptr), m_pMonster(nullptr)
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
	dynamic_cast<CPlayer*> (m_pPlayer)->SetBullet(&m_BulletList);
	if (!m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}
}

void CMainGame::Update()
{
	m_pPlayer->Update();
	m_pMonster->Update();
	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end();)
	{
		(*iter)->Update();
		if (dynamic_cast<CBullet*> (*iter)->CheckColiision())
		{
			Safe_Delete((*iter));
			iter = m_BulletList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 50, 50, WINCX - 50, WINCY - 50);
	m_pPlayer->Render(m_hDC);
	m_pMonster->Render(m_hDC);
	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end(); ++iter)
	{
		(*iter)->Render(m_hDC);
	}
}

void CMainGame::Release()
{
	Safe_Delete(m_pPlayer);
	Safe_Delete(m_pMonster);
	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end();++iter)
	{
		Safe_Delete((*iter));
	}
	m_BulletList.clear();
}

