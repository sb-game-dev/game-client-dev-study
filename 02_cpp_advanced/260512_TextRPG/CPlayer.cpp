#include "CPlayer.h"
#include "pch.h"
#include "CItem.h"
#include "algorithm"
CPlayer::CPlayer()
{
	memset(m_pSlot, 0, sizeof(m_pSlot));
}

CPlayer::~CPlayer()
{
}

void CPlayer::SelectJob()
{
	int iInput;
	while (true)
	{
		system("cls");
		cout << "직업을 선택해주세요 (1. 전사 2. 마법사 3. 도적): ";
		cin >> iInput;
		switch (iInput)
		{
		case WARRIOR:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			m_Inven.SetPlayer(this);
			return;
		case MAGE:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			m_Inven.SetPlayer(this);
			return;
		case THIEF:
			m_tInfo = { 100,100,10,10000 };
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			m_Inven.SetPlayer(this);
			return;
		default:
			break;
		}
	}
}

void CPlayer::Equip(CObj* pItem)
{
	ITEMTYPE IT = dynamic_cast<CItem*>(pItem)->GetItemType();
	if (m_pSlot[IT])
	{
		dynamic_cast<CItem*>(m_pSlot[IT])->SetItemState(UNEQUP);
		PlayerStat(-m_pSlot[IT]->GetInfo().iHp,-m_pSlot[IT]->GetInfo().iAttack);
		m_pSlot[IT] = nullptr;
	}
	m_pSlot[IT] = pItem;
	dynamic_cast<CItem*>(pItem)->SetItemState(EQUIP);
	PlayerStat(pItem->GetInfo().iHp, pItem->GetInfo().iAttack);
}

void CPlayer::Unequip(CObj* pItem)
{
	ITEMTYPE IT = dynamic_cast<CItem*>(pItem)->GetItemType();
	
	if (m_pSlot[IT])
	{
		dynamic_cast<CItem*>(m_pSlot[IT])->SetItemState(UNEQUP);
		PlayerStat(-m_pSlot[IT]->GetInfo().iHp, -m_pSlot[IT]->GetInfo().iAttack);
		m_pSlot[IT] = nullptr;
	}
}

void CPlayer::Render()
{
	cout << "==============================" << endl;
	cout << "이름: " << m_tInfo.szName << "\t소지금: " << m_tInfo.iMoney << endl;
	cout << "체력: " << m_tInfo.iHp << "/" << m_tInfo.iMaxHp << "\t공격력: " << m_tInfo.iAttack << endl;
}

void CPlayer::PlayerStat(int iHp, int iAttack)
{
	m_tInfo.iMaxHp += iHp;
	m_tInfo.iAttack += iAttack;
}
