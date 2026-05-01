#include "CInventory.h"
#include "pch.h"
#include "CObj.h"
#include "Define.h"
#include "CItem.h"
#include "CPlayer.h"
CInventory::CInventory() : m_pPlayer(nullptr),m_pWeaponSlot(nullptr),m_pArmorSlot(nullptr)
{
	for (int i = 0; i < 5; i++)
	{
		m_vecInventoryP.push_back(nullptr);
	}
}

CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize()
{
	
}

void CInventory::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 아이템 착용 2. 인벤토리 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			SetItem();
			break;
		case 2:
			return;
		default:
			break;
		}
	}
}

void CInventory::Release()
{
	for (auto it = m_vecInventoryP.begin();
		it != m_vecInventoryP.end();
		)
	{
		SafeDelete(*it);
		it = m_vecInventoryP.erase(it);
	}
}
void CInventory::Render()
{
	cout << "============<무기 슬롯>============" << endl;
	if (m_pWeaponSlot) m_pWeaponSlot->Render();
	else cout << "비어있음" << endl;

	cout << "============<방어구 슬롯>============" << endl;
	if (m_pWeaponSlot) m_pArmorSlot->Render();
	else cout << "비어있음" << endl;

	cout << "============<인벤토리>============" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout <<"<" << i + 1 << "번 칸>" << endl;
		if (strcmp(m_vecInventoryP[i]->GetInfo().szName, m_pWeaponSlot->GetInfo().szName)
			|| strcmp(m_vecInventoryP[i]->GetInfo().szName, m_pArmorSlot->GetInfo().szName))
		{
			cout << "(장착중)" << endl;
		}
		if (m_vecInventoryP[i])
		{
			m_vecInventoryP[i]->Render();
		}
		else
		{
			cout << "비어있음" << endl;
		}
	}
}

void CInventory::SetItem()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "착용하실 아이템 번호를 입력하세요 ";
		cin >> iInput;
		//int delta = 0;
		switch (iInput)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (m_vecInventoryP[iInput - 1])
			{
				if (m_vecInventoryP[iInput - 1]->GetInfo().iHp)
				{
					m_pArmorSlot = m_vecInventoryP[iInput - 1];
					((CPlayer*)m_pPlayer)->Heal(100 + m_vecInventoryP[iInput - 1]->GetInfo().iHp);
				}
				else
				{
					m_pWeaponSlot = m_vecInventoryP[iInput - 1];
					((CPlayer*)m_pPlayer)->SetAttack(10 + m_vecInventoryP[iInput - 1]->GetInfo().iAttack);
				}
				cout << "착용 완료!";
				system("pause");
				return;
			}
			else
			{
				cout << "아이템이 없습니다." << endl;
				system("pause");
				return;
			}
		default:
			break;
		}
	}
}

bool CInventory::AddItem(CObj* pItem)
{
	for (int i = 0; i < 5; i++)
	{
		if (!m_vecInventoryP[i])
		{
			m_vecInventoryP[i] = new CItem(*pItem);
			return 1;
		}
	}
	return 0;
}

void CInventory::SellItem(int iNum)
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "판매하실 아이템 번호를 입력하세요 ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (m_vecInventoryP[iInput - 1])
			{
				if (m_vecInventoryP[iInput - 1]->GetInfo().iHp)
				{
					m_pArmorSlot = m_vecInventoryP[iInput - 1];
					((CPlayer*)m_pPlayer)->Heal(100 + m_vecInventoryP[iInput - 1]->GetInfo().iHp);
				}
				else
				{
					m_pWeaponSlot = m_vecInventoryP[iInput - 1];
					((CPlayer*)m_pPlayer)->SetAttack(10 + m_vecInventoryP[iInput - 1]->GetInfo().iAttack);
				}
				cout << "판매 완료!";
				system("pause");
				return;
			}
			else
			{
				cout << "아이템이 없습니다." << endl;
				system("pause");
				return;
			}
		default:
			break;
		}
	}
}
