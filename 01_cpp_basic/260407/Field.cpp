#include "Field.h"
#include "Utility.h"
#include "Monster.h"
#include "Player.h"
#include "Battle.h"

void Field(Player* pPlayer)
{
	while (true)
	{
		int iMonsterChoice = SelectMonsterLevel(pPlayer);
		if (iMonsterChoice < 1 || iMonsterChoice>4) PrintSysMessage("잘못된 입력입니다. 다시 입력해 주세요:");
		else if (iMonsterChoice == 4) break;
		else
		{
			Monster* pMonster = CreateMonster(iMonsterChoice);
			Battle(pPlayer, pMonster);
			if (pPlayer->iHp <= 0) pPlayer->iHp = 100;
			SAFE_DELETE(pMonster);
		}
	}
}
int SelectMonsterLevel(Player* pPlayer)
{
	int iInput;
	while (true)
	{
		PrintPlayerStat(pPlayer);

		cout << "1.초급\t2.중급\t3.고급\t4.전 단계: ";
		cin >> iInput;
		if (iInput < 1 || iInput>4) PrintSysMessage("잘못된 입력입니다. 다시 입력해 주세요:");
		else break;
	}
	return iInput;
}