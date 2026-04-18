#include "CPlayer.h"
#include "CObj.h"
#include "pch.h"
CPlayer::CPlayer()
{
	//strcpy_s(m_szName, sizeof(m_szName), szName);
	//m_iHp = iHp;
	//m_iAttack = iAttack;
}

CPlayer::~CPlayer()
{

}

void CPlayer::Initialize()
{
	int iInput;
	while (true)
	{
		cout << "1. 전사 2. 마법사 3. 도적: ";
		cin >> iInput;
		switch (iInput)
		{
		case CPlayer::WARRIOR:
			strcpy_s(m_szName, sizeof(m_szName), "전사");
			m_iHp = 100;
			m_iAttack = 10;
			return;
		case CPlayer::MAGE:
			strcpy_s(m_szName, sizeof(m_szName), "마법사");
			m_iHp = 100;
			m_iAttack = 10;
			return;
		case CPlayer::THIEF:
			strcpy_s(m_szName, sizeof(m_szName), "도적");
			m_iHp = 100;
			m_iAttack = 10;
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
	CPlayer* pObj = new CPlayer();
	return pObj;
}
void CPlayer::Destroy()
{
	delete this;
}
