#include "CMainGame.h"
#include "Define.h"
#include "CField.h"
CMainGame::CMainGame()
{
	Player = nullptr;
	Field = nullptr;
	Shop = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	Player = new CPlayer;
	Player->Initialize();
}

void CMainGame::Update()
{
	int iInput;
	while (true)
	{
		Player->PrintInfo();
		cout << "1. 사냥터 2. 상점 3. 저장 후 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Field = new CField;
			Field->Update(&Player);
			SAFE_DELETE(Field);
			break;
		case 2:
			Shop = new CShop;
			Shop->Update(&Player);
			SAFE_DELETE(Shop);
			break;
		case 3:
			Player->SaveData();
			return;
		default:
			SystemMessage("다시 입력해주세요");
			break;
		}
	}
}

void CMainGame::Release()
{
	SAFE_DELETE(Player);
	SAFE_DELETE(Field);
	SAFE_DELETE(Shop);
}
