#include "CMainGame.h"
#include "pch.h"
#include "Define.h"
#include "CPlayer.h"
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
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer();
		dynamic_cast<CPlayer*> (m_pPlayer)->SelectJob();
	}
	if (!m_pField)
	{
		m_pField = new CField();
		m_pField->SetPlayer(m_pPlayer);
	}
	if (!m_pShop)
	{
		m_pShop = new CShop();
		m_pShop->Initialize();
		m_pShop->SetPlayer(m_pPlayer);
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
		case 1:
			if (m_pField) m_pField->Update();
			break;
		case 2:
			if (m_pShop) m_pShop->Update();
			break;
		case 3:
			if (m_pPlayer) dynamic_cast<CPlayer*>(m_pPlayer)->GetInven().Update();
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
	Safe_Delete(m_pPlayer);
	Safe_Delete(m_pField);
	Safe_Delete(m_pShop);
}
