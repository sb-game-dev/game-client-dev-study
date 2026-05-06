#include "CInventory.h"
#include "pch.h"
#include "CObj.h"
#include "CItem.h"
CInventory::CInventory():m_pPlayer(nullptr),m_iArmorNum(-1),m_iWeaponNum(-1)
{
}

CInventory::~CInventory()
{
	Release();
}

void CInventory::Update()
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
			SetItem();
			break;
		case 2:
			Unequip();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void CInventory::Release()
{
	for (auto it = m_vecInventoryP.begin();
		it != m_vecInventoryP.end();
		)
	{
		SafeDelete(*it);
		it = m_vecInventoryP.erase(it);
	}
}

void CInventory::Render()
{
	cout << "==============================" << endl;
	cout << "<무기 슬롯>" << endl;
	if (m_iWeaponNum >= 0) m_vecInventoryP[m_iWeaponNum]->Render();
	else cout << "비어있음" << endl;
	cout << "<방어구 슬롯>" << endl;
	if (m_iArmorNum >= 0) m_vecInventoryP[m_iArmorNum]->Render();
	else cout << "비어있음" << endl;
	cout << "==============================" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "<" << i + 1 << "번칸>";
		if (i < m_vecInventoryP.size())
		{
			if (i == m_iWeaponNum || i == m_iArmorNum) cout << "(장착중)" << endl;
			else cout << endl;

			m_vecInventoryP[i]->Render();
		}
		else cout << "\n비어있음" << endl;
	}
}
bool CInventory::AddItem(CObj* pItem)
{
	if (m_vecInventoryP.size() >= 5) return false;

	m_vecInventoryP.push_back(new CItem(*pItem));
	return true;
}

int CInventory::DeleteItem(int iIndex)
{
	if (iIndex < m_vecInventoryP.size())
	{
		if (iIndex == m_iWeaponNum) m_iWeaponNum = -1;
		else if (iIndex == m_iArmorNum) m_iArmorNum = -1;

		if (iIndex < m_iWeaponNum) m_iWeaponNum--;
		else if (iIndex < m_iArmorNum) m_iArmorNum--;

		auto it = m_vecInventoryP.begin() + iIndex;
		int iMoney = (*it)->GetInfo().iMoney;
		SafeDelete(*it);
		m_vecInventoryP.erase(it);
		return iMoney;
	}
	else
	{
		cout << "비어있는 칸입니다." << endl;
		system("pause");
		return 0;
	}
}

void CInventory::SetItem()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "장착할 아이템 번호를 입력하세요(0: 전 단계): ";
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
			if (iInput <= m_vecInventoryP.size())
			{
				if (m_vecInventoryP[--iInput]->GetInfo().iAttack)m_iWeaponNum = iInput;
				else m_iArmorNum = iInput;
			}
			else
			{
				cout << "비어있는 칸입니다." << endl;
				system("pause");
			}
			break;
		default:
			break;
		}
	}
}

void CInventory::Unequip()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "장착할 아이템 번호를 입력하세요(0: 전 단계): ";
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
			if (iInput <= m_vecInventoryP.size())
			{
				if (iInput-1 == m_iWeaponNum)m_iWeaponNum = -1;
				else if(iInput - 1 == m_iArmorNum )m_iArmorNum = -1;
			}
			else
			{
				cout << "비어있는 칸입니다." << endl;
				system("pause");
			}
			break;
		default:
			break;
		}
	}
}

int CInventory::GetWeaponSlot()
{
	if (m_iWeaponNum >= 0) return m_vecInventoryP[m_iWeaponNum]->GetInfo().iAttack;
	return 0;
}

int CInventory::GetArmorSlot()
{
	if (m_iArmorNum >= 0) return m_vecInventoryP[m_iArmorNum]->GetInfo().iHp;
	return 0;
}



