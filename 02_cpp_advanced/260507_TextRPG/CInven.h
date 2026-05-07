#pragma once
#include "pch.h"
class CObj;
class CInven
{
public:
	CInven();
	~CInven();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

	void Initialize();
	void Update();
	void Release();

	void Render();

	bool AddItem(CObj* pitem);
	bool DeleteItem(int iInput, int& iMoney);

	void Equip();
	void UnEquip();

private:
	CObj* m_pPlayer;
	vector<CObj*> m_vecInvenP;
	const int m_iSize;
};

