#include "CItem.h"
#include "pch.h"
CItem::CItem()
{
}

CItem::CItem(const char* szName, int iHp, int iAttack, int iMoney)
	:CObj(szName,iHp,iAttack,iMoney)
{
}

CItem::~CItem()
{
}

void CItem::Render()
{
	cout << "============================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack <<"\t금액: "<<m_tInfo.iGold << endl;
}
