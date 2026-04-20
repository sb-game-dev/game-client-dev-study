#include "CPlayer.h"
#include "pch.h"
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
		case CPlayer::WARRIOR:
			strcpy_s(m_szName, sizeof(m_szName), "전사");
			m_iAttack = 10;
			m_iHp = 100;
			return;
		case CPlayer::MAGE:
			strcpy_s(m_szName, sizeof(m_szName), "마법사");
			m_iAttack = 10;
			m_iHp = 100;
			return;
		case CPlayer::THIEF:
			strcpy_s(m_szName, sizeof(m_szName), "도적");
			m_iAttack = 10;
			m_iHp = 100;
			return;
		default:
			break;
		}
	}
}

CPlayer* CPlayer::Create()
{
	CPlayer* pObj = new CPlayer;
	return pObj;
}

void CPlayer::Destroy()
{
	delete this;
}