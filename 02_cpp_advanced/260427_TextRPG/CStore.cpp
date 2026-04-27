#include "CStore.h"
#include"pch.h"
#include"CObj.h"
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
	m_pItem[WEAPON][NORMAL] = new CItem("초급검", 0, 10, 1000);
	m_pItem[WEAPON][MAGIC] = new CItem("중급검", 0, 20, 2000);
	m_pItem[WEAPON][RARE] = new CItem("고급검", 0, 30, 3000);

	m_pItem[ARMOR][NORMAL] = new CItem("초급옷", 10, 0, 1000);
	m_pItem[ARMOR][MAGIC] = new CItem("중급옷", 20, 0, 2000);
	m_pItem[ARMOR][RARE] = new CItem("고급옷", 30, 0, 3000);
}
void CStore::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1.초급 2.중급 3.고급 4.상점 나가기: ";
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

void CStore::Release()
{
	for (int i = 0; i < END_IT; i++)
	{
		for (int j = 0; j < END_IC; j++)
		{
			SAFE_DELETE(m_pItem[i][j]);
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
		m_pItem[WEAPON][IC]->Render();
		m_pItem[ARMOR][IC]->Render();
		int iPlayerMoney = m_pPlayer->GetInfo().iMoney;
		int iWeaponMoney = m_pItem[WEAPON][IC]->GetInfo().iMoney;
		int iArmorMoney = m_pItem[ARMOR][IC]->GetInfo().iMoney;
		cout << "1.무기 구매 2.갑옷 구매 3.전 단계: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			if (iPlayerMoney >= iWeaponMoney)
			{
				cout << "검 구매" << endl;
				system("pause");
			}
			else
			{
				cout << "소지금이 부족합니다." << endl;
				system("pause");
			}
			break;
		case 2:
			if (iPlayerMoney >= iArmorMoney)
			{
				cout << "갑옷 구매" << endl;
				system("pause");
			}
			else
			{
				cout << "소지금이 부족합니다." << endl;
				system("pause");
			}
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}
