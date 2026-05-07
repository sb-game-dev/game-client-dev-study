#include "CItem.h"
#include "pch.h"
CItem::CItem(const char* szName, int iHp, int iAttack, int iMoney, ITEMTYPE IT)
	:CObj(szName,iHp,iAttack,iMoney), eType(IT),eEquip(UNEQUIP)
{
}

CItem::CItem(const CObj& rhs)
	:CObj(rhs)
{

}

CItem::~CItem()
{

}

void CItem::Render()
{
	cout << "이름: " << m_tInfo.szName << "\t가격: " << m_tInfo.iMoney << endl;
	if (eType == ARMOR)cout << "체력: " << m_tInfo.iHp << endl;
	else cout << "공격력: " << m_tInfo.iAttack << endl;
}
