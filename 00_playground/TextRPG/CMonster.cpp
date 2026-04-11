#include "CMonster.h"
#include "Define.h"
CMonster::CMonster()
{
	Monster = nullptr;
}
CMonster::~CMonster()
{
	Release();
}
void CMonster::Initialize(int iLevel)
{
	Monster = new stMonster;
	CreateMonster(iLevel);
}
void CMonster::Update()
{

}
void CMonster::Release()
{
	SAFE_DELETE(Monster);
}
int CMonster::GetHp() { return Monster->iHp; }
int CMonster::GetPower() { return Monster->iPower; }

void CMonster::CreateMonster(int iLevel)
{
	switch (iLevel)
	{
	case 1:
		Monster->SetStat("초급", iLevel * 30, iLevel * 3);
		return;

	case 2:
		Monster->SetStat("중급", iLevel * 30, iLevel * 3);
		return;

	case 3:
		Monster->SetStat("고급", iLevel * 30, iLevel * 3);
		return;
	default:
		break;
	}
}

void CMonster::TakeDamage(int iEnemyDamage)
{
	if (Monster->iHp > 0)
		Monster->iHp -= iEnemyDamage;
}

void CMonster::PrintInfo()
{
	cout << "==========================" << endl;
	cout << "이름:" << Monster->szName << endl;
	cout << "체력: " << Monster->iHp << ((Monster->iHp > 9) ? "\t" : "\t\t") << "공격력:" << Monster->iPower << endl;
}
