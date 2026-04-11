#include "CShop.h"
#include <ctime>
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
			//대장장이 코드
			if ((*ppPlayer)->GetGold() < (*ppPlayer)->GetItem() * 5)
			{
				SystemMessage("골드가 부족합니다.");
				break;
			}
			switch ((*ppPlayer)->GetItem())
			{
			case 1:
				if (rand() % 100 < 90)
				{
					(*ppPlayer)->SetGold((*ppPlayer)->GetGold() - (*ppPlayer)->GetItem() * 5);
					(*ppPlayer)->SetItem((*ppPlayer)->GetItem() + 1);
					SystemMessage("강화 성공!");
				}
				else SystemMessage("강화 실패!");
				break;
			case 2:
				if (rand() % 100 < 75)
				{
					(*ppPlayer)->SetGold((*ppPlayer)->GetGold() - (*ppPlayer)->GetItem() * 5);
					(*ppPlayer)->SetItem((*ppPlayer)->GetItem() + 1);
					SystemMessage("강화 성공!");
				}
				else SystemMessage("강화 실패!");
				break;
			case 3:
				if (rand() % 100 < 60)
				{
					(*ppPlayer)->SetGold((*ppPlayer)->GetGold() - (*ppPlayer)->GetItem() * 5);
					(*ppPlayer)->SetItem((*ppPlayer)->GetItem() + 1);
					SystemMessage("강화 성공!");
				}
				else SystemMessage("강화 실패!");
				break;
			case 4:
				if (rand() % 100 < 45)
				{
					(*ppPlayer)->SetGold((*ppPlayer)->GetGold() - (*ppPlayer)->GetItem() * 5);
					(*ppPlayer)->SetItem((*ppPlayer)->GetItem() + 1);
					SystemMessage("강화 성공!");
				}
				else SystemMessage("강화 실패!");
				break;
			
			default:
				SystemMessage("이미 최고 단계 아이템입니다.");
				break;
			}
			//대장장이 코드
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

