#pragma once
#include "CObj.h"
class CMonster:public CObj
{
public:
	CMonster(const char* szname, int iHp, int iAttack);
public:
	void Render() override;
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
};

