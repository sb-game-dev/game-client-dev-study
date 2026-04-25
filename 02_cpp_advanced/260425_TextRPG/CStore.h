#pragma once
#include "CPlayer.h"
#include "Define.h"
#include "CItem.h"
class CStore
{
public:
	CStore();
	~CStore();

public:
	void	Initialize();
	void	Update();
	void	SetPlayer(CObj* pPlayer) { m_pCopyPlayer = pPlayer; }
private:
	CObj* m_pCopyPlayer;
	CObj* m_pItem[END_ITEMTYPE][END_ITEMCLASS];

private:
	void Render(ItemClass IC);
};

