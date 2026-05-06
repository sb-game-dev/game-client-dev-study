#include "CMainGame.h"
#include "pch.h"
#include "Define.h"
#include "CPlayer.h"
#include "CField.h"
#include "CStore.h"
CMainGame::CMainGame(): m_pPlayer(nullptr),m_pField(nullptr),m_pStore(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		CPlayer* tempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);
		if (tempPlayer)
		{
			tempPlayer->SelectJob();
		}
	}
	if (!m_pField)
	{
		m_pField = new CField;
		m_pField->SetPlayer(m_pPlayer);
	}
	if (!m_pStore)
	{
		m_pStore = new CStore;
		m_pStore->SetPlayer(m_pPlayer);
		m_pStore->Initialize();
	}
}



void CMainGame::Update()
{
	int iInput;
	CPlayer* tempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 사냥터 2. 상점 3. 인벤토리 4. 게임 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case FIELD:
			m_pField->Update();
			break;
		case STORE:
			m_pStore->Update();
			break;
		case INVENTORY:
			tempPlayer->InvUpdate();
			break;
		case END_MENU:
			return;
		default:
			break;
		}
	}
}

void CMainGame::Release()
{
	SafeDelete(m_pPlayer);
	SafeDelete(m_pField);
	SafeDelete(m_pStore);
}


