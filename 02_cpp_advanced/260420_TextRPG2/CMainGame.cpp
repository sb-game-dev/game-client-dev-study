#include "pch.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CField.h"
#include "CStore.h"
CMainGame::CMainGame()
{
	m_pPlayer = nullptr;
	m_pField = nullptr;
	m_pStore = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initailze()
{
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer();
		//m_pPlayer->SelectJob();
	}
	if (!m_pField)
	{
		m_pField = new CField();
		m_pField->SetPlayer(m_pPlayer);
	}
	if (!m_pStore)
	{
		m_pStore = new CStore;
		m_pStore->SetPlayer(m_pPlayer);
	}

}


void CMainGame::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 사냥터 2. 상점 3. 게임 종료: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			m_pField->Update();
			break;
		case 2:
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void CMainGame::Release()
{
	SAFEDELETE(m_pPlayer);
	SAFEDELETE(m_pField);
	SAFEDELETE(m_pStore);
}
