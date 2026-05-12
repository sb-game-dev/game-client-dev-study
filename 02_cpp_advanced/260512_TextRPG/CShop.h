#pragma once
#include "Define.h"
class CObj;
class CShop
{
public :
	CShop();
	~CShop();

public :
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

	void Initialize();
	void Update();
	void Release();

	void Buy();
	void Sell();

	void RenderAndBuy(ITEMCLASS);

private:
	CObj* m_pPlayer;
	CObj* m_pItem[IT_END][IC_END];
};

