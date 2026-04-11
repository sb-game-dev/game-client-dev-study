#include "CMainGame.h"
CMainGame::CMainGame()
{

	cout << "CMainGame 클래스 생성자 호출" << endl;
	stu = new CStudent;
	system("pause");
}
CMainGame::~CMainGame()
{
	stu->Release();
	cout << "CMainGame 클래스 소멸자 호출" << endl;
	system("pause");
}

void CMainGame::Initialize()
{
	
}

void CMainGame::Update()
{

	int iInput;
	while (true)
	{
		system("cls");
		cout << "1. 추가 2. 출력 3. 검색 4. 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			stu->AddStudent();
			break;
		case 2:
			stu->PrintStudent();
			break;
		case 3:
			stu->SearchStudent();
			break;
		case 4:
			return;
		default:
			break;
		}
		system("pause");
	}
}

void CMainGame::Release()
{
}


