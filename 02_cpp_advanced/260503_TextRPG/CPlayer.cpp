#include "CPlayer.h"
#include "CInventory.h"
#include "CItem.h"
#include "pch.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	m_pInventory.Release();
}

void CPlayer::SeletJob()
{
	int iInput;
	while (true)
	{
		system("cls");
		cout << "직업을 선택해 주세요(1. 전사 2. 마법사 3. 도적): ";
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

void CPlayer::Render()
{
	cout << "==============================" << endl;
	cout << "이름: " << m_tInfo.szName << "\t소지금 : " << m_tInfo.iMoney << endl;
	cout << "체력: " << m_tInfo.iHp << "/" << m_tInfo.iMaxHp << "\t공격력: " << m_tInfo.iAttack << endl;
}


bool CPlayer::AddItem(const CObj* pItem)
{
	if (m_pInventory.GetSize() < 5)
	{
		m_pInventory.PushItem(pItem);
		return true;
	}
	return false;
}

void CPlayer::SellItem(int iIndex)
{
	switch (iIndex)
	{
	case 0:
		return;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		if (iIndex <= m_pInventory.GetSize())
		{
			m_pInventory.DeleteItem(iIndex - 1);
			if (!m_pInventory.GetArmorSlot())
				m_tInfo.iMaxHp = 100;
			if (!m_pInventory.GetWeaponSlot())
				m_tInfo.iAttack = 10;
		}
		else
		{
			cout << "아이템이 비어있습니다." << endl;
			system("pause");
		}
	default:
		break;
	}
}

void CPlayer::SetItem()
{
	int iInput;
	
	while (true)
	{
		system("cls");
		Render();
		RenderInventory();
		cout << "착용하실 아이템 번호를 눌러주세요(0: 인벤토리 나가기):";
		cin >> iInput;
		switch (iInput)
		{
		case 0:
			return;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (iInput <= m_pInventory.GetSize())
			{
				m_pInventory.SetItem(iInput - 1);
				if(m_pInventory.GetArmorSlot())
					m_tInfo.iMaxHp = 100 + m_pInventory.GetArmorSlot()->GetInfo().iHp;
				if(m_pInventory.GetWeaponSlot())
					m_tInfo.iAttack = m_pInventory.GetWeaponSlot()->GetInfo().iAttack;
			}
			else
			{
				cout << "아이템이 비어있습니다." << endl;
				system("pause");
			}
		default:
			break;
		}
	}
}
