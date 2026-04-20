#include "CField.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "pch.h"
CField::CField()
{
	m_pMonster = nullptr;
	m_pCopyPlayer = nullptr;
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
		m_pCopyPlayer->Render();
		cout << "1. 초급 2. 중급 3. 고급 4. 사냥터 나가기 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			m_pMonster = CMonster::Create("초급", iInput * 30, iInput * 3);
			break;
		case 2:
			m_pMonster = CMonster::Create("초급", iInput * 30, iInput * 3);
			break;
		case 3:
			m_pMonster = CMonster::Create("초급", iInput * 30, iInput * 3);
			break;
		case 4:
			return;
		default:
			break;
		}

		int iRes = Battle();
		if (iRes)
		{
			m_pCopyPlayer->Heal(100);
		}
		m_pMonster->Destroy();
		m_pMonster = nullptr;
	}
}
CField* CField::Create()
{
	CField* pObj = new CField;
	return pObj;
}

void CField::Destroy()
{
	delete this;
}

int CField::Battle()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pCopyPlayer->Render();
		m_pMonster->Render();

		cout << "1. 공격 2. 도망: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_pCopyPlayer->TakeDamage(m_pMonster->GetAttack());
			m_pMonster->TakeDamage(m_pCopyPlayer->GetAttack());
			if (m_pCopyPlayer->GetHp() <= 0)
			{
				system("cls");
				m_pCopyPlayer->Render();
				m_pMonster->Render();
				cout << "플레이어 사망" << endl;
				system("pause");
				return 1;
			}
			if (m_pMonster->GetHp() <= 0)
			{
				system("cls");
				m_pCopyPlayer->Render();
				m_pMonster->Render();
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
