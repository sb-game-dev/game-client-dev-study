#include "CMonster.h"
#include "pch.h"
CMonster::CMonster(const char szName[], int iHp, int iAttack)
{
	strcpy_s(m_szName, sizeof(m_szName), szName);
	m_iAttack = iAttack;
	m_iHp = iHp;
}

CMonster::~CMonster()
{
}

CMonster* CMonster::Create(const char szName[], int iHp, int iAttack)
{
	CMonster* pObj = new CMonster(szName,iHp,iAttack);
	return pObj;
}


void CMonster::Destroy()
{
	delete this;
}