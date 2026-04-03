#include<iostream>
using namespace std;
typedef struct st
{
	string szName;
	int iHp, iPower;
}Player, Monster;

void PrintStat(st Obj);
void ChoiceClass(st* Obj);
void ChoiceHuntOrEnd(st* Player);
void ChoiceLevel(st* Player);
void Battle(st* Player, st* Monster);

int main()
{
	Player Player = {"",100,10};
	ChoiceClass(&Player);
	ChoiceHuntOrEnd(&Player);
}

void ChoiceClass(st* Obj)
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
void PrintStat(st Obj)
{
	cout << "=====================================" << endl;
	cout << "이름: " << Obj.szName << endl;
	cout << "체력: " << Obj.iHp << "\t" << "공격력: " << Obj.iPower << endl;
}
void ChoiceHuntOrEnd(st* Player)
{
	system("cls");
	PrintStat(*Player);
	int iInput;
	cout << "1. 사냥터 2. 종료: ";
	cin >> iInput;
	if (iInput < 1 || iInput>2)
	{
		cout << "잘못된 입력입니다. 다시 입력해 주세요:" << endl;
		system("pause");
		ChoiceHuntOrEnd(Player);
	}
	else if (iInput == 1)
	{
		ChoiceLevel(Player);
	}
}
void ChoiceLevel(st* Player)
{
	system("cls");
	PrintStat(*Player);
	int iInput;
	cout << "1.초급\t2.중급\t3.고급\t4.전 단계: ";
	cin >> iInput;
	if (iInput < 1 || iInput>4)
	{
		cout << "잘못된 입력입니다. 다시 입력해 주세요:" << endl;
		system("pause");
		ChoiceLevel(Player);
	}
	else if (iInput == 4)
	{
		ChoiceHuntOrEnd(Player);
	}
	else
	{
		Monster Monster = { "",30* iInput,3* iInput };

		switch (iInput)
		{
		case 1:
			Monster.szName = "초급";
			break;
		case 2:
			Monster.szName = "중급";
			break;
		case 3:
			Monster.szName = "고급";
			break;
		}
		Battle(Player, &Monster);
	}
}
void Battle(st* Player, st* Monster)
{
	system("cls");
	PrintStat(*Player);
	PrintStat(*Monster);
	cout << "1.공격\t2.도망: ";
	int iInput;
	cin >> iInput;
	switch (iInput)
	{
	case 1:
		Player->iHp -= Monster->iPower;
		Monster->iHp -= Player->iPower;
		if (Monster->iHp <= 0)
		{
			cout << "승리" << endl;
			system("pause");
			ChoiceLevel(Player);
		}
		else if (Player->iHp <= 0)
		{
			cout << "플레이어 사망" << endl;
			system("pause");
			Player->iHp = 100;
			ChoiceLevel(Player);
		}
		else Battle(Player, Monster);
		break;
	case 2:
		ChoiceLevel(Player);
		return;
	default:
		cout << "잘못된 입력입니다. 다시 입력해 주세요:" << endl;
		system("pause");
		Battle(Player, Monster);
	}
}