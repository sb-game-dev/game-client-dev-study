#include "pch.h"
#include "CMainGame.h"
#include "Define.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CMouse.h"
#include "CBarrel.h"
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
	m_ObjList[OBJ_BARREL].push_back(CAbstractFactory<CBarrel>::Create());
	m_ObjList[OBJ_MOUSE].push_back(CAbstractFactory<CMouse>::Create());
	for (int i = 0; i < 5; i++)
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY));

	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetBullet(&m_ObjList[OBJ_BULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetBarrel(m_ObjList[OBJ_BARREL].front());
	dynamic_cast<CBarrel*>(m_ObjList[OBJ_BARREL].front())->SetPlayer(m_ObjList[OBJ_PLAYER].front());
	dynamic_cast<CBarrel*>(m_ObjList[OBJ_BARREL].front())->SetMouse(m_ObjList[OBJ_MOUSE].front());
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
	CCollisionMgr::CollisionCircle(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::CollisionRect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_MOUSE]);
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

