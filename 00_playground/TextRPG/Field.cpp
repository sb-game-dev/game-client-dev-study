#include "Field.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "Battle.h"
void Field(CPlayer* pPlayer)
{
	int iInput;
	while (true)
	{
		(*pPlayer).PrintPlayer();
		CMonster* Monster = new CMonster;
		cout << "1. 초급 2. 중급 3. 고급 4. 전단계: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			(*Monster).CreateMonster("초급", iInput * 30, iInput * 3);
			Battle(&pPlayer, Monster);
			break;
		case 2:
			(*Monster).CreateMonster("중급", iInput * 30, iInput * 3);
			Battle(&pPlayer, Monster);
			break;
		case 3:
			(*Monster).CreateMonster("고급", iInput * 30, iInput * 3);
			Battle(&pPlayer, Monster);
			break;
		case 4:
			break;
		default:
			break;
		}
	}

}
