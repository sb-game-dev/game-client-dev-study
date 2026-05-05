#include "CInventory.h"
#include "pch.h"
#include "CPlayer.h"
#include "CItem.h"
CInventory::CInventory():m_iWeaponNum(-1),m_iArmorNum(-1),m_pPlayer(nullptr)//,m_pArmorSlot(nullptr),m_pWeaponSlot(nullptr)
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
		cout << "1. 아이템 장착 2. 아이템 해제 (0: 인벤토리 나가기): " << endl;
		cin >> iInput;
		switch (iInput)
		{
		case 0:
			return;
		case 1:
			SetItem();
			break;
		case 2:
			Unequip();
			break;
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

void CInventory::SetItem()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "착용할 아이템 번호를 입력하세요(0: 전 단계): " << endl;
		cin >> iInput;
		if (!iInput) return;
		iInput--;

		if (m_vecInventoryP.size() > iInput)
		{
			if (m_vecInventoryP[iInput]->GetInfo().iAttack)
			{
				m_iWeaponNum = iInput;
				//m_pWeaponSlot = m_vecInventoryP[iInput];
			}
			else
			{
				m_iArmorNum = iInput;
				//m_pArmorSlot = m_vecInventoryP[iInput];
			}
		}
		else
		{
			cout << "비어있는 칸입니다." << endl;
			system("pause");
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
		cout << "착용해제할 아이템 번호를 입력하세요(0: 전 단계): " << endl;
		cin >> iInput;
		if (!iInput) return;
		iInput--;
		if (m_vecInventoryP.size() > iInput)
		{
			if (iInput == m_iWeaponNum)
			{
				m_iWeaponNum = -1;
				//m_pWeaponSlot = nullptr;
			}
			else if(iInput == m_iArmorNum)
			{
				m_iArmorNum = -1;
				//m_pArmorSlot = nullptr;
			}
		}
		else
		{
			cout << "비어있는 칸입니다." << endl;
			system("pause");
		}
	}
}

bool CInventory::AddItem(CObj* pItem)
{
	if (m_vecInventoryP.size() >= 5)
	{
		return false;
	}
	m_vecInventoryP.push_back(new CItem(*pItem));
	return true;
}

int CInventory::DeleteItem(int iIndex)
{
	if (iIndex < m_vecInventoryP.size())
	{
		auto it = m_vecInventoryP.begin() + iIndex;
		int iMoney = (*it)->GetInfo().iMoney;
		SafeDelete((*it));
		m_vecInventoryP.erase(it);

		if (m_iArmorNum > iIndex) m_iArmorNum--;
		else if (m_iArmorNum == iIndex) m_iArmorNum = -1;
		if (m_iWeaponNum > iIndex)m_iWeaponNum--;
		else if (m_iWeaponNum == iIndex) m_iWeaponNum = -1;

		return iMoney;
	}
	else
	{
		cout << "비어있는 칸입니다." << endl;
		system("pause");
		return 0;
	}
}

void CInventory::Render()
{
	cout << "==============================" << endl;
	if (m_iWeaponNum>=0) m_vecInventoryP[m_iWeaponNum]->Render();
	else cout << "비어있음" << endl;
	cout << "==============================" << endl;
	if (m_iArmorNum>=0) m_vecInventoryP[m_iArmorNum]->Render();
	else cout << "비어있음" << endl;
	cout << "==============================" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "<" << i + 1 << "번칸>";
		if (m_vecInventoryP.size() > i)
		{
			if (m_iArmorNum == i || m_iWeaponNum == i) cout << "\t(장착중)" << endl;
			else cout << endl;
			m_vecInventoryP[i]->Render();
		}
		else cout << "비어있음" << endl;
	}
}

CObj* CInventory::GetWeapon()
{
	if (m_iWeaponNum >= 0) return m_vecInventoryP[m_iWeaponNum]; 
	return nullptr;
}

CObj* CInventory::GetArmor()
{
	if (m_iArmorNum >= 0) return m_vecInventoryP[m_iArmorNum];
	return nullptr;
}
