#pragma once
#include "Define.h"
class CObj abstract
{
public:
	CObj() {}
	CObj(const char* szName,int iHp,int iAttack,int iMoney=0);
	virtual~CObj() {}

public:
	virtual void Render() = 0;
	virtual Info GetInfo() { return m_tInfo; }
	virtual void TakeDamage(int iNum) {};
protected:
	Info m_tInfo;
};

