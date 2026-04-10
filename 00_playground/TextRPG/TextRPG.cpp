#include "pch.h"
#include "CPlayer.h"
#include "MainGame.h"

int main()
{
	CPlayer* Player = new CPlayer;
	
	MainGame(Player);
	
	SAFE_DELETE(Player);
	return 0;
}
