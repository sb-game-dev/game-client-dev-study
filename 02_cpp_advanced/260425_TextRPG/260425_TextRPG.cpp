#include "pch.h"
#include "CMainGame.h"
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CMainGame MainGame;

	MainGame.Initialize();
	MainGame.Update();

	return 0;
}
