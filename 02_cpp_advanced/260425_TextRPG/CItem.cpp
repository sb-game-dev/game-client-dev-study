#include "CItem.h"
#include "pch.h"
CItem::CItem(const char* szName, int iHp, int iAttack, int iMoney)
	:CObj(szName,iHp,iAttack,iMoney)
{
}
CItem::~CItem()
{
}
void CItem::Render()
{
	cout << "================================================" << endl;
	cout << "이름: " << m_tInfo.szName << "\t가격: " << m_tInfo.iMoney << endl;
	cout << "체력: " << m_tInfo.iHp << "\t공격력: " << m_tInfo.iAttack << endl;
}
