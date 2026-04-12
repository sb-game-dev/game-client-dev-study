#include "CShop.h"
#include <ctime>
#include "Define.h"
CShop::CShop()
{

}
CShop::~CShop()
{

}

void CShop::Initialize()
{

}
void CShop::Update(CPlayer** ppPlayer)
{
	int iInput;
	while (true)
	{
		(*ppPlayer)->PrintInfo();
		srand(unsigned(time(NULL)));
		cout << "1. 회복(5G) 2. 강화(" << (*ppPlayer)->GetItem() * 5 << "G) 3. 나가기: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			if ((*ppPlayer)->GetHp() >= 100)
			{
				SystemMessage("이미 최대 체력입니다.");
				break;
			}
			(*ppPlayer)->SetGold((*ppPlayer)->GetGold() - 5);
			(*ppPlayer)->SetHp(100);
			break;
		case 2:
			ItemEnhancement(ppPlayer, 90 - ((*ppPlayer)->GetItem() - 1) * 15);
			break;
		case 3:
			return;
		default:
			SystemMessage("다시 입력해주세요");
			break;
		}
	}
	
}

void CShop::Release()
{

}

void ItemEnhancement(CPlayer **ppPlayer,int iProbability)
{
	if ((*ppPlayer)->GetGold() < (*ppPlayer)->GetItem() * 5)
	{
		SystemMessage("골드가 부족합니다.");
		return;
	}
	if ((*ppPlayer)->GetItem() >= 5)
	{
		SystemMessage("이미 최고 단계 아이템입니다.");
		return;
	}
	(*ppPlayer)->SetGold((*ppPlayer)->GetGold() - (*ppPlayer)->GetItem() * 5);
	if (rand() % 100 < iProbability)
	{
		cout << "강화 성공\t";
		setColor(iItemColor[(*ppPlayer)->GetItem()]);
		cout << szItemRarity[(*ppPlayer)->GetItem()];

		setColor(15);
		cout << " -> ";

		(*ppPlayer)->SetItem((*ppPlayer)->GetItem() + 1);
		(*ppPlayer)->SetPower((*ppPlayer)->GetItem() * 10);

		setColor(iItemColor[(*ppPlayer)->GetItem()]);
		cout << szItemRarity[(*ppPlayer)->GetItem()] << endl;

		setColor(15);
		system("pause");
	}
	else SystemMessage("강화 실패!");
}

