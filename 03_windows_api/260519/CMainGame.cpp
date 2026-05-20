#include "pch.h"
#include "CMainGame.h"
#include "Define.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
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
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetBullet(&m_ObjList[OBJ_BULLET]);

	for (int i = 0; i < 5; i++)
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY));
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
	CollisonCheck(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}


void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->Render(m_hDC);
	}
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

void CMainGame::CollisonCheck(list<CObj*> &ObjList_1, list<CObj*> &ObjList_2)
{
	if (!ObjList_1.size() || !ObjList_2.size())
		return;
	//// 1. IntersectRect 사용
	//for (auto& Obj1 : ObjList_1)
	//{
	//	for (auto& Obj2 : ObjList_2)
	//	{
	//		RECT rc;
	//		if (IntersectRect(&rc, (Obj1->GetRect()), (Obj2->GetRect())))
	//		{
	//			Obj1->SetDead(DEAD);
	//			Obj2->SetDead(DEAD);
	//		}
	//	}
	//}

	//// 2. 피타고라스 사용
	for (auto& Obj1 : ObjList_1)
	{
		for (auto& Obj2 : ObjList_2)
		{
			double fDistance = sqrt((Obj1->GetInfo().fX - Obj2->GetInfo().fX)* (Obj1->GetInfo().fX - Obj2->GetInfo().fX) 
				+ (Obj1->GetInfo().fY - Obj2->GetInfo().fY) * (Obj1->GetInfo().fY - Obj2->GetInfo().fY));
			double fSize = (Obj1->GetInfo().fCX - Obj2->GetInfo().fCX) * 0.5f;
			if (fDistance <= fSize)
			{
				Obj1->SetDead(DEAD);
				Obj2->SetDead(DEAD);
			}
		}
	}
}
