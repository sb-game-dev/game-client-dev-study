#include "CMainGame.h"
#include "pch.h"
#include "CPlayer.h"
#include "CObj.h"
#include "CField.h"
#include "CShop.h"
CMainGame::CMainGame()
{
	m_pPlayer = nullptr;
	m_pField = nullptr;
	m_pShop = nullptr;
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
	m_pShop = CShop::Create();
	m_pShop->SetPlayer(m_pPlayer);
}



void CMainGame::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 사냥터 2. 상점 3. 종료: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			m_pField->Update();
			break;
		case 2:
			m_pShop->Update();
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
	m_pField->Destroy();
	m_pPlayer->Destroy();
	m_pShop->Destroy();
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
