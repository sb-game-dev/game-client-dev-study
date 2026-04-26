#include "CField.h"
#include "pch.h"
#include "CMonster.h"
#include "CPlayer.h"
CField::CField()
{
	m_pPlayer = nullptr;
	m_pMonster = nullptr;
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
			CPlayer* p = dynamic_cast<CPlayer*>(m_pPlayer);
			if (p)
				p->Heal(100);
		}
		SAFE_DELETE(m_pMonster);
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
		cout << "1. 공격 2. 도망: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			m_pMonster->TakeDamage(m_pPlayer->GetInfo().iAttack);
			m_pPlayer->TakeDamage(m_pMonster->GetInfo().iAttack);
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
