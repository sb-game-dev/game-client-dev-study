#include "CPlayer.h"
#include "pch.h"
CPlayer::CPlayer():CObj()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::SelectJob()
{
	int iInput;
	while (true)
	{
		cout << "1. 전사 2. 마법사 3. 도적: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			m_tInfo.iHp = 100;
			m_tInfo.iAttack = 10;
			return;
		case 2:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			m_tInfo.iHp = 100;
			m_tInfo.iAttack = 10;
			return;
		case 3:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			m_tInfo.iHp = 100;
			m_tInfo.iAttack = 10;
			return;
		default:
			break;
		}
	}
}

