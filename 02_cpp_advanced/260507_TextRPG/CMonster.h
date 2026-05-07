#pragma once
#include "CObj.h"
class CMonster:public CObj
{
public:
	CMonster(const char* szName, int iHp, int iAttack);
	~CMonster();

public:
	void Render()override;

	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }

};

