#include "CPlayer.h"
#include "Define.h"
#include "pch.h"
CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{
}
void CPlayer::Render()
{
	cout << "==============================" << endl;
	cout << "이름: " << m_tInfo.szName << "\t소지금: " << m_tInfo.iMoney << endl;
	cout << "체력: " << m_tInfo.iHp << "/" << (m_Inventorty.GetArmor() ? m_tInfo.iMaxHp + m_Inventorty.GetArmor()->GetInfo().iHp : m_tInfo.iMaxHp);
	cout << "\t공격력: " << (m_Inventorty.GetWeapon() ? m_tInfo.iAttack + m_Inventorty.GetWeapon()->GetInfo().iAttack : m_tInfo.iAttack) << endl;
}

void CPlayer::SelectJob()
{
	int iInput;
	while (true)
	{
		system("cls");
		cout << "직업을 선택해주세요(1. 전사 2. 마법사 3. 도적): ";
		cin >> iInput;
		switch (iInput)
		{
		case WARRIOR:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			m_Inventorty.SetPlayer(this);
			return;
		case MAGE:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			m_Inventorty.SetPlayer(this);
			return;
		case THIEF:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			m_Inventorty.SetPlayer(this);
			return;			
		default:
			break;
		}
	}
}
