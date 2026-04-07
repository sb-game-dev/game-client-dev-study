#include "pch.h"

#define SAFE_DELETE(p) if(p){ delete p; p = nullptr;}

using namespace std;
struct Player
{
	string szName;
	int iHp, iPower;
};

struct Monster
{
	string szName;
	int iHp, iPower;
};

void PrintMonsterStat(Monster*); // -> 반환타입 구조체로 바꿔보기
void PrintPlayerStat(Player*);
void ChoiceClass(Player*);
int ActionMenu(Player*);
//void Shop(Player*);
void Field(Player*);
int ChoiceMonsterLevel(Player*);
Monster CreatMonster(int);
void Battle(Player*, Monster*); // 캐릭터가 죽으면  배틀 종류 후 캐릭터 체력 100 회복으로 바꾸기 (반환값 변경?)
// 메모리누수 확인하는 코드 헤더파일에 추가 pch.h

int main()
{
	Player* player = new Player{ "" , 100,10 };

	ChoiceClass(player);

	while (true)
	{
		int iActionMenu = ActionMenu(player);
		if (iActionMenu == 1)
		{
			Field(player);
		}
		else if (iActionMenu == 2)
		{
			ChoiceClass(player);
		}
		else if (iActionMenu == 3)
		{
			//Shop(player);
		}
		else
		{
			SAFE_DELETE(player);
			return 0;
		}
	}

}

void ChoiceClass(Player* player)
{
	int iInput;
	while (true)
	{
		system("cls");

		cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적) : ";
		cin >> iInput;
		if (iInput < 1 || iInput>3)
		{
			cout << "잘못된 입력입니다. 다시 입력하세요" << endl;
			system("pause");
		}
		else break;
	}
	switch (iInput)
	{
	case 1:
		player->szName = "전사";
		break;
	case 2:
		player->szName = "마법사";
		break;
	case 3:
		player->szName = "도적";
		break;
	}

}
int ActionMenu(Player* player)
{
	int iInput;
	while (true)
	{
		system("cls");
		PrintPlayerStat(player);
		cout << "1. 사냥터 2. 직업 변경 3. 종료: ";
		cin >> iInput;
		if (iInput < 1 || iInput>3)
		{
			cout << "잘못된 입력입니다. 다시 입력해 주세요:" << endl;
			system("pause");
		}
		else break;
	}
	return iInput;
}

void Field(Player* player)
{
	while (true)
	{
		int iMonsterChoice = ChoiceMonsterLevel(player);
		if (iMonsterChoice == 4)
		{
			break;
		}
		else
		{
			Monster* monster = new Monster(CreatMonster(iMonsterChoice));
			Battle(player, monster);
			SAFE_DELETE(monster);
		}
	}
}
int ChoiceMonsterLevel(Player* player)
{
	int iInput;
	while (true)
	{
		system("cls");
		PrintPlayerStat(player);

		cout << "1.초급\t2.중급\t3.고급\t4.전 단계: ";
		cin >> iInput;
		if (iInput < 1 || iInput>4)
		{
			cout << "잘못된 입력입니다. 다시 입력해 주세요:" << endl;
			system("pause");
		}
		else break;
	}
	return iInput;
}
Monster CreatMonster(int iInput)
{
	Monster monster = { "", 30 * iInput,3 * iInput };
	switch (iInput)
	{
	case 1:
		monster.szName = "초급";
		break;
	case 2:
		monster.szName = "중급";
		break;
	case 3:
		monster.szName = "고급";
		break;
	}
	return monster;
}

void Battle(Player* player, Monster* monster)
{
	while (true)
	{
		system("cls");
		PrintPlayerStat(player);
		PrintMonsterStat(monster);
		cout << "1.공격\t2.도망: ";
		int iInput;
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			player->iHp -= monster->iPower;
			monster->iHp -= player->iPower;
			if (monster->iHp <= 0)
			{
				cout << "승리" << endl;
				system("pause");
				return;
			}
			else if (player->iHp <= 0)
			{
				cout << "플레이어 사망" << endl;
				system("pause");
				player->iHp = 100;
				return;
			}
			break;
		case 2:
			return;
		default:
			cout << "잘못된 입력입니다. 다시 입력해 주세요:" << endl;
			system("pause");
		}
	}
}

void PrintPlayerStat(Player* player)
{
	cout << "=====================================" << endl;
	cout << "이름: " << player->szName << endl;
	cout << "체력: " << player->iHp << "\t" << "공격력: " << player->iPower << endl;
}

void PrintMonsterStat(Monster* monster)
{
	cout << "=====================================" << endl;
	cout << "이름: " << monster->szName << endl;
	cout << "체력: " << monster->iHp << "\t" << "공격력: " << monster->iPower << endl;
}