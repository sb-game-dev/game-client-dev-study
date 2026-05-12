#include "CShop.h"
#include "pch.h"
#include "CItem.h"
#include "CPlayer.h"
CShop::CShop():m_pPlayer(nullptr)
{
	memset(m_pItem, 0, sizeof(m_pItem));
}

CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	m_pItem[WEAPON][NORMAL]	= new CItem("초급 검", 0, 10, 1000);
	m_pItem[WEAPON][MAGIC]	= new CItem("중급 검", 0, 20, 2000);
	m_pItem[WEAPON][RARE]	= new CItem("고급 검", 0, 30, 3000);

	m_pItem[ARMOR][NORMAL]	= new CItem("초급 옷", 10, 0, 1000);
	m_pItem[ARMOR][MAGIC]	= new CItem("중급 옷", 20, 0, 2000);
	m_pItem[ARMOR][RARE]	= new CItem("고급 옷", 30, 0, 3000);
}

void CShop::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 아이템 구매 2. 아이템 판매 3. 상점 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Buy();
			break;
		case 2:
			Sell();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}
void CShop::Release()
{
	for (int i = 0; i < IT_END; i++)
	{
		for (int j = 0; j < IC_END; j++)
		{
			Safe_Delete(m_pItem[i][j]);
		}
	}
}
void CShop::Buy()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		cout << "1. 초급 아이템 2. 중급 아이템 3. 고급 아이템 4. 전 단계: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			RenderAndBuy(NORMAL);
			break;
		case 2:
			RenderAndBuy(MAGIC);
			break;
		case 3:
			RenderAndBuy(RARE);
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}

void CShop::Sell()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		dynamic_cast<CPlayer*>(m_pPlayer)->GetInven().Render();
		cout << "판매할 아이템 번호를 입력하세요(0:전 단계): ";
		cin >> iInput;
		int iMoney = 0;
		switch (iInput)
		{
		case 0:
			return;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			iMoney = dynamic_cast<CPlayer*>(m_pPlayer)->GetInven().DeleteItem(--iInput);
			if (iMoney == 0) cout << "비어있는 칸입니다" << endl;
			else
			{
				dynamic_cast<CPlayer*>(m_pPlayer)->ChangeMoney(iMoney);
				cout << "판매 완료!" << endl;
			}
			system("pause");
		default:
			break;
		}
	}
}

void CShop::RenderAndBuy(ITEMCLASS IC)
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pPlayer->Render();
		m_pItem[WEAPON][IC]->Render();
		m_pItem[ARMOR][IC]->Render();
		cout << "1. 무기 구매 2. 방어구 구매 3. 전 단계: ";
		cin >> iInput;
		iInput--;
		switch (iInput)
		{
		case WEAPON:
			if (m_pPlayer->GetInfo().iMoney >= m_pItem[WEAPON][IC]->GetInfo().iMoney 
				&& dynamic_cast<CPlayer*>(m_pPlayer)->GetInven().AddItem(m_pItem[WEAPON][IC]))
			{
				dynamic_cast<CPlayer*>(m_pPlayer)->ChangeMoney(-m_pItem[WEAPON][IC]->GetInfo().iMoney);
				cout << "무기 구매 성공" << endl;
			}
			else
			{
				cout << "골드 또는 인벤토리칸이 부족합니다." << endl;
			}
			system("pause");
			break;
		case ARMOR:
			if (m_pPlayer->GetInfo().iMoney >= m_pItem[ARMOR][IC]->GetInfo().iMoney 
				&& dynamic_cast<CPlayer*>(m_pPlayer)->GetInven().AddItem(m_pItem[ARMOR][IC]))
			{
				dynamic_cast<CPlayer*>(m_pPlayer)->ChangeMoney(-m_pItem[ARMOR][IC]->GetInfo().iMoney);
				cout << "방어구 구매 성공" << endl;
			}
			else
			{
				cout << "골드 또는 인벤토리칸이 부족합니다." << endl;
			}
			system("pause");
			break;
		case IT_END:
			return;
		default:
			break;
		}
	}
}
