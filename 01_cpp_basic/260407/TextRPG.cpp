#include "Utility.h"
#include "pch.h"
#include "Player.h"
#include "Shop.h"
#include "Item.h"
#include "Game.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Player* pPlayer = SelectJob();

	if (!pPlayer) return -1;
	MainGame(pPlayer);

	SAFE_DELETE(pPlayer);
	return 0;
}