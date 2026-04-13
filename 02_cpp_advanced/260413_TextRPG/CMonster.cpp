#include "CMonster.h"
#include "pch.h"
CMonster::CMonster(const char TempName[], int iTempHp, int iTempAttack)
{
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), TempName);
	m_tInfo.iAttack = iTempAttack;
	m_tInfo.iHp = iTempHp;
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Release()
{
}

void CMonster::Render()
{
	cout << "===================================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t" << "공력력: " << m_tInfo.iAttack << endl;
}


