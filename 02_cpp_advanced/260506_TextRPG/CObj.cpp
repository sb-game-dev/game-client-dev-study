#include "CObj.h"
#include "pch.h"
CObj::CObj(const char* szName, int iHp, int iAttack, int iMoney)
{
	m_tInfo = { iHp,iHp,iAttack,iMoney };
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), szName);
}

CObj::~CObj()
{
}
