#include "pch.h"
#include "CCollisionMgr.h"
#include "CObjMgr.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || !pObj)
		return;
	m_ObjList[eID].push_back(pObj);
}
void CObjMgr::Update()
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

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->LateUpdate(); 
	}
	CCollisionMgr::CollisionBody(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_PLAYER]);


	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER]);
	
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_WATER]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_WATER]);
	//CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_WATER]);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->Update_Rect();
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->Render(hDC);
	}
	//TCHAR szBombCount[32] = L"";
	//wsprintf(szBombCount, L"Bomb: %d", m_ObjList[OBJ_BOMB].size());
	//TextOut(hDC, 50, 50, szBombCount, lstrlen(szBombCount));
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Safe_Delete(Obj);
		m_ObjList[i].clear();
	}
}