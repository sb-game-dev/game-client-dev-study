#include "CObj.h"
#include "pch.h"
CObj::CObj(const char* szName, int iHp, int iAttack, int iMoney)
{
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), szName);
	m_tInfo.iHp = iHp;
	m_tInfo.iAttack = iAttack;
	m_tInfo.iMoney = iMoney;
}
