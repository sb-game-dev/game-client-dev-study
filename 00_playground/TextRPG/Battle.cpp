#include "Battle.h"
#include "CPlayer.h"
#include "CMonster.h"

void Battle(CPlayer** pPlayer, CMonster* pMonster)
{
	int iInput;
	while (true)
	{
		(**pPlayer).PrintPlayer();
		(*pMonster).PrintMonster();
		cout << "1. 공격 2. 도망: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			(**pPlayer).EnemyAttack((*pMonster).GetPower());
			(*pMonster).EnemyAttack((**pPlayer).GetPower());
			if ((*pMonster).GetHp() <= 0)
			{
				cout << "승리!" << endl;
				system("pause");
				return;
			}
			else if ((**pPlayer).GetHp() <= 0)
			{
				cout << "플레이어 사망!" << endl;
				system("pause");
				return;
			}
			break;

		case 2:
			return;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주세요" << endl;
			system("pause");
			break;
		}
	}
	
}