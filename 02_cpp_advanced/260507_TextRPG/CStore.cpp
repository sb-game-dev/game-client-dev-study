#include "CStore.h"
#include "pch.h"
#include "CItem.h"
#include "CPlayer.h"
#include "CInven.h"
CStore::CStore():m_pPlayer(nullptr), m_pInven(nullptr)
{
	memset(m_pItem, 0, sizeof(m_pItem));
}

CStore::~CStore()
{
	Release();
}

void CStore::Initialize()
{
	m_pItem[WEAPON][NORMAL]	= new CItem("초급 검", 0, 10, 1000, WEAPON);
	m_pItem[WEAPON][MAGIC]	= new CItem("중급 검", 0, 20, 2000, WEAPON);
	m_pItem[WEAPON][RARE]	= new CItem("고급 검", 0, 30, 3000, WEAPON);

	m_pItem[ARMOR][NORMAL] = new CItem("초급 옷", 10, 0, 1000, ARMOR);
	m_pItem[ARMOR][MAGIC]	= new CItem("중급 옷", 20, 0, 2000, ARMOR);
	m_pItem[ARMOR][RARE]	= new CItem("고급 옷", 30, 0, 3000, ARMOR);
}


void CStore::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 구매 2. 판매 3. 상점 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Buy();
			break;
		case 2:
			Sell();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}



void CStore::Release()
{
	for (int i = 0; i < IT_END; i++)
	{
		for (int j = 0; j < IC_END; j++)
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
		cout << "1. 초급 아이템 구매 2. 중급 아이템 구매 3. 고급 아이템 구매 4. 전 단계: ";
		cin >> iInput;
		switch (--iInput)
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
		case IC_END:
			return;
		default:
			break;
		}
	}
}

void CStore::Sell()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		m_pInven->Render();
		cout << "판매할 아이템 번호를 입력하세요(0: 전 단계): ";
		cin >> iInput;
		int iMoney = 0;
		switch (iInput)
		{
		case 0:
			return;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (m_pInven->DeleteItem(--iInput, iMoney))
				dynamic_cast<CPlayer*>(m_pPlayer)->AddMoney(iMoney);
			break;
		default:
			break;
		}
	}
}

void CStore::Render(ITEMCLASS IC)
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
		cout << "1. 무기 구매 2. 방어구 구매 3. 전 단계: ";
		cin >> iInput;
		switch (--iInput)
		{
		case WEAPON:
			if (m_pPlayer->GetInfo().iMoney >= m_pItem[WEAPON][IC]->GetInfo().iMoney
				&& m_pInven->AddItem(m_pItem[WEAPON][IC]))
			{
				dynamic_cast<CPlayer*>(m_pPlayer)->AddMoney(-m_pItem[WEAPON][IC]->GetInfo().iMoney);
				cout << "무기 구매 성공" << endl;
			}
			else cout << "잔액 혹은 인벤토리 칸이 부족합니다." << endl;
			system("pause");
			break;
		case ARMOR:
			if (m_pPlayer->GetInfo().iMoney >= m_pItem[ARMOR][IC]->GetInfo().iMoney
				&& m_pInven->AddItem(m_pItem[ARMOR][IC]))
			{
				dynamic_cast<CPlayer*>(m_pPlayer)->AddMoney(-m_pItem[ARMOR][IC]->GetInfo().iMoney);
				cout << "방어구 구매 성공" << endl;
			}
			else cout << "잔액 혹은 인벤토리 칸이 부족합니다." << endl;
			system("pause");
			break;
		case IT_END:
			return;
		default:
			break;
		}
	}
}
