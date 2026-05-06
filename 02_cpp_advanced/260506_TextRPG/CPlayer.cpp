#include "CPlayer.h"
#include "pch.h"
CPlayer::CPlayer()
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
		system("cls");
		cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적): ";
		cin >> iInput;
		m_Inventory.SetPlayer(this);
		switch (iInput)
		{
		case WARRIOR:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			return;
		case MAGE:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			return;
		case THIEF:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			return;
		default:
			break;
		}
	}
}

void CPlayer::Render()
{
	cout << "==============================" << endl;
	cout << "이름: " << m_tInfo.szName << "\t소지금: " << m_tInfo.iMoney << endl;
	cout << "체력: " << m_tInfo.iHp << "/" << m_tInfo.iMaxHp + m_Inventory.GetArmorSlot();
	cout << "\t공격력: " << m_tInfo.iAttack + m_Inventory.GetWeaponSlot() << endl;
}
