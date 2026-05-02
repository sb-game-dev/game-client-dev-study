#include "CInventory.h"
#include "CItem.h"
#include "CPlayer.h"
#include "pch.h"
CInventory::CInventory() :m_WeaponSlot(nullptr), m_ArmorSlot(nullptr), m_iArmorNum(-1), m_iWeaponNum(-1),m_pPlayer(nullptr)
{
	//for (int i = 0; i < 5; i++)
	//{
	//	m_vecInventoryP.push_back(nullptr);
	//}
}

CInventory::~CInventory()
{
	Release();
}
void CInventory::Initialize()
{
	
}
void CInventory::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		Render();
		cout << "착용하실 아이템의 칸을 입력하거나 (0: 인벤토리 나가기): ";
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
			SetItem(iInput - 1);
			break;
		default:
			break;
		}
	}
}

void CInventory::Release()
{
	m_WeaponSlot = nullptr;
	m_ArmorSlot = nullptr;
	for (auto it = m_vecInventoryP.begin();
		it != m_vecInventoryP.end();
		)
	{
		SafeDelete(*it);
		it = m_vecInventoryP.erase(it);
	}
}
bool CInventory::AddItem(CObj* pItem)
{
	if (m_vecInventoryP.size() < 5)
	{
		m_vecInventoryP.push_back(new CItem(*pItem));
		return true;
	}
	else
	{
		return false;
	}
}

void CInventory::DeleteItem(int iNum)
{
	if (iNum >= m_vecInventoryP.size())
	{
		cout << "아이템이 비어있습니다." << endl;
		system("pause");
		return;
	}
	if (iNum == m_iArmorNum)
	{
		((CPlayer*)m_pPlayer)->SetMaxHp(100);
		m_ArmorSlot = nullptr;
		m_iArmorNum = -1;
	}
	else if (iNum == m_iWeaponNum)
	{
		((CPlayer*)m_pPlayer)->SetAttack(10);
		m_WeaponSlot = nullptr;
		m_iWeaponNum = -1;
	}

	if (iNum < m_iWeaponNum) m_iWeaponNum--;
	if (iNum < m_iArmorNum) m_iArmorNum--;
	((CPlayer*)m_pPlayer)->SetMoney(m_pPlayer->GetInfo().iMoney + this->m_vecInventoryP[iNum]->GetInfo().iMoney);
	auto it = m_vecInventoryP.begin() + iNum;
	SafeDelete(*it);
	m_vecInventoryP.erase(it);
}

void CInventory::SetItem(int iNum)
{
	if (m_vecInventoryP.size()>iNum)
	{
		if (m_vecInventoryP[iNum]->GetInfo().iHp)
		{
			((CPlayer*)m_pPlayer)->SetMaxHp(100 + m_vecInventoryP[iNum]->GetInfo().iHp);
			m_iArmorNum = iNum;
			m_ArmorSlot = m_vecInventoryP[iNum];
		}
		else
		{
			((CPlayer*)m_pPlayer)->SetAttack(10 + m_vecInventoryP[iNum]->GetInfo().iAttack);
			m_iWeaponNum = iNum;
			m_WeaponSlot = m_vecInventoryP[iNum];
		}
	}
	else
	{
		cout << "인벤토리가 비어있습니다." << endl;
		system("pause");
		return;
	}
}

void CInventory::Render()
{
	m_pPlayer->Render();
	cout << "================<무기 슬롯>==============" << endl;
	if(m_WeaponSlot) m_WeaponSlot->Render();
	else cout << "비어있습니다." << endl;

	cout << "================<방어구 슬롯>==============" << endl;
	if(m_ArmorSlot) m_ArmorSlot->Render();
	else cout << "비어있습니다." << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "================<"<<i+1<<"번째 칸>==============" << endl;
		
		if (i<m_vecInventoryP.size())
		{
			if (m_iArmorNum == i || m_iWeaponNum == i)cout << "(장착중)" << endl;
			m_vecInventoryP[i]->Render();
		}
		else
		{
			cout << "비어있습니다." << endl;
		}
	}
}
