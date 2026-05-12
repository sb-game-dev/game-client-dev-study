#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	CObj(const char* szName,int iHp,int iAttack,int iMoney=0);
	virtual ~CObj();

public:
	virtual void Render() = 0;
	virtual const Info& GetInfo() const { return m_tInfo; }

protected:
	Info m_tInfo;
};

