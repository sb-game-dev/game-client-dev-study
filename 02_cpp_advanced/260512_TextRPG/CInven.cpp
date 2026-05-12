#include "CInven.h"
#include "CItem.h"
#include "CPlayer.h"
#include "pch.h"
#include "algorithm"
CInven::CInven():iSize(5)
{
	m_pPlayer = nullptr;
	m_vecInvenP.reserve(5);
}

CInven::~CInven()
{
	Release();
}
void CInven::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "1. 아이템 장착 2. 아이템 해제 3. 인벤토리 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			EquipItem();
			break;
		case 2:
			UnEquipItem();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}
void CInven::Release()
{
	for (auto pItem : m_vecInvenP)
	{
		Safe_Delete(pItem);
	}
	m_vecInvenP.clear();
}
void CInven::Render()
{
	for (int i = 0; i < iSize; i++)
	{
		if (i < m_vecInvenP.size())
			m_vecInvenP[i]->Render();
		else
		{
			cout << "==============================" << endl;
			cout << "비어있습니다." << endl;
		}
	}
}
bool CInven::AddItem(CObj* pItem)
{
	if (m_vecInvenP.size() >= 5) return false;

	m_vecInvenP.push_back(new CItem(*pItem));
	return true;
}

int CInven::DeleteItem(int iNum)
{
	if (iNum >= m_vecInvenP.size())
		return 0;
	int iReturn = 0;
	auto iter = m_vecInvenP.begin() + iNum;
	if (dynamic_cast<CItem*>(*iter)->GetItemState() == EQUIP)
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->PlayerStat(-(*iter)->GetInfo().iHp, -(*iter)->GetInfo().iAttack);
	}
	iReturn = (*iter)->GetInfo().iMoney / 2;
	Safe_Delete(*iter);
	m_vecInvenP.erase(iter);
	return iReturn;
}

void CInven::EquipItem()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "착용할 아이템 번호를 입력하세요(0: 전 단계): ";
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
			if (--iInput >= m_vecInvenP.size())
			{
				cout << "비어있는 칸입니다." << endl;
				system("pause");
			}
			else
			{
				dynamic_cast<CPlayer*>(m_pPlayer)->Equip(m_vecInvenP[iInput]);
			}
			break;
		default:
			break;
		}
	}
}

void CInven::UnEquipItem()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "해제할 아이템 번호를 입력하세요(0: 전 단계): ";
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
			if (--iInput >= m_vecInvenP.size())
			{
				cout << "비어있는 칸입니다." << endl;
				system("pause");
			}
			else if (dynamic_cast<CItem*>(m_vecInvenP[iInput])->GetItemState() == UNEQUP)
			{
				cout << "착용하고있는 아이템이 아닙니다." << endl;
				system("pause");
			}
			else
			{
				dynamic_cast<CPlayer*>(m_pPlayer)->Unequip(m_vecInvenP[iInput]);
			}
			break;
		default:
			break;
		}
	}
}
