#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CBomb.h"
#include "CMonster.h"
CMainGame::CMainGame():m_hDC(WM_NULL)
{
}

CMainGame::~CMainGame()
{
	Release();
}



void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetBomb(&m_ObjList[OBJ_BOMB]);

	for (int i = 0; i < 5; i++)
	{
		m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY, 10, 10));
	}
}

void CMainGame::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			int iResult = (*iter)->Update();
			if (iResult == DEAD)
			{
				Safe_Delete((*iter));
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CMainGame::LateUpdate()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->LateUpdate();
	}
	CollisionCheck(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_PLAYER]);
	CollisionCheck(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_MONSTER]);
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->Render(m_hDC);
	}
	TCHAR szBombCount[32] = L"";
	wsprintf(szBombCount, L"Bomb: %d", m_ObjList[OBJ_BOMB].size());
	TextOut(m_hDC, 50, 50, szBombCount,lstrlen(szBombCount));
}

void CMainGame::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Safe_Delete(Obj);
		m_ObjList[i].clear();
	}
}

void CMainGame::CollisionCheck(list<CObj*> ObjList1, list<CObj*> ObjList2)
{
	if (!ObjList1.size() || !ObjList2.size())
		return;
	for (auto Obj1 : ObjList1)
	{
		for (auto Obj2 : ObjList2)
		{
			RECT rResult;
			if (dynamic_cast<CBomb*>(Obj1)->GetState() == ST_EXPLODE_ING &&
				IntersectRect(&rResult, (Obj1->GetRect()), (Obj2->GetRect())))
			{
				Obj2->TakeDamage(Obj1->GetStat().fAttack);
				//Bullet->TakeDamage(Obj->GetStat().fAttack);
			}
		}
	}

}
