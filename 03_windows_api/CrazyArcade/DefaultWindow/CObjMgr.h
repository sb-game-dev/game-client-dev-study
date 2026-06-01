#pragma once
#include "Define.h"
#include "CObj.h"
class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(const CObjMgr* rhs) = delete;
	CObjMgr& operator=(CObjMgr& rCObjMgr) = delete;
	~CObjMgr();

public:
	void AddObject(OBJID eID, CObj* pObj);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	list<CObj*>& GetList(OBJID eID) { return m_ObjList[eID]; }

	void DeleteObj(OBJID eID);
public:
	static CObjMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CObjMgr* m_pInstance;
	list<CObj*> m_ObjList[OBJ_END];
};

