#pragma once
#include "Define.h"
class CObj;
class CStore
{
public:
	CStore();
	~CStore();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void Initialize();
	void Update();
	void Release();
	void Render(ITEMCLASS IC);
private:
	CObj* m_pPlayer;
	CObj* m_pItem[END_IT][END_IC];
};

