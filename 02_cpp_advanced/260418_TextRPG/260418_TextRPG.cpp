#include "pch.h"
#include "CMainGame.h"
int main()
{
	CMainGame* pMainGame = CMainGame::Create();

	pMainGame->Initialize();
	pMainGame->Update();

	pMainGame->Destroy();

	return 0;
}
