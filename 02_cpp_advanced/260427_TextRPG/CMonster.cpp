#include "CMonster.h"
#include "pch.h"
CMonster::CMonster(const char* szname, int iHp, int iAttack)
	:CObj(szname,iHp,iAttack)
{
}
void CMonster::Render()
{
	cout << "====================================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}
