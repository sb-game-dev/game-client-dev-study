#include "CMonster.h"

CMonster::CMonster(const char szName[], int iHp, int iAttack)
{
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), szName);
	m_tInfo.iHp = iHp;
	m_tInfo.iAttack = iAttack;
}

CMonster::~CMonster()
{
}
void CMonster::Initialize()
{

}
void CMonster::Render() const
{
	cout << "================================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}
CMonster* CMonster::Create(const char szName[], int iHp, int iAttack)
{
	CMonster* pMonster = new CMonster(szName, iHp, iAttack);
	return pMonster;
}

void CMonster::Destroy()
{
	delete this;
}