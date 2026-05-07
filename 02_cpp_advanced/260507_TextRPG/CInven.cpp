#include "CInven.h"
#include "CPlayer.h";
#include "CItem.h"
CInven::CInven() :m_pPlayer(nullptr), m_iSize(5)
{
	m_vecInvenP.reserve(5);
}

CInven::~CInven()
{
	Release();
}
void CInven::Initialize()
{
	
}

void CInven::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "1. 장착 2. 해제 3. 인벤토리 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Equip();
			break;
		case 2:
			UnEquip();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void CInven::Release()
{
	for (vector<CObj*>::iterator iter = m_vecInvenP.begin();
		iter != m_vecInvenP.end();
		++iter)
	{
		SafeDelete(*iter);
	}
	m_vecInvenP.clear();
}

void CInven::Render()
{
	for (vector<CObj*>::iterator iter = m_vecInvenP.begin();
		iter != m_vecInvenP.end();
		++iter)
	{
		cout << "==============================" << endl;
		(*iter)->Render();
	}
}
bool CInven::AddItem(CObj* pitem)
{
	if (m_vecInvenP.size() >= m_iSize) return false;
	
	CItem* pTempItem = dynamic_cast<CItem*> (pitem);
	CObj* pCopyItem = new CItem(*pTempItem);
	m_vecInvenP.push_back(pCopyItem);
	return true;
}

bool CInven::DeleteItem(int iInput, int& iMoney)
{
	if (m_vecInvenP.empty()) return false;
	if (iInput >= m_vecInvenP.size()) return false;

	vector<CObj*>::iterator iter = m_vecInvenP.begin() + iInput;

	iMoney = (*iter)->GetInfo().iMoney / 2;
	if (dynamic_cast<CItem*>(*iter)->GetEquip() == EQUIP)
		dynamic_cast<CPlayer*>(m_pPlayer)->UnEquip(*iter);
	SafeDelete(*iter);
	m_vecInvenP.erase(iter);
	return true;
}

void CInven::Equip()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "장착할 아이템 번호를 입력하세요(0:전 단계): ";
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
			if(m_vecInvenP.size() >= --iInput)
				dynamic_cast<CPlayer*>(m_pPlayer)->Equip(m_vecInvenP[iInput]);
			break;
		default:
			break;
		}
	}
}

void CInven::UnEquip()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		Render();
		cout << "해제할 아이템 번호를 입력하세요(0:전 단계): ";
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
			if (m_vecInvenP.size() >= --iInput)
				dynamic_cast<CPlayer*>(m_pPlayer)->UnEquip(m_vecInvenP[iInput]);
			break;
		default:
			break;
		}
	}
}
