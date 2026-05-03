#pragma once
#include "pch.h"
class CObj;
class CInventory
{
public:
	CInventory();
	~CInventory();

public:
	void Release();
	
	void Render();
	size_t  GetSize() { return m_vecInventoryP.size(); }
	void PushItem(const CObj* pItem);
	void SetItem(int iIndex);
	void DeleteItem(int iIndex);
	CObj* GetArmorSlot() { return m_pArmorSlot; }
	CObj* GetWeaponSlot() { return m_pWeaponSlot; }
private:
	vector<CObj*> m_vecInventoryP;
	CObj* m_pWeaponSlot;
	CObj* m_pArmorSlot;
	int m_iWeaponIndex;
	int m_iArmorIndex;
};

