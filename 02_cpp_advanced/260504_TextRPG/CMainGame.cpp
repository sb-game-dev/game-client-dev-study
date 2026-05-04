#include "CMainGame.h"
#include "Define.h"
#include "pch.h"
#include "CPlayer.h"
#include "CField.h"
CMainGame::CMainGame():m_pPlayer(nullptr),m_pField(nullptr),m_pStore(nullptr)
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
		CPlayer* tempPlayer = dynamic_cast<CPlayer*> (m_pPlayer);
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
			break;
		case INVENTORY:
			break;
		case END_GAMEMENU:
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
	SafeDelete(m_pPlayer);
}
