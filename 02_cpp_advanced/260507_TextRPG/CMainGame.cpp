#include "CMainGame.h"
#include "Define.h"
#include "pch.h"
#include "CPlayer.h"
#include "CField.h"
#include "CStore.h"
#include "CInven.h"
CMainGame::CMainGame() : m_pPlayer(nullptr),m_pField(nullptr),m_pStore(nullptr), m_pInven(nullptr)
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
		dynamic_cast<CPlayer*> (m_pPlayer)->SelectJob();
	}
	
	if (!m_pField)
	{
		m_pField = new CField;
		m_pField->SetPlayer(m_pPlayer);
	}
	if (!m_pStore)
	{
		m_pStore = new CStore;
		m_pStore->Initialize();
		m_pStore->SetPlayer(m_pPlayer);
	}
	if (!m_pInven)
	{
		m_pInven = new CInven;
		m_pInven->SetPlayer(m_pPlayer);
	}
	m_pStore->SetInven(m_pInven);
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
		case 1:
			if (m_pField)m_pField->Update();
			break;
		case 2:
			if (m_pStore)m_pStore->Update();
			break;
		case 3:
			if (m_pInven)m_pInven->Update();
			break;
		case 4:
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
	SafeDelete(m_pInven);
}
