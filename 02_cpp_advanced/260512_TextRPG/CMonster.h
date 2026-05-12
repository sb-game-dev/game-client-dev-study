#pragma once
#include "CObj.h"
class CMonster :public CObj
{
public:
	CMonster(const char* szName, int iHp, int iAttack);
	~CMonster();

public:
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }

	// CObj을(를) 통해 상속됨
	void Render() override;
};

