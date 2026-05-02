#pragma once
#include"Define.h"
class CObj;
class CInventory;
class CStore
{
public:
	CStore();
	~CStore();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void SetInventory(CInventory* pInventory) { m_pInventory = pInventory; }
	void Initialize();
	void Update();
	void Release();
	void Purchase();
	void Sale();
	void Render(ITEMCLASS IC);

private:
	CObj* m_pPlayer;
	CInventory* m_pInventory;
	CObj* m_pItem[END_IT][END_IC];
};

