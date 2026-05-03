#include "CInventory.h"
#include "CPlayer.h"
#include "CItem.h"
#include "CObj.h"
CInventory::CInventory(): m_pArmorSlot(nullptr),m_pWeaponSlot(nullptr), m_iArmorIndex(-1), m_iWeaponIndex(-1)
{
}

CInventory::~CInventory()
{
	
}
void CInventory::Release()
{
	if (m_vecInventoryP.size() < 1)return;
	for (auto it = m_vecInventoryP.begin();
		it != m_vecInventoryP.end();)
	{
		SafeDelete(*it);
		it = m_vecInventoryP.erase(it);
	}
}

void CInventory::Render()
{
	cout << "==============================" << endl;
	cout << "<무기 슬롯>" << endl;
	if (m_pWeaponSlot)m_pWeaponSlot->Render();
	else cout << "비어있음" << endl;
	cout << "<방어구 슬롯>" << endl;
	if (m_pArmorSlot)m_pArmorSlot->Render();
	else cout << "비어있음" << endl;

	cout << "==============================" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (m_vecInventoryP.size() > i)
		{
			cout << "<" << i + 1 << "번째 칸 ";
			if (i == m_iArmorIndex || i == m_iWeaponIndex) cout << "(장착중)>" << endl;
			else cout <<">" << endl;
			m_vecInventoryP[i]->Render();
		}
		else cout << "<" << i + 1 << "번째 칸>" << endl << "비어있음" << endl;
	}
}

void CInventory::PushItem(const CObj* pItem)
{
	m_vecInventoryP.push_back(new CItem(*pItem)); 
}

void CInventory::SetItem(int iIndex)
{
	if (m_vecInventoryP[iIndex]->GetInfo().iHp)
	{
		m_pArmorSlot = m_vecInventoryP[iIndex];
		m_iArmorIndex = iIndex;
	}
	else if (m_vecInventoryP[iIndex]->GetInfo().iAttack)
	{
		m_pWeaponSlot = m_vecInventoryP[iIndex];
		m_iWeaponIndex = iIndex;
	}
}

void CInventory::DeleteItem(int iIndex)
{
	auto it = m_vecInventoryP.begin() + iIndex;
	if (iIndex == m_iArmorIndex)
	{
		m_pArmorSlot = nullptr;
		m_iArmorIndex = -1;
	}
	else if (iIndex == m_iWeaponIndex)
	{
		m_pWeaponSlot = nullptr;
		m_iWeaponIndex = -1;
	}
	if (iIndex < m_iArmorIndex) m_iArmorIndex--;
	if (iIndex < m_iWeaponIndex)m_iWeaponIndex--;
	SafeDelete((*it));
	m_vecInventoryP.erase(it);
}
