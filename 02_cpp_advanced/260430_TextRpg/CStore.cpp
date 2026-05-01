#include "CStore.h"
#include "pch.h"
#include "CObj.h"
#include "CItem.h"
#include "CPlayer.h"
#include"CInventory.h"
CStore::CStore() :m_pPlayer(nullptr), m_Inventory(nullptr)
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
		cout << "1. 구매 2. 판매 3. 상점 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Purchase();
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
	for (int i = 0; i < END_IT; i++)
	{
		for (int j = 0; j < END_IC; j++)
		{
			SafeDelete(m_pItem[i][j]);
		}
	}
}

void CStore::Purchase()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 초급 2. 중급 3. 고급 4. 상점 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Render(NORMAL);
			break;
		case 2:
			Render(MAGIC);
			break;
		case 3:
			Render(RARE);
			break;
		case 4:
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
		m_Inventory->Render();
		cout << "판매할 아이템 번호를 입력하세요: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			m_Inventory->SellItem(iInput);
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
		
		CPlayer* tempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);

		int iWeaponMoney = m_pItem[WEAPON][IC]->GetInfo().iMoney;
		int iArmorMoney = m_pItem[ARMOR][IC]->GetInfo().iMoney;

		system("cls");
		m_pPlayer->Render();
		cout << "==================================" << endl;
		m_pItem[WEAPON][IC]->Render();
		cout << "==================================" << endl;
		m_pItem[ARMOR][IC]->Render();
		cout << "1. 무기 구매 2. 방어구 구매 3. 전 단계: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			if (m_pPlayer->GetInfo().iMoney >= iWeaponMoney && m_Inventory->AddItem(m_pItem[WEAPON][IC]))
			{
				tempPlayer->SetMoney(m_pPlayer->GetInfo().iMoney - iWeaponMoney);
				cout << "무기 구매 성공!" << endl;
			}
			else
			{
				cout << "소지금 또는 인벤토리 칸을 확인하세요." << endl;
			}
			system("pause");
			break;
		case 2:
			if (m_pPlayer->GetInfo().iMoney >= iArmorMoney && m_Inventory->AddItem(m_pItem[ARMOR][IC]))
			{
				tempPlayer->SetMoney(m_pPlayer->GetInfo().iMoney - iArmorMoney);
				cout << "방어구 구매 성공!" << endl;
			}
			else
			{
				cout << "소지금 또는 인벤토리 칸을 확인하세요." << endl;
			}
			system("pause");
			break;
		case 3:
			return;
		default:
			break;
		}
	}

}
