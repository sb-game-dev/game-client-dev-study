#pragma once
#include "Define.h"
class CObj;
class CInven;
class CStore
{
public:
	CStore();
	~CStore();

public :
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void SetInven(CInven* pInven) { m_pInven = pInven; }

	void Initialize();
	void Update();
	void Release();

private:
	void Buy();
	void Sell();

	void Render(ITEMCLASS IC);
private:
	CObj* m_pPlayer;
	CObj* m_pItem[IT_END][IC_END];
	CInven* m_pInven;
};

