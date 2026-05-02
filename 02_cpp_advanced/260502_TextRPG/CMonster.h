#pragma once
#include "CObj.h"
class CMonster:public CObj
{
public:
	CMonster(const char* szName,int iHp,int iAttack);
	~CMonster();

public:
	void TackDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetAttack(int iNum) { m_tInfo.iMoney = iNum; }

public:
	void Render() override;
};

