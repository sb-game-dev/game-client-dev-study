#include "CMainGame.h"
#include "pch.h"
#include "CPlayer.h"
#include "CField.h"
CMainGame::CMainGame()
{
	m_pPlayer = nullptr;
	m_pField = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}


void CMainGame::Initialize()
{
	m_pPlayer = CPlayer::Create();
	m_pPlayer->Initialize();
	m_pField = CField::Create();
	m_pField->SetPlayer(m_pPlayer);
}


void CMainGame::Update()
{
	int iInput;
	while (true)
	{
		m_pPlayer->Render();
		cout << "1. 사냥 2. 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_pField->Update();
			break;
		case 2:
			return;
		default:
			break;
		}
	}
}

void CMainGame::Release()
{
	m_pField->Destroy();
	m_pPlayer->Destroy();
}

CMainGame* CMainGame::Create()
{
	CMainGame* pObj = new CMainGame;
	return pObj;
}

void CMainGame::Destroy()
{
	delete this;
}
