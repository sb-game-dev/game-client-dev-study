#include <iostream>

using namespace std;

typedef struct tagInfo
{
	char	szName[32];
	int		iHp;
	int		iAttack;

}INFO;

enum JOBINDEX { WARRIOR = 1, MAGE, THIEF, END };

INFO	SelectJob();
void	Render(INFO* pInfo);
void	Field(INFO* pPlayer);
void	CreateMonster(INFO pMonster[]);
void	Fight(INFO* pPlayer, INFO* pMonster);


int main()
{
	INFO		tPlayer;
	memset(&tPlayer, 0, sizeof(INFO));

	tPlayer = SelectJob();

	int iInput(0);

	while (true)
	{
		system("cls");

		Render(&tPlayer);

		cout << "1. 사냥터 2. 종료 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			Field(&tPlayer);
			break;

		case 2:
			return 0;
		}

	}



	return 0;
}

INFO SelectJob()
{
	INFO	tData = {};
	int		iInput(0);

	cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적) : ";
	cin >> iInput;

	switch (iInput)
	{
	case WARRIOR:
		strcpy_s(tData.szName, sizeof(tData.szName), "전사");
		tData.iHp = 100;
		tData.iAttack = 10;
		break;

	case MAGE:
		strcpy_s(tData.szName, sizeof(tData.szName), "마법사");
		tData.iHp = 100;
		tData.iAttack = 10;
		break;

	case THIEF:
		strcpy_s(tData.szName, sizeof(tData.szName), "도적");
		tData.iHp = 100;
		tData.iAttack = 10;
		break;
	}

	return tData;
}

void Render(INFO* pInfo)
{
	cout << "====================================" << endl;
	cout << "이름 : " << pInfo->szName << endl;
	cout << "체력 : " << pInfo->iHp << "\t공격력 : " << pInfo->iAttack << endl;
}

void Field(INFO* pPlayer)
{
	int		iInput(0);
	INFO	tMonster[3] = {};

	while (true)
	{
		system("cls");

		Render(pPlayer);

		cout << "1. 초급 2. 중급 3. 고급 4. 전 단계 : ";
		cin >> iInput;

		if (4 == iInput)
			return;

		else if (3 >= iInput)
		{
			CreateMonster(tMonster);
			Fight(pPlayer, &tMonster[iInput - 1]);
		}
	}

}

void CreateMonster(INFO pMonster[])
{
	strcpy_s(pMonster[0].szName, sizeof(pMonster[0].szName), "초급");
	strcpy_s(pMonster[1].szName, sizeof(pMonster[1].szName), "중급");
	strcpy_s(pMonster[2].szName, sizeof(pMonster[2].szName), "고급");

	for (int i = 0; i < 3; ++i)
	{
		pMonster[i].iHp = (i + 1) * 30;
		pMonster[i].iAttack = (i + 1) * 3;
	}

}

void Fight(INFO* pPlayer, INFO* pMonster)
{
	int iInput(0);

	while (true)
	{
		system("cls");

		Render(pPlayer);
		Render(pMonster);

		cout << "1. 공격 2. 도망 : ";
		cin >> iInput;

		if (iInput == 1)
		{
			pMonster->iHp -= pPlayer->iAttack;
			pPlayer->iHp -= pMonster->iAttack;

			if (pPlayer->iHp <= 0)
			{
				cout << "플레이어 사망" << endl;
				pPlayer->iHp = 100;
				system("pause");
				return;
			}

			if (pMonster->iHp <= 0)
			{
				cout << "승리" << endl;
				system("pause");
				return;
			}
		}

		else if (iInput == 2)
			return;

	}
}


// 1. 플레이어와 몬스터를 동적할당하여서 동작시키는 TextRPG를 완성하라