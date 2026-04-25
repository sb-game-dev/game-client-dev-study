#include "CMainGame.h"
#include"pch.h"
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

void CMainGame::Initialize()
{
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		((CPlayer*)m_pPlayer)->Initialize();
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
			m_pStore->Update();
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
	SAFE_DELETE(m_pField);
	SAFE_DELETE(m_pStore);
	SAFE_DELETE(m_pPlayer);
}
