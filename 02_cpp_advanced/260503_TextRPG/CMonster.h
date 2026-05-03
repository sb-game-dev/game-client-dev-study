#pragma once
#include "CObj.h"
class CMonster:public CObj
{
public:
	CMonster(const char* szName, int iHp, int iAttack);
	~CMonster();

public:
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetHp(int iNum) { m_tInfo.iHp = iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }
	void TackDamage(int iNum) { m_tInfo.iHp -= iNum; }

	void Render() override;

};

