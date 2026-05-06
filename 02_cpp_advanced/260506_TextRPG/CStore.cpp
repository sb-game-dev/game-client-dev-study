#include "CStore.h"
#include "pch.h"
#include "Define.h"
#include "CPlayer.h"
#include "CItem.h"
CStore::CStore():m_pPlayer(nullptr)
{
	memset(m_pItem, 0, sizeof(m_pItem));
}

CStore::~CStore()
{
	Release();
}

void CStore::Initialize()
{
	m_pItem[WEAPON][NORMAL]	= new CItem("초급 검", 0, 10, 1000);
	m_pItem[WEAPON][MAGIC]	= new CItem("중급 검", 0, 20, 2000);
	m_pItem[WEAPON][RARE]	= new CItem("고급 검", 0, 30, 3000);

	m_pItem[ARMOR][NORMAL]	= new CItem("초급 옷", 10, 0, 1000);
	m_pItem[ARMOR][MAGIC]	= new CItem("중급 옷", 20, 0, 2000);
	m_pItem[ARMOR][RARE]	= new CItem("고급 옷", 30, 0, 3000);
}
void CStore::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 아이템 구매 2. 아이템 판매 3. 상점 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case BUY:
			Buy();
			break;
		case SELL:
			Sell();
			break;
		case END_STOREMENU:
			return;
		default:
			break;
		}
	}
}

void CStore::Release()
{
	for (int i = 0; i < END_IT; i++)
	{
		for (int j = 0; j < END_IC; j++)
		{
			SafeDelete(m_pItem[i][j]);
		}
	}
}
void CStore::Buy()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 초급 장비 2. 중급 장비 3. 고급 장비 4. 전 단계: ";
		cin >> iInput;
		iInput--;
		switch (iInput)
		{
		case NORMAL:
			Render(NORMAL);
			break;
		case MAGIC:
			Render(MAGIC);
			break;
		case RARE:
			Render(RARE);
			break;
		case END_IC:
			return;
		default:
			break;
		}
	}
}

void CStore::Sell()
{
	int iInput;
	CPlayer* tempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		if (tempPlayer) tempPlayer->InvRender();
		cout << "판매할 아이템 번호를 입력하세요(0: 전 단계): ";
		cin >> iInput;
		switch (iInput)
		{
		case 0:
			return;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			tempPlayer->SetMoney(m_pPlayer->GetInfo().iMoney + tempPlayer->InvDeleteItem(--iInput));
			break;
		default:
			break;
		}
	}
}

void CStore::Render(ItemClass IC)
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "==============================" << endl;
		m_pItem[WEAPON][IC]->Render();
		cout << "==============================" << endl;
		m_pItem[ARMOR][IC]->Render();
		CPlayer* tempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);
		cout << "1. 무기 구매 2. 방어구 구매 3. 전 단계: ";
		cin >> iInput;
		iInput--;
		switch (iInput)
		{
		case WEAPON:
		case ARMOR:
			if (m_pPlayer->GetInfo().iMoney >= m_pItem[iInput][IC]->GetInfo().iMoney && tempPlayer->InvAddItem(m_pItem[iInput][IC]))
			{
				if (tempPlayer)
				{
					tempPlayer->SetMoney(m_pPlayer->GetInfo().iMoney - m_pItem[iInput][IC]->GetInfo().iMoney);
					cout << "구매 완료." << endl;
					system("pause");
				}
			}
			else
			{
				cout << "잔액 혹은 인벤토리칸이 부족합니다." << endl;
				system("pause");
			}
			break;
		case END_IT:
			return;
		default:
			break;
		}
	}
}
