#include "pch.h"
#include "Player.h"
#include "Monster.h"
#include "Battle.h"
#include "Utility.h"


void Battle(Player* pPlayer, Monster* pMonster)
{
	while (true)
	{
		PrintPlayerStat(pPlayer);
		PrintMonsterStat(pMonster);
		cout << "1.공격\t2.도망: ";
		int iInput;
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			pPlayer->iHp -= pMonster->iPower;
			pMonster->iHp -= pPlayer->iPower;
			if (pMonster->iHp <= 0)
			{
				pPlayer->iGold += pMonster->iPower;
				cout << "승리" << "\t" << pMonster->iPower << "골드 획득!" << endl;
				system("pause");
				return;
			}
			else if (pPlayer->iHp <= 0)
			{
				cout << "플레이어 사망" << endl;
				system("pause");
				pPlayer->iHp = 100;
				return;
			}
			break;
		case 2:
			return;
		default:
			PrintSysMessage("잘못된 입력입니다. 다시 입력해 주세요:");
			break;
		}
	}
}