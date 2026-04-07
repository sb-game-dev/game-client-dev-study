#include "pch.h"
#include<string>
#define SAFE_DELETE(p) if(p){ delete p; p = nullptr;}
#define SAFE_ARR_DELETE(p) if(p){delete[] p;p = nullptr;}
using namespace std;
struct Player
{
	char szName[32];
	int iHp, iPower;
};

struct Monster
{
	string szName;
	int iHp, iPower;
};
char* IntToString(int);
//=================================//
void MainGame(Player* );

void PrintMonsterStat(Monster*); 
void PrintPlayerStat(Player*);

Player* ChoiceClass();
void SaveInfo(Player* pPlayer);
void CreatPlayer(Player** pPlayer, const char pName[], int iHp, int iPower);

int ActionMenu(Player*);

void Field(Player*);
int ChoiceMonsterLevel(Player*);
Monster CreatMonster(int);
void Battle(Player*, Monster*);

void Shop(Player*); //체력 회복

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Player* pPlayer = ChoiceClass();

	if (!pPlayer) return -1;
	MainGame(pPlayer);

	SAFE_DELETE(pPlayer);
}
void MainGame(Player* pPlayer)
{
	while (true)
	{
		int iActionMenu = ActionMenu(pPlayer);
		if (iActionMenu == 1)
		{
			Field(pPlayer);
		}
		else if (iActionMenu == 2)
		{
			pPlayer = ChoiceClass();
		}
		//else if (iActionMenu == 3)
		//{
		//	Shop(pPlayer);
		//}
		else
		{
			SaveInfo(pPlayer);
			return ;
		}
	}
}
Player* ChoiceClass()
{
	int iInput;
	Player* pPlayer = nullptr;
	while (true)
	{
		system("cls");

		cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적 4. 이전 캐릭터) : ";
		cin >> iInput;
		if (iInput == 1)
		{
			pPlayer = new Player;
			CreatPlayer(&pPlayer, "전사", 100, 10);
			return pPlayer;
		}
		else if (iInput == 2)
		{
			pPlayer = new Player;
			CreatPlayer(&pPlayer, "마법사", 100, 10);
			return pPlayer;
		}
		else if (iInput == 3)
		{
			pPlayer = new Player;
			CreatPlayer(&pPlayer, "도적", 100, 10);
			return pPlayer;
		}
		else if (iInput == 4)
		{
			//캐릭터 불러와서 pPlayer에 할당
			pPlayer = new Player;
			FILE* fRead = nullptr;
			errno_t err = fopen_s(&fRead, "Player_Info.txt", "rt");
			if (err == 0)
			{
				char c=' ';
				int iSize = 0;
				fseek(fRead, 0, SEEK_SET);
				while ((c = fgetc(fRead)) != '\n')
				{
					cout << c << endl;
					pPlayer->szName[iSize++] = c;
				}
				pPlayer->szName[iSize] = '\0';
				int iTemp = 0;
				while ((c = fgetc(fRead)) != '\n')
				{
					iTemp = iTemp * 10 + (c - '0');
				}
				pPlayer->iHp = iTemp;

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n')
				{
					iTemp = iTemp * 10 + (c - '0');
				}
				pPlayer->iPower = iTemp;
				fclose(fRead);
			}
			return pPlayer;
		}
		else
		{
			cout << "잘못된 입력입니다. 다시 입력하세요" << endl;
			system("pause");
			
		}
	}
}
void CreatPlayer(Player** pPlayer,const char pName[], int iHp, int iPower)
{
	strcpy_s((*pPlayer)->szName, sizeof((*pPlayer)->szName), pName);
	(*pPlayer)->iHp = iHp;
	(*pPlayer)->iPower = iPower;
	SaveInfo(*pPlayer);
}
int ActionMenu(Player* pPlayer)
{
	int iInput;
	while (true)
	{
		system("cls");
		PrintPlayerStat(pPlayer);
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

void Field(Player* pPlayer)
{
	while (true)
	{
		int iMonsterChoice = ChoiceMonsterLevel(pPlayer);
		if (iMonsterChoice == 4)
		{
			break;
		}
		else
		{
			Monster* monster = new Monster(CreatMonster(iMonsterChoice));
			Battle(pPlayer, monster);
			if (pPlayer->iHp <= 0) pPlayer->iHp = 100;
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
void Shop(Player*)
{
	
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

char* IntToString(int iNum)
{
	char* szNum = new char[32];
	if (iNum == 0)
	{
		szNum[0] = '0';
		szNum[1] = '\0';
		return szNum;
	}
	int iNumSize = 0;
	int iTemp = iNum;
	while (iTemp)
	{
		iNumSize++;
		iTemp /= 10;
	}
	szNum[iNumSize] = '\0';
	while(iNum)
	{
		szNum[--iNumSize] = iNum % 10 + '0';
		iNum /= 10;
	}
	return szNum;
}

void SaveInfo(Player* pPlayer)
{
	FILE* fWrite = nullptr;
	errno_t err = fopen_s(&fWrite, "Player_Info.txt", "wt");
	if (err == 0)
	{
		fputs(pPlayer->szName, fWrite);
		fputc('\n', fWrite);

		char* pTemp = IntToString(pPlayer->iHp);
		fputs(pTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(pTemp);
		//delete[] pTemp;
		//pTemp = nullptr;

		pTemp = IntToString(pPlayer->iPower);
		fputs(pTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(pTemp);
		//delete[] pTemp;
		//pTemp = nullptr;

		fclose(fWrite);
	}
}