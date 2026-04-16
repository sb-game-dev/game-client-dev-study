#include <iostream>
#include "CMainGame.h"
int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CMainGame* p_MainGame = CMainGame::Create();

	p_MainGame->Initialize();
	p_MainGame->Update();
	p_MainGame->Release();
	p_MainGame->Destroy();
}
