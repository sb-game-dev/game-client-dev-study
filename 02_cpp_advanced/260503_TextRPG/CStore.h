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
	void Initialize();
	void Update();
	void Release();

	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

private:
	void Buy();
	void Sell();

	void Render(ItemClass IC);

private:
	CObj* m_pPlayer;
	CObj* m_pItem[END_IT][END_IC];
};

