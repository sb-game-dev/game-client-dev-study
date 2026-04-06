#include "SelectClass.h"

void SelectClass(Player* Player)
{
	system("cls");
	int iInput;
	cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적) : ";
	cin >> iInput;
	if (iInput < 1 || iInput>3)
	{
		cout << "잘못된 입력입니다. 다시 입력하세요" << endl;
		system("pause");
		ChoiceClass(Obj);
	}
	else
	{
		switch (iInput)
		{
		case 1:
			Obj->szName = "전사";
			break;
		case 2:
			Obj->szName = "마법사";
			break;
		case 3:
			Obj->szName = "도적";
			break;
		}
	}
}