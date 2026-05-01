#pragma once
#include "pch.h"
class CObj;
class CInventory
{
public:
	CInventory();
	~CInventory();

public:
	void Initialize();
	void Update();
	void Release();

	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	bool AddItem(CObj* pItem);
	void SellItem(int iNum);
	void Render();
	void SetItem();
	//void SetWeapon();
	//void SetArmor();
private:
	CObj* m_pPlayer;
	vector<CObj*> m_vecInventoryP;
	CObj* m_pWeaponSlot;
	CObj* m_pArmorSlot;
};

