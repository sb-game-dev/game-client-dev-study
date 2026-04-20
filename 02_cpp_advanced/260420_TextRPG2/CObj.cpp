#include "CObj.h"
#include "pch.h"
CObj::CObj()
{
	memset(&m_tInfo, 0, sizeof(m_tInfo));
}
CObj::CObj(const char* szName, int iHp, int iAttack, int iGold)
{
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), szName);
	m_tInfo.iHp = iHp;
	m_tInfo.iAttack = iAttack;
	m_tInfo.iGold = iGold;

}
CObj::~CObj()
{
}



void CObj::Render()
{
	cout << "============================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}

