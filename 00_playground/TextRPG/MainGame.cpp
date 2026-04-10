#include "MainGame.h"
#include"Field.h"

void ActionMenu(CPlayer *pPlayer)
{
	int iInput;
	while (true)
	{
		(*pPlayer).PrintPlayer();
		cout << "1. 사냥터 2. 상점 3. 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Field(pPlayer);
			break;
		case 2:
			break;
		case 3:
			(*pPlayer).SavePlayer();
			return;
		default:
			break;
		}
	}
}

void MainGame(CPlayer* pPlayer)
{
	(*pPlayer).SelectJob(&pPlayer);
	
	ActionMenu(pPlayer);
}