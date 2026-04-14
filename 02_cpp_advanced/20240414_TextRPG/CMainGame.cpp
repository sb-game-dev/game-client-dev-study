#include "CMainGame.h"
#include "pch.h"
#include "CPlayer.h"
#include "Define.h"
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
	m_pPlayer = new CPlayer;
	m_pPlayer->Initialize();
	m_pField = new CField;
}


void CMainGame::Update()
{
	int iInput;
	while (true)
	{
		m_pPlayer->Render();
		cout << "1.사냥터 2. 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_pField->SetPlayer(m_pPlayer);
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
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pField);
}

