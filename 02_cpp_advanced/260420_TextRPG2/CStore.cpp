#include "CStore.h"
#include "pch.h"
#include "CPlayer.h"
#include "Define.h"
#include "CItem.h"
CStore::CStore() :m_pCopyPlayer(nullptr)
{
	m_pItem[IT_WEAPON][IC_NORMAL] = new CItem("초급 검", 0, 10, 1000);
	m_pItem[IT_WEAPON][IC_MAGIC] = new CItem("중급 검", 0, 20, 2000);
	m_pItem[IT_WEAPON][IC_RARE] = new CItem("고급 검", 0, 30, 3000);

	m_pItem[IT_ARMOR][IC_NORMAL] = new CItem("초급 방어구", 10, 0, 1000);
	m_pItem[IT_WEAPON][IC_MAGIC] = new CItem("중급 방어구", 20, 0, 2000);
	m_pItem[IT_WEAPON][IC_RARE] = new CItem("고급 방어구", 30, 0, 3000);
}

CStore::~CStore()
{
	Release();
}
void CStore::Update()
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pCopyPlayer->Render();
		cout << "1. 초급 2. 중급 3. 고급 4. 상점 나가기: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Render(IC_NORMAL);
			break;
		case 2:
			Render(IC_MAGIC);
			break;
		case 3:
			Render(IC_RARE);
			break;
		case 4:
			return;
		default:
			break;
		}
		
	}
}

void CStore::Release()
{
	for (int i = 0; i < IT_END; i++)
	{
		for (int j = 0; j < IC_END; j++)
		{
			SAFEDELETE(m_pItem[i][j]);
		}
	}
}

void CStore::Render(ItemClass ItClass)
{
	int iInput;
	while (true)
	{
		system("cls");
		m_pCopyPlayer->Render();
		m_pItem[0][ItClass]->Render();
		m_pItem[1][ItClass]->Render();
		cout << "1. 무기 구매 2. 방어구 구매 3. 이전 단계: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			if (m_pCopyPlayer->GetInfo().iGold < m_pItem[0][ItClass]->GetInfo().iGold)
			{
				cout << "골드가 부족합니다."<<endl;
				break;
			}
			break;
		case 2:
			if (m_pCopyPlayer->GetInfo().iGold < m_pItem[1][ItClass]->GetInfo().iGold)
			{
				cout << "골드가 부족합니다."<<endl;
				break;
			}
			break;
		case 3:
			return;
		default:
			break;
		}

	}
}
