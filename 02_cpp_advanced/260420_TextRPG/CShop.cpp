#include "CShop.h"
#include "CPlayer.h"
#include "pch.h"
CShop::CShop()
{
	m_pCopyPlayer = nullptr;
}

CShop::~CShop()
{
}
void CShop::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pCopyPlayer->Render();
		cout << "1. 무기 상점 2. 방어구 상점 3. 상점 나가기 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			Weapon();
			break;
		case 2:
			Armor();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

CShop* CShop::Create()
{
	CShop* pObj = new CShop;
	return pObj;
}

void CShop::Destroy()
{
	delete this;
}

void CShop::Weapon()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pCopyPlayer->Render();
		cout << "1. 하급 무기 2. 중급 무기 3. 상급 무기 4. 최상급 무기 5. 무기상점 나가기 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 5:
			return;
		default:
			break;
		}
	}
}

void CShop::Armor()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pCopyPlayer->Render();
		cout << "1. 하급 방어구 2. 중급 방어구 3. 상급 방어구 4. 최상급 방어구 5. 방어구상점 나가기 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 5:
			return;
		default:
			break;
		}
	}
}
