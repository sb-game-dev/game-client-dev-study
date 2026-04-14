#include "CField.h"
#include "pch.h"
#include "CPlayer.h"
#include "Define.h"
#include "CMonster.h"
CField::CField()
{
	m_copyPlayer = nullptr;
	m_pMonster = nullptr;
}

CField::~CField()
{
	Release();
}


void CField::Initialize()
{

}


void CField::Update()
{
	int iInput;
	while (true)
	{
		m_copyPlayer->Render();
		cout << "1.초급 2. 중급 3. 고급 4. 사냥터 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_pMonster = new CMonster("초급",iInput*30,iInput*3);
			break;
		case 2:
			m_pMonster = new CMonster("중급", iInput * 30, iInput * 3);
			break;
		case 3:
			m_pMonster = new CMonster("고급", iInput * 30, iInput * 3);
			break;
		case 4:
			return;
		default:
			break;
		}

		if (m_pMonster)
		{
			int iResult = Battle();
			if (iResult) m_copyPlayer->Heal(100);
			SAFE_DELETE(m_pMonster);
		}
	}
}

void CField::Release()
{
	SAFE_DELETE(m_pMonster);
}

int CField::Battle()
{
	int iInput;
	while (true)
	{
		m_copyPlayer->Render();
		m_pMonster->Render();
		cout << "1. 공격 2. 도망: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_copyPlayer->TakeDamage(m_pMonster->SetInfo().iAttack);
			m_pMonster->TakeDamage(m_copyPlayer->SetInfo().iAttack);
			if (m_copyPlayer->SetInfo().iHp <= 0)
			{
				m_copyPlayer->Render();
				m_pMonster->Render();
				cout << "플레이어 사망" << endl;
				system("pause");
				return 1;
			}
			if (m_pMonster->SetInfo().iHp <= 0)
			{
				m_copyPlayer->Render();
				m_pMonster->Render();
				cout << "승리!" << endl;
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
