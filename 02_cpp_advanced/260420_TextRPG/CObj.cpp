#include "CObj.h"
#include "pch.h"
CObj::CObj()
{

}

CObj::~CObj()
{

}

void CObj::Render()
{
	cout << "===============================" << endl;
	cout << "이름: " << m_szName << endl;
	cout << "체력: " << m_iHp << "\t공격력: " << m_iAttack << endl;
}