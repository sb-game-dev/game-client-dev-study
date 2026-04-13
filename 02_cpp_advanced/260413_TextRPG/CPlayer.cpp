#include "CPlayer.h"
#include "Define.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initailize()
{
	
	int iInput;
	while (true)
	{
		cout << "1. 전사 2. 마법사 3. 도적: ";
		cin >> iInput;

		switch (iInput)
		{
		case CPlayer::WARRIOR:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		case CPlayer::MAGE:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		case CPlayer::THIEF:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		default:
			break;
		}
	}
}


void CPlayer::Render()
{
	system("cls");
	cout << "===================================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t" << "공력력: " << m_tInfo.iAttack << endl;
}
