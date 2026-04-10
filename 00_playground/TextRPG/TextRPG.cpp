#include "pch.h"
#include "CPlayer.h"
#include "MainGame.h"

int main()
{
	CPlayer* Player = new CPlayer;
	
	MainGame(Player);
	//(*Player).SelectJob(&Player);
	//int iInput;
	//while (true)
	//{
	//	(*Player).PrintPlayer();
	//	cout << "1. 사냥터 2. 상점 3. 종료: ";
	//	cin >> iInput;
	//	switch (iInput)
	//	{
	//	case 1:
	//		//Field(pPlayer);
	//		break;
	//	case 2:
	//		break;
	//	case 3:
	//		(*Player).SavePlayer();
	//		SAFE_DELETE(Player);
	//		return 0;
	//	default:
	//		break;
	//	}
	//}
	SAFE_DELETE(Player);
	return 0;
}
