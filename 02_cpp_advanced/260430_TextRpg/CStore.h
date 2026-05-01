#pragma once
#include "Define.h"
class CObj;
class CInventory;
class CStore
{
public:
	CStore();
	~CStore();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void SetInventory(CInventory* pInven) { m_Inventory = pInven; }
	void Initialize();
	void Update();
	void Release();
	void Purchase();
	void Sell();
	void Render(ITEMCLASS IC);
private:
	CObj* m_pPlayer;
	CObj* m_pItem[END_IT][END_IC];
	CInventory* m_Inventory;
};

