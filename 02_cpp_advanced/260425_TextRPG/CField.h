#pragma once
#include "CPlayer.h"
#include "CMonster.h"
class CField
{
public:
	CField();
	~CField();

public:
	void	Update();
	void	SetPlayer(CObj* pPlayer) { m_pCopyPlayer = pPlayer; }
private:
	CObj*	m_pCopyPlayer;
	CObj*	m_pMonster;

	int Battle();
};

