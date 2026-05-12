#include "CItem.h"
#include "pch.h"
CItem::CItem(const char* szName, int iHp, int iAttack, int iMoney)
	:CObj(szName,iHp,iAttack,iMoney),m_ItemState(UNEQUP)
{
	if (iHp) m_ItemType = ARMOR;
	else m_ItemType = WEAPON;
}

CItem::CItem(const CObj& rhs)
	:CObj(rhs), m_ItemState(UNEQUP)
{
	if (rhs.GetInfo().iHp) m_ItemType = ARMOR;
	else m_ItemType = WEAPON;
}

CItem::~CItem()
{
}

void CItem::Render()
{
	cout << "==============================" << endl;
	if (m_ItemState == EQUIP)
		cout << "(장착중)";
	cout << "이름: " << m_tInfo.szName << "\t가격: " << m_tInfo.iMoney << endl;
	if(m_ItemType == WEAPON)
		cout << "아이템 타입: 무기" << "\t공격력: " << m_tInfo.iAttack << endl;
	else
		cout<< "아이템 타입: 방어구" << "\t체력: " << m_tInfo.iHp << endl;	
}
