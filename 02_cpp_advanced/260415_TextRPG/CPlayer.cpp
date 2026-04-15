#include "CPlayer.h"
#include "pch.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	int iInput;
	while (true)
	{
		cout << "1. 전사 2. 마법사 3. 도적 4. 이전 데이터 불러오기: ";
		cin >> iInput;
		switch (iInput)
		{
		case  CPlayer::WARRIOR:
			strcpy_s(m_tinfo.szName, sizeof(m_tinfo.szName), "전사");
			m_tinfo.iAttack = 100;
			m_tinfo.iHp = 10;
			return;
		case  CPlayer::MAGE:
			strcpy_s(m_tinfo.szName, sizeof(m_tinfo.szName), "마법사");
			m_tinfo.iAttack = 100;
			m_tinfo.iHp = 10;
			return;
		case  CPlayer::THEIF:
			strcpy_s(m_tinfo.szName, sizeof(m_tinfo.szName), "도적");
			m_tinfo.iAttack = 100;
			m_tinfo.iHp = 10;
			return;
		case  CPlayer::LOADDATA:
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
	CPlayer* pGameObj = new CPlayer;
	return pGameObj;
}

void CPlayer::Destroy()
{
	delete this;
}

void CPlayer::Render() const
{
	system("cls");
	cout << "================================" << endl;
	cout << "이름: " << m_tinfo.szName << endl;
	cout << "체력: " << m_tinfo.iHp << "\t공격력: " << m_tinfo.iAttack << endl;
}