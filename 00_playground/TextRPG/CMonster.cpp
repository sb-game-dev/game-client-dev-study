#include "CMonster.h"
#include "pch.h"

void CMonster::SetName(const char cTemp[]) { strcpy_s(m_szName, sizeof(m_szName), cTemp); }
char* CMonster::GetName() { return m_szName; }
void CMonster::SetHp(int iNum) { m_iHp = iNum; }
int CMonster::GetHp() { return m_iHp; }
void CMonster::SetPower(int iNum) { m_iPower = iNum; }
int CMonster::GetPower() { return m_iPower; }


void CMonster::CreateMonster(const char szName[], int iHp, int iPower)
{
	//cout << "1.초급 2. 중급 3. 고급. 4. 전단계:";
	SetName(szName);
	SetHp(iHp);
	SetPower(iPower);
}

void CMonster::PrintMonster()
{
	cout << "==================================" << endl;
	cout << "이름: " << m_szName << endl;
	cout << "체력: " << m_iHp << ((m_iHp > 9) ? "\t" : "\t\t") << "공격력: " << m_iPower << endl;
}

void CMonster::EnemyAttack(int iPower)
{
	m_iHp -= iPower;
}