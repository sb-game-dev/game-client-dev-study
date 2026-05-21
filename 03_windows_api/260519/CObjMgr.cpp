#include "pch.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"

//static 변수이므로 (클래스 변수) 클래스 외부에서 초기화 해야 함
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
	if (eID >= OBJ_END || pObj == nullptr)
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
	CCollisionMgr::CollisionCircle(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]);
	//CCollisionMgr::CollisionRectEx(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_MONSTER]);
	//CCollisionMgr::CollisionRectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->UpdateRect();
	}
}
void CObjMgr::Render(HDC m_hDC)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->Render(m_hDC);
	}
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