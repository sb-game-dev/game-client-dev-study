#include "pch.h"
#include "Player.h"
#include "Item.h"
#include "Utility.h"

void CreatPlayerObj(Player** pPlayer, const char pName[], int iHp, int iPower)
{
	strcpy_s((*pPlayer)->szName, sizeof((*pPlayer)->szName), pName);
	(*pPlayer)->iHp = 100;
	(*pPlayer)->iPower = 10;
}
void PrintPlayerStat(Player* pPlayer)
{
	system("cls");
	cout << "=====================================" << endl;
	cout << "레벨: " << pPlayer->iLevel	<< (pPlayer->iLevel > 9 ? "\t" : "\t\t")	<< "직업: " << pPlayer->szName << endl;
	cout << "체력: " << pPlayer->iHp	<< (pPlayer->iHp > 9 ? "\t" : "\t\t")		<< "공격력: " << pPlayer->iPower << endl;
	cout << "골드: " << pPlayer->iGold	<< (pPlayer->iGold > 9 ? "\t" : "\t\t")		<< "아이템: ";
	
	setColor(iItemColor[pPlayer->iItemRarity]);
	cout << szItemRarity[pPlayer->iItemRarity] << endl;
	setColor(15);
}
Player* SelectJob()
{
	int iInput;
	Player* pPlayer = new Player;
	while (true)
	{
		system("cls");
		cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적 4. 이전 캐릭터) : ";
		cin >> iInput;
		//체력 공격력을 바꿀거라 if로 남겨둠
		if (iInput == 1)
		{
			CreatPlayerObj(&pPlayer, "전사", 100, 10);
			return pPlayer;
		}
		else if (iInput == 2)
		{
			CreatPlayerObj(&pPlayer, "마법사", 100, 10);
			return pPlayer;
		}
		else if (iInput == 3)
		{
			CreatPlayerObj(&pPlayer, "도적", 100, 10);
			return pPlayer;
		}
		else if (iInput == 4)
		{
			FILE* fRead = nullptr;
			errno_t err = fopen_s(&fRead, "Player_Info.txt", "rt");
			if (err == 0)
			{
				//fgets(pPlayer->szName, sizeof(pPlayer->szName), fRead);

				char c;
				fseek(fRead, 0, SEEK_SET);
				int iTemp = 0;
				while ((c = fgetc(fRead)) != '\n')
				{
					
					pPlayer->szName[iTemp++] = c;
				}
				pPlayer->szName[iTemp] = '\0';

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n') iTemp = iTemp * 10 + (c - '0');
				pPlayer->iHp = iTemp;

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n') iTemp = iTemp * 10 + (c - '0');
				pPlayer->iPower = iTemp;

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n') iTemp = iTemp * 10 + (c - '0');
				pPlayer->iLevel = iTemp;

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n') iTemp = iTemp * 10 + (c - '0');
				pPlayer->iGold = iTemp;

				iTemp = 0;
				while ((c = fgetc(fRead)) != '\n') iTemp = iTemp * 10 + (c - '0');
				pPlayer->iItemRarity = iTemp;

				fclose(fRead);
			}
			return pPlayer;
		}
		else PrintSysMessage("다시 입력해주세요");
		
	}
}

void SaveInfo(Player* pPlayer)
{
	FILE* fWrite = nullptr;
	errno_t err = fopen_s(&fWrite, "./Player_Info.txt", "wt");
	if (err == 0)
	{
		fseek(fWrite, 0, SEEK_SET);
		fputs(pPlayer->szName, fWrite);
		fputc('\n', fWrite);

		char* szTemp = IntToString(pPlayer->iHp);
		fputs(szTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(szTemp);

		szTemp = IntToString(pPlayer->iPower);
		fputs(szTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(szTemp);

		szTemp = IntToString(pPlayer->iLevel);
		fputs(szTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(szTemp);

		szTemp = IntToString(pPlayer->iGold);
		fputs(szTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(szTemp);

		szTemp = IntToString(pPlayer->iItemRarity);
		fputs(szTemp, fWrite);
		fputc('\n', fWrite);
		SAFE_ARR_DELETE(szTemp);

		fclose(fWrite);
	}
}
//int main()
//{
//	Player* pPlayer = SelectJob();
//
//	PrintPlayerStat(pPlayer);
//
//	SaveInfo(pPlayer);
//}