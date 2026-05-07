#include "CPlayer.h"
#include "pch.h"
#include "Define.h"
#include "CItem.h"
CPlayer::CPlayer()
{
	memset(m_pItemSlot, 0, sizeof(m_pItemSlot));
}

CPlayer::~CPlayer()
{
}

void CPlayer::Render()
{
	cout << "==============================" << endl;
	cout << "이름: " << m_tInfo.szName << "\t소지금: " << m_tInfo.iMoney << endl;
	cout << "체력: " << m_tInfo.iHp << "/" << m_tInfo.iMaxHp << "\t공격력: " << m_tInfo.iAttack << endl;
}

void CPlayer::SelectJob()
{
	int iInput;
	while (true)
	{
		system("cls");
		cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적): ";
		cin >> iInput;
		switch (iInput)
		{
		case WARRIOR:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			return;
		case MAGE:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			return;
		case THIEF:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			return;
		default:
			break;
		}
	}
}

void CPlayer::itemAbility(int&& iHp, int&& iAttack)
{
	m_tInfo.iAttack += iAttack; 
	m_tInfo.iHp += iHp;
}

void CPlayer::Equip(CObj* pitem)
{
	ITEMTYPE eType = dynamic_cast<CItem*> (pitem)->GetType();
	if (m_pItemSlot[eType])
	{
		itemAbility(-m_pItemSlot[eType]->GetInfo().iHp, -m_pItemSlot[eType]->GetInfo().iAttack);
		dynamic_cast<CItem*> (m_pItemSlot[eType])->SetItemEquip(UNEQUIP);
		m_pItemSlot[eType] = nullptr;
	}
	itemAbility(pitem->GetInfo().iHp, pitem->GetInfo().iAttack);
	dynamic_cast<CItem*> (pitem)->SetItemEquip(EQUIP);
	m_pItemSlot[eType] = pitem;
}

void CPlayer::UnEquip(CObj* pitem)
{
	ITEMTYPE eType = dynamic_cast<CItem*> (pitem)->GetType();
	if (m_pItemSlot[eType])
	{
		itemAbility(-m_pItemSlot[eType]->GetInfo().iHp, -m_pItemSlot[eType]->GetInfo().iAttack);
		dynamic_cast<CItem*> (m_pItemSlot[eType])->SetItemEquip(UNEQUIP);
		m_pItemSlot[eType] = nullptr;
	}
}
