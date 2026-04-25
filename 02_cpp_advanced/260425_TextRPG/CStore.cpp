#include "CStore.h"
#include "pch.h"
CStore::CStore() :m_pCopyPlayer(nullptr)
{
	memset(m_pItem, 0, sizeof(m_pItem));
}

CStore::~CStore()
{
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
		m_pCopyPlayer->Render();
		cout << "1.초급 2. 중급 3. 고급 4. 상점 나가기: ";
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

void CStore::Render(ItemClass IC)
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pCopyPlayer->Render();
		m_pItem[0][IC]->Render();
		m_pItem[1][IC]->Render();
		int iPlayerMoney = m_pCopyPlayer->GetInfo().iMoney;
		int iWeaponMoney = m_pItem[0][IC]->GetInfo().iMoney;
		int iArmorMoney = m_pItem[1][IC]->GetInfo().iMoney;
		cout << "1. 무기구매 2. 방어구 구매 3.전 단계: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			if (iPlayerMoney >= iWeaponMoney)
			{
				cout << "구매 완료" << endl;
				((CPlayer*)m_pCopyPlayer)->SetMoney(iPlayerMoney - iWeaponMoney);
				((CPlayer*)m_pCopyPlayer)->SetAttack(m_pItem[0][IC]->GetInfo().iAttack);
			}
			else
			{
				cout << "소지금이 부족합니다." << endl;
			}
			system("pause");
			break;
		case 2:
			if (iPlayerMoney >= iArmorMoney)
			{
				cout << "구매 완료" << endl;
				((CPlayer*)m_pCopyPlayer)->SetMoney(iPlayerMoney - iArmorMoney);
				((CPlayer*)m_pCopyPlayer)->SetAttack(m_pItem[1][IC]->GetInfo().iAttack);
			}
			else
			{
				cout << "소지금이 부족합니다." << endl;
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
