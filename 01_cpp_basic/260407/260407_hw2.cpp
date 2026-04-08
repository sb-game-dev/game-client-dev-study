#include "pch.h"
#include<ctime>
#include <windows.h>

#define SAFE_DELETE(p) if(p){ delete p; p = nullptr;}
#define SAFE_ARR_DELETE(p) if(p){delete[] p;p = nullptr;}
using namespace std;
//8:일반, 9:마법, 14:희귀, 12:전설, 13:고유
//enum itemColor
//{
//	itemNormal = 8,
//	itemMagic = 9,
//	itemRare = 14,
//	itemLegendary = 12,
//	itemUnique = 13,
//	END
//};
enum item
{
	Normal = 1,
	Magic,
	Rare,
	Legendary,
	Unique,
	END
};
struct Player
{
	char szName[32];
	int iHp, iPower,iGold = 0,iLevel = 1, iItemRarity = Normal;
};

struct Monster
{
	string szName;
	int iHp, iPower;
};
char* IntToString(int);
void PrintErroMessage(const char []);
void setColor(unsigned short text);
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

void Shop(Player*); //체력 회복 // 무기 강화

void ItemEnhancement(Player*);

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
		else if (iActionMenu == 3)
		{
			Shop(pPlayer);
		}
		else
		{
			SaveInfo(pPlayer);
			PrintErroMessage("저장되었습니다.");
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

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n')
				{
					iTemp = iTemp * 10 + (c - '0');
				}
				pPlayer->iGold = iTemp;

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n')
				{
					iTemp = iTemp * 10 + (c - '0');
				}
				pPlayer->iLevel = iTemp;

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n')
				{
					iTemp = iTemp * 10 + (c - '0');
				}
				pPlayer->iItemRarity = iTemp;
				fclose(fRead);
			}
			return pPlayer;
		}
		else PrintErroMessage("잘못된 입력입니다. 다시 입력해 주세요:");
	}
}
void CreatPlayer(Player** pPlayer,const char pName[], int iHp, int iPower)
{
	strcpy_s((*pPlayer)->szName, sizeof((*pPlayer)->szName), pName);
	(*pPlayer)->iHp = iHp;
	(*pPlayer)->iPower = iPower;
	//(*pPlayer)->iGold = 0;
	//(*pPlayer)->iLevel = 1;
	//(*pPlayer)->iItemRarity = 1;
	SaveInfo(*pPlayer);
}
int ActionMenu(Player* pPlayer)
{
	int iInput;
	while (true)
	{
		PrintPlayerStat(pPlayer);
		cout << "1. 사냥터 2. 직업 변경 3. 상점 4. 저장 후 종료: ";
		cin >> iInput;
		if (iInput < 1 || iInput>4) PrintErroMessage("잘못된 입력입니다. 다시 입력해 주세요:");
		else break;
	}
	return iInput;
}

void Field(Player* pPlayer)
{
	while (true)
	{
		int iMonsterChoice = ChoiceMonsterLevel(pPlayer);
		if (iMonsterChoice < 1 || iMonsterChoice>4) PrintErroMessage("잘못된 입력입니다. 다시 입력해 주세요:");

		else if (iMonsterChoice == 4) break;

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
		PrintPlayerStat(player);

		cout << "1.초급\t2.중급\t3.고급\t4.전 단계: ";
		cin >> iInput;
		if (iInput < 1 || iInput>4) PrintErroMessage("잘못된 입력입니다. 다시 입력해 주세요:");

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

void Battle(Player* pPlayer, Monster* pMonster)
{
	while (true)
	{
		PrintPlayerStat(pPlayer);
		PrintMonsterStat(pMonster);
		cout << "1.공격\t2.도망: ";
		int iInput;
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			pPlayer->iHp -= pMonster->iPower;
			pMonster->iHp -= pPlayer->iPower;
			if (pMonster->iHp <= 0)
			{
				pPlayer->iGold += pMonster->iPower;
				cout << "승리" <<"\t"<< pMonster->iPower <<"골드 획득!" << endl;
				system("pause");
				return;
			}
			else if (pPlayer->iHp <= 0)
			{
				cout << "플레이어 사망" << endl;
				system("pause");
				pPlayer->iHp = 100;
				return;
			}
			break;
		case 2:
			return;
		default:
			PrintErroMessage("잘못된 입력입니다. 다시 입력해 주세요:");
			break;
		}
	}
}
void Shop(Player* pPlayer)
{
	int iInput;
	while (true)
	{
		PrintPlayerStat(pPlayer);
		cout << "1. 체력 회복(5G) 2. 아이템 강화("<<pPlayer->iItemRarity*5 << "G) 3. 상점 나가기: ";
		cin >> iInput;
		if (iInput < 1 || iInput>3)
		{
			PrintErroMessage("잘못된 입력입니다. 다시 입력해 주세요:");
		}
		else if (iInput == 1)
		{
			if (pPlayer->iHp < 100)
			{
				pPlayer->iHp = 100;
				pPlayer->iGold -= 5;
			}
			else PrintErroMessage("플레이어의 체력이 이미 100입니다.");
		}
		else if (iInput == 2)
		{
			ItemEnhancement(pPlayer);
		}
		else
		{
			return;
		}
	}
}
void ItemEnhancement(Player* pPlayer)
{
	if (pPlayer->iGold < pPlayer->iItemRarity * 5)
	{
		PrintErroMessage("골드가 부족합니다.");
		return ;
	}
	
	pPlayer->iGold -= pPlayer->iItemRarity * 5;
	srand(unsigned(time(NULL)));

	bool* pSuccess = new bool(false);

	switch (pPlayer->iItemRarity)
	{
	case Normal: //90%,
		if (rand() % 100 < 90) *pSuccess = true;
		else PrintErroMessage("강화 실패!");
		break;
	case Magic: //60%
		if (rand() % 100 < 60) *pSuccess = true;
		else PrintErroMessage("강화 실패!");
		break;
	case Rare: //30%
		if (rand() % 100 < 30) *pSuccess = true;
		else PrintErroMessage("강화 실패!");
		break;
	case Legendary://10%
		if (rand() % 100 < 10) *pSuccess = true;
		else PrintErroMessage("강화 실패!");
		break;
	case Unique:
		PrintErroMessage("장비가 최고 단계 상태입니다.");
		break;
	}

	if (*pSuccess)
	{
		int* pItemColor = new int[6] {0, 8, 9, 14, 12, 13};
		pPlayer->iPower += 10;
		cout << "강화 성공!\t ";

		setColor(pItemColor[pPlayer->iItemRarity]);
		cout << pPlayer->iItemRarity;

		setColor(15);
		cout << " -> ";

		pPlayer->iItemRarity += 1;

		setColor(pItemColor[pPlayer->iItemRarity]);
		cout << pPlayer->iItemRarity;

		setColor(15);

		SAFE_ARR_DELETE(pItemColor);
		system("pause");
	}
}
void PrintPlayerStat(Player* pPlayer)
{
	system("cls");
	cout << "=====================================" << endl;
	cout << "레벨: " << pPlayer->iLevel << (pPlayer->iLevel > 9 ? "\t" : "\t\t") << "이름: " << pPlayer->szName << endl;
	cout << "체력: " << pPlayer->iHp	<< (pPlayer->iHp > 9 ? "\t" : "\t\t") << "공격력 : " << pPlayer->iPower << endl;
	cout << "골드: " << pPlayer->iGold	<< (pPlayer->iGold > 9 ? "\t" : "\t\t") << "아이템 희귀도 : ";
	//8:일반, 9:마법, 14:희귀, 12:전설, 13:고유
	int* pItemColor = new int[6]{0,8,9,14,12,13};
	setColor(pItemColor[pPlayer->iItemRarity]);
	switch (pPlayer->iItemRarity)
	{
	case Normal:
		cout << "Normal" << "\t";
		break;
	case Magic:
		cout << "Magic" << "\t";
		break;
	case Rare:
		cout << "Rare" << "\t";
		break;
	case Legendary:
		cout << "Legendary" << "\t";
		break;
	case Unique:
		cout << "Unique" << "\t";
		break;
	}
	cout<< endl;
	setColor(15);
	SAFE_ARR_DELETE(pItemColor);
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

		pTemp = IntToString(pPlayer->iPower);
		fputs(pTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(pTemp);

		pTemp = IntToString(pPlayer->iGold);
		fputs(pTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(pTemp);

		pTemp = IntToString(pPlayer->iLevel);
		fputs(pTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(pTemp);

		pTemp = IntToString(pPlayer->iItemRarity);
		fputs(pTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(pTemp);

		fclose(fWrite);
	}
}

void PrintErroMessage(const char szMessage[])
{
	cout << szMessage << endl;
	system("pause");
}

void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}