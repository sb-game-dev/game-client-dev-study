#include "pch.h"
#include "Player.h"
#include "Shop.h"
#include "Utility.h"
#include "Item.h"

void Shop(Player* pPlayer)
{
	int iInput;
	while (true)
	{
		PrintPlayerStat(pPlayer);
		cout << "1. 체력 회복(5G) 2. 아이템 강화(" << pPlayer->iItemRarity * 5 << "G) 3. 상점 나가기: ";
		cin >> iInput;
		if (iInput < 1 || iInput>3)
		{
			PrintSysMessage("잘못된 입력입니다. 다시 입력해 주세요:");
		}
		else if (iInput == 1)
		{
			if (pPlayer->iHp < 100)
			{
				pPlayer->iHp = 100;
				pPlayer->iGold -= 5;
			}
			else PrintSysMessage("플레이어의 체력이 이미 100입니다.");
		}
		else if (iInput == 2) ItemEnhancement(pPlayer);
		else return;
	}
}
void ItemEnhancement(Player* pPlayer)
{
	if (pPlayer->iGold < pPlayer->iItemRarity * 5)
	{
		PrintSysMessage("골드가 부족합니다.");
		return;
	}
	pPlayer->iGold -= pPlayer->iItemRarity * 5;
	srand(unsigned(time(NULL)));

	bool* pSuccess = new bool(false);

	switch (pPlayer->iItemRarity)
	{
	case Normal: //90%,
		if (rand() % 100 < 90) *pSuccess = true;
		else PrintSysMessage("강화 실패!");
		break;
	case Magic: //60%
		if (rand() % 100 < 60) *pSuccess = true;
		else PrintSysMessage("강화 실패!");
		break;
	case Rare: //30%
		if (rand() % 100 < 30) *pSuccess = true;
		else PrintSysMessage("강화 실패!");
		break;
	case Legendary://10%
		if (rand() % 100 < 10) *pSuccess = true;
		else PrintSysMessage("강화 실패!");
		break;
	case Unique:
		PrintSysMessage("장비가 최고 단계 상태입니다.");
		break;
	}

	if (*pSuccess)
	{
		int* pItemColor = new int[6] {0, 8, 9, 14, 12, 13};
		pPlayer->iPower += 10;
		cout << "강화 성공!\t ";

		setColor(pItemColor[pPlayer->iItemRarity]);
		cout << szItemRarity[pPlayer->iItemRarity];

		setColor(15);
		cout << " -> ";

		pPlayer->iItemRarity += 1;

		setColor(pItemColor[pPlayer->iItemRarity]);
		cout << szItemRarity[pPlayer->iItemRarity];

		cout << endl;
		setColor(15);

		SAFE_ARR_DELETE(pItemColor);
		system("pause");
	}
}