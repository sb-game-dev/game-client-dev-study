#include "CField.h"
#include "pch.h"
#include "CPlayer.h"
#include "CMonster.h"
CField::CField()
{
	m_pPlayer = nullptr;
	m_pMonster = nullptr;
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
		cout << "1. 초급 2. 중급 3. 고급 4. 사냥터 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_pMonster = new CMonster("초급", 30, 3);
			break;
		case 2:
			m_pMonster = new CMonster("중급", 60, 6);
			break;
		case 3:
			m_pMonster = new CMonster("고급", 90, 9);
			break;
		case 4:
			return;
		default:
			break;
		}
		int iRes = Battle();
		if (iRes)
		{
			CPlayer* tempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);
			if (tempPlayer)
				tempPlayer->Heal(m_pPlayer->GetInfo().iMaxHp);
		}
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
		CPlayer* tempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);
		CMonster* tempMonster = dynamic_cast<CMonster*>(m_pMonster);
		cout << "1. 공격 2. 도망: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			if (tempMonster) tempMonster->TakeDamage(m_pPlayer->GetInfo().iAttack);
			if (tempPlayer) tempPlayer->TakeDamage(m_pMonster->GetInfo().iAttack);

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