#include "pch.h"
#include "Monster.h"

void PrintMonsterStat(Monster* pMonster)
{
	cout << "=====================================" << endl;
	cout << "이름: " << pMonster->szName << endl;
	cout << "체력: " << pMonster->iHp << "\t" << "공격력: " << pMonster->iPower << endl;
}
Monster* CreateMonster(int iNum)
{
	Monster* pMonster = new Monster;

	switch (iNum)
	{
	case 1:
		strcpy_s(pMonster->szName, sizeof(pMonster->szName), "초급");
		break;
	case 2:
		strcpy_s(pMonster->szName, sizeof(pMonster->szName), "중급");
		break;
	case 3:
		strcpy_s(pMonster->szName, sizeof(pMonster->szName), "고급");
		break;
	default:
		break;
	}
	pMonster->iHp = iNum * 30;
	pMonster->iPower = iNum * 3;

	return pMonster;
}