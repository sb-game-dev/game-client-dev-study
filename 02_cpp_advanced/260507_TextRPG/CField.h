#pragma once
#include "CMonster.h"
#include "CPlayer.h"
class CField
{
public:
	CField();
	~CField();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

	void Update();
	int Battle();
private:
	CObj* m_pPlayer;
	CObj* m_pMonster;
};

