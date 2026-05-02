#pragma once
#include <vector>
class CObj;
class CInventory
{
public:
	CInventory();
	~CInventory();

public:
	friend class CStore;
	void Initialize();
	void Update();
	void Release();

	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	bool AddItem(CObj* pItem);
	void DeleteItem(int iNum);
	void SetItem(int iNum);
	void Render();

private:
	std::vector<CObj*> m_vecInventoryP;

	CObj* m_WeaponSlot;
	CObj* m_ArmorSlot;
	CObj* m_pPlayer;

	int m_iWeaponNum;
	int m_iArmorNum;
};

