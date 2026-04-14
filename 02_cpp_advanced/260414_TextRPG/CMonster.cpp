#include "CMonster.h"
#include "pch.h"
CMonster::CMonster(const char* tempName, int tempHp, int tempAttack)
{
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), tempName);
	m_tInfo.iHp = tempHp;
	m_tInfo.iAttack = tempAttack;
}
CMonster::~CMonster()
{
}

void CMonster::Render()
{
	cout << "========================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}
