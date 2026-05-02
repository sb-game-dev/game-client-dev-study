#include "pch.h"
#include "Define.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CField.h"
#include "CStore.h"
#include "CInventory.h"
CMainGame::CMainGame() :m_pPlayer(nullptr),m_pField(nullptr),m_pStore(nullptr),m_pInventory(nullptr)
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
		CPlayer* pTempPlayer = dynamic_cast<CPlayer*> (m_pPlayer);
		if (pTempPlayer)
		{
			pTempPlayer->SelectJob();
		}
	}
	if (!m_pInventory)
	{
		m_pInventory = new CInventory;
		m_pInventory->SetPlayer(m_pPlayer);
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
		m_pStore->SetInventory(m_pInventory);
		m_pStore->Initialize();
	}
}



void CMainGame::Update()
{
	int iInput;
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
			m_pInventory->Update();
			break;

		case GAMEOVER:
			return;
		default:
			break;
		}
	}
}



void CMainGame::Release()
{
	SafeDelete(m_pField);
	SafeDelete(m_pStore);
	SafeDelete(m_pInventory);
	SafeDelete(m_pPlayer);
}
