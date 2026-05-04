#include "CField.h"
#include "pch.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "Define.h"
CField::CField():m_pPlayer(nullptr), m_pMonster(nullptr)
{
}

CField::~CField()
{
}
void CField::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 초급 몬스터 2. 중급 몬스터 3. 고급 몬스터 4. 사냥터 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case LOW:
			m_pMonster = new CMonster("초급 몬스터",30,3);
			break;
		case MID:
			m_pMonster = new CMonster("중급 몬스터", 60, 6);
			break;
		case HIGH:
			m_pMonster = new CMonster("고급 몬스터", 90, 9);
			break;
		case END_MONSTERLEVEL:
			return;
		default:
			break;
		}
		int iResult = Battle();
		if (iResult)
			((CPlayer*)m_pPlayer)->SetHp(m_pPlayer->GetInfo().iMaxHp);
		SafeDelete(m_pMonster);
	}
}

int CField::Battle()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		m_pMonster->Render();
		CPlayer* tempPlayer = dynamic_cast<CPlayer*> (m_pPlayer);
		CMonster* tempMonster = dynamic_cast<CMonster*> (m_pMonster);
		if (!tempPlayer || !tempMonster)
			return -1;
		cout << "1. 공격 2. 도망: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			tempPlayer->TakeDamage(m_pMonster->GetInfo().iAttack);
			tempMonster->TakeDamage(m_pPlayer->GetInfo().iAttack);
			if (m_pPlayer->GetInfo().iHp <= 0)
			{
				cout << "플레이어 사망" << endl;
				system("pause");
				return 1;
			}
			if (m_pMonster->GetInfo().iHp <= 0)
			{
				cout << "승리" << endl;
				system("pause");
				return 0;
			}
			break;
		case 2:
			return 0;
		default:
			break;
		}
	}
}
