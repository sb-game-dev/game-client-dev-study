#include "CField.h"
#include "CPlayer.h"
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
		cout << "1. 초급 2. 중급 3. 고급 4. 사냥터 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_pMonster = CMonster::Create("초급", iInput*30, iInput*3);
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
			m_copyPlayer->Heal(100);
		}
		m_pMonster->Destroy();
	}
}
int CField::Battle()
{
	int iInput;
	while (true)
	{
		m_copyPlayer->Render();
		m_pMonster->Render();
		cout << "1. 공격 2. 도망" << endl;
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			m_copyPlayer->TakeDamage(m_pMonster->GetInfo().iAttack);
			m_pMonster->TakeDamage(m_copyPlayer->GetInfo().iAttack);

			if (m_copyPlayer->GetInfo().iHp <= 0)
			{
				m_copyPlayer->Render();
				m_pMonster->Render();
				cout << "플레이어 사망" << endl;
				system("pause");
				return 1;
			}
			if (m_pMonster->GetInfo().iHp <= 0)
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
void CField::Release()
{

}

CField* CField::Create()
{
	CField* pField = new CField;
	return pField;
}

void CField::Destroy()
{
	delete this;
}