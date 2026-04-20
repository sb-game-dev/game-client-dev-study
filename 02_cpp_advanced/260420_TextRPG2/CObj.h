#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	CObj(const char* szName,int iHp, int iAttack, int iGold = 0);
	~CObj();
	virtual void Render();
	virtual Info GetInfo() { return m_tInfo; }
	virtual void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
protected:
	Info m_tInfo;
};

