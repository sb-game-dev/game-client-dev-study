#pragma once
#include "Define.h"
class CItem;
class CObj;
class CStore
{
public:
	CStore();
	~CStore();

public:
	void SetPlayer(CObj* pPlayer) { m_pCopyPlayer = pPlayer; }
	void Update();
	void Release();
private:
	CObj* m_pCopyPlayer;
	CObj* m_pItem[IT_END][IC_END];

	void Render(ItemClass ItClass);
};

