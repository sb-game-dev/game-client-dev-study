#include "pch.h"
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
	if (eID >= OBJ_END || pObj == nullptr)
		return;
	m_ObjList[eID].push_back(pObj);
}
void CObjMgr::AddTile(TILEID eID, CObj* pTile)
{
	if (eID >= TILE_END || pTile == nullptr)
		return;
	m_ObjList[eID].push_back(pTile);
}
void CObjMgr::Initialize() 
{
	for (int i=0;i<OBJ_END;++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Initialize();
	}
}

int  CObjMgr::Update() 
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();iter != m_ObjList[i].end();)
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
	return 0;
}
void CObjMgr::LateUpdate() 
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->LateUpdate();
	}

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Update_Rect();
		}
	}
}
void CObjMgr::Render(Graphics* _pGraphics)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Render(_pGraphics);
	}
}
void CObjMgr::Release() 
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			Safe_Delete(pObj);
		}
		m_ObjList[i].clear();
	}
}