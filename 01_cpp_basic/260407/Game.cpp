#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Utility.h"
#include "Field.h"
#include "Shop.h"

void MainGame(Player* pPlayer)
{
	while (true)
	{
		int iActionMenu = ActionMenu(pPlayer);
		if (iActionMenu == 1)
		{
			Field(pPlayer);
		}
		else if (iActionMenu == 2)
		{
			Shop(pPlayer);
		}
		else
		{
			SaveInfo(pPlayer);
			PrintSysMessage("저장되었습니다.");
			return;
		}
	}
}

int ActionMenu(Player* pPlayer)
{
	int iInput;
	while (true)
	{
		PrintPlayerStat(pPlayer);
		cout << "1. 사냥터 2. 상점 3. 저장 후 종료: ";
		cin >> iInput;
		if (iInput < 1 || iInput>3) PrintSysMessage("잘못된 입력입니다. 다시 입력해 주세요:");
		else break;
	}
	return iInput;
}