#pragma once
#include <vector>
using namespace std;
class CObj;
class CInventory
{
public:
	CInventory();
	~CInventory();

public:
	void Update();
	void Release();

	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void SetItem();
	void Unequip();

	bool AddItem(CObj* pItem);
	int DeleteItem(int iIndex);
	void Render();

	CObj* GetWeapon();
	CObj* GetArmor();

private:
	vector<CObj*> m_vecInventoryP;
	CObj* m_pPlayer;
	//CObj* m_pWeaponSlot;
	//CObj* m_pArmorSlot;
	int m_iWeaponNum;
	int m_iArmorNum;
};

