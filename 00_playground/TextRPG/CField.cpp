#include "CField.h"
#include "Define.h"
#include "CPlayer.h"
CField::CField()
{
	Monster = nullptr;
}
CField::~CField()
{
	Release();
}
void CField::Initialize(CPlayer* pPlayer)
{
}
void CField::Update(CPlayer** ppPlayer)
{
	int iInput;
	while (true)
	{
		(*ppPlayer)->PrintInfo();
		cout << "1. 초급 2. 중급 3. 고급 4. 전단계: ";
		cin >> iInput;

		Monster = new CMonster;
		switch (iInput)
		{
		case 1:
			Monster->Initialize(iInput);
			break;
		case 2:
			Monster->Initialize(2);
			break;
		case 3:
			Monster->Initialize(3);
			break;
		case 4:
			return;
		default:
			SystemMessage("다시 입력해주세요");
			continue;
		}

		Battle(ppPlayer);
		Release();
		if ((*ppPlayer)->GetHp() <= 0) (*ppPlayer)->SetHp(100);
	}	
}
void CField::Release()
{
	SAFE_DELETE(Monster);
}

void CField::Battle(CPlayer** ppPlayer)
{
	int iInput;
	while (true)
	{
		(*ppPlayer)->PrintInfo();
		Monster->PrintInfo();
		cout << "1. 공격 2. 도망: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			(*ppPlayer)->TakeDamage(Monster->GetPower());
			(Monster)->TakeDamage((*ppPlayer)->GetPower());
			if ((*ppPlayer)->GetHp() <= 0)
			{
				(*ppPlayer)->PrintInfo();
				Monster->PrintInfo();
				cout << "플레이어 사망" << endl;
				system("pause");
				return;
			}
			if (Monster->GetHp() <= 0)
			{
				(*ppPlayer)->SetGold((*ppPlayer)->GetGold() + Monster->GetPower());
				(*ppPlayer)->PrintInfo();
				Monster->PrintInfo();
				cout << "승리!" << endl;
				system("pause");
				return;
			}
			break;
		case 2:
			return;
		default:
			SystemMessage("다시 입력해주세요");
			break;
		}
	}
}

