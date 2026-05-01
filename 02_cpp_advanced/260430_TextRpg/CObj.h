#pragma once
#include "Define.h"
class CObj abstract
{
public:
	CObj();
	CObj(const char* szName,int iHp,int iAttack, int iMoney=0);
	virtual ~CObj();

public:
	virtual void Render() = 0;
	virtual Info GetInfo() = 0;
protected:
	Info m_tInfo;
};

