#include "CMonster.h"
#include "pch.h"
CMonster::CMonster(const char* szName, int iHp, int iAttack)
	:CObj(szName,iHp,iAttack)
{
}

CMonster::~CMonster()
{
}

void CMonster::Render()
{
	cout << "==============================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "/" << m_tInfo.iMaxHp << "\t공격력: " << m_tInfo.iAttack << endl;
}
