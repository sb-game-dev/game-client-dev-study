#include "pch.h"
#include "CPlayer.h"
#include "CMonster.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	int iInput;
	while (true)
	{
		cout << "1. 전사 2. 마법사 3. 도적 : ";
		cin >> iInput;
		switch (iInput)
		{
		case WARRIOR:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		case MAGE:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		case THEIF:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		default:
			break;
		}
	}
}

void CPlayer::Update()
{
	
}

void CPlayer::Release()
{
}
CPlayer* CPlayer::Create()
{
	CPlayer* p_Player = new CPlayer;
	return p_Player;
}

void CPlayer::Destroy()
{
	delete this;
}


void CPlayer::Render() const
{
	system("cls");
	cout << "========================================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}
