#pragma once
#include "CObj.h"
class CMonster:public CObj
{
public:
	CMonster(const char* szName, int iHp, int iAttack);
	~CMonster()override;

public:
	// CObj을(를) 통해 상속됨
	void Render() override;
	void TakeDamage(int iNum) override { m_tInfo.iHp -= iNum; };

};

