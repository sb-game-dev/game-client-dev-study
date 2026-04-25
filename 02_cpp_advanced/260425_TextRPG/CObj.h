#pragma once
#include "Define.h"
class CObj abstract
{
public:
	CObj() {}
	CObj(const char* szName, int iHp, int iAttack, int iMoney=0);
	virtual ~CObj() {};

public:
	virtual void Render() = 0;
	virtual void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	virtual Info GetInfo() { return m_tInfo; }
protected:
	Info m_tInfo;
};

