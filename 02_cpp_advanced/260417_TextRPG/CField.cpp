#include "CField.h"
#include "CPlayer.h"
#include "pch.h"
#include "CMonster.h"
CField::CField()
{
	m_pCopyPlayer = nullptr;
	m_pMonster = nullptr;
}

CField::~CField()
{
}
void CField::Initialize()
{
}


void CField::Update()
{
	int iInput;
	while (true)
	{
		m_pCopyPlayer->Render();
		cout << "1. 초급 2. 중급 3. 고급 4. 사냥터 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_pMonster = CMonster::Create("초급", iInput * 30, iInput * 3);
			break;
		case 2:
			m_pMonster = CMonster::Create("중급", iInput * 30, iInput * 3);
			break;
		case 3:
			m_pMonster = CMonster::Create("고급", iInput * 30, iInput * 3);
			break;
		case 4:
			return;
		default:
			break;
		}
		int iResult = Battle();
		if (iResult)
		{
			m_pCopyPlayer->Heal(100);
		}
		m_pMonster->Destroy();
		m_pMonster = nullptr;
	}
}

void CField::Release()
{
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
		m_pCopyPlayer->Render();
		m_pMonster->Render();
		cout << "1. 공격 2. 도망: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			m_pCopyPlayer->TakeDamage(m_pMonster->GetInfo().iAttack);
			m_pMonster->TakeDamage(m_pCopyPlayer->GetInfo().iAttack);
			if (m_pCopyPlayer->GetInfo().iHp <= 0)
			{
				m_pCopyPlayer->Render();
				m_pMonster->Render();
				cout << "플레이어 사망";
				system("pause");
				return 1;
			}
			if (m_pMonster->GetInfo().iHp <= 0)
			{
				m_pCopyPlayer->Render();
				m_pMonster->Render();
				cout << "승리";
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