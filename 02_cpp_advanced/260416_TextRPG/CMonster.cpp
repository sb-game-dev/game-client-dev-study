#include "CMonster.h"
#include "pch.h"


CMonster::CMonster(const char szName[], int iHp, int iAttack)
{
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), szName);
	m_tInfo.iAttack = iAttack;
	m_tInfo.iHp = iHp;
}
CMonster::~CMonster()
{
}

CMonster* CMonster::Create(const char szName[], int iHp, int iAttack)
{
	CMonster* p_Monster = new CMonster(szName,iHp,iAttack);
	return p_Monster;
}

void CMonster::Destroy()
{
	delete this;
}


void CMonster::Render() const
{
	cout << "========================================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}
