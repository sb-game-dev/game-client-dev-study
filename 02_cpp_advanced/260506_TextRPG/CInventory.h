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
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

	void Update();
	void Release();

	void Render();

	bool AddItem(CObj* pItem);
	int DeleteItem(int iIndex);

	void SetItem();
	void Unequip();

	int GetWeaponSlot();
	int GetArmorSlot();
private:
	vector<CObj*> m_vecInventoryP;
	CObj* m_pPlayer;
	int m_iWeaponNum;
	int m_iArmorNum;
};

