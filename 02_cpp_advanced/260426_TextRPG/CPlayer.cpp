#include "CPlayer.h"
#include "pch.h"
void CPlayer::Render()
{
	cout << "=========================================" << endl;
	cout << "이름: " << m_tInfo.szName << "\t소지금: " << m_tInfo.iMoney << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}

void CPlayer::SelectJob()
{
	int iInput;
	while (true)
	{
		system("cls");
		cout << "직업을 선택하세요 (1. 전사 2. 마법사 3. 도적): ";
		cin >> iInput;
		switch (iInput)
		{
		case WARRIOR:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			m_tInfo.iHp = 100;
			m_tInfo.iAttack = 10;
			m_tInfo.iMoney = 0;
			return;
		case MAGE:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			m_tInfo.iHp = 100;
			m_tInfo.iAttack = 10;
			m_tInfo.iMoney = 0;
			return;
		case THIEF:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			m_tInfo.iHp = 100;
			m_tInfo.iAttack = 10;
			m_tInfo.iMoney = 0;
			return;
		default:
			break;
		}
	}
}
