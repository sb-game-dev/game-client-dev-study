#pragma once
#include "CObj.h"
#include "Define.h"
class CObjMgr
{
public :
	CObjMgr();
	CObjMgr(const CObjMgr* rhs) = delete;
	CObjMgr& operator=(const CObjMgr* rhs) = delete;
	~CObjMgr();

public:
	void AddObject(OBJID eID, CObj* pObj);
	void AddTile(TILEID eID, CObj* pTile);

public :
	void Initialize();
	int  Update();
	void LateUpdate();
	void Render(Graphics* _pGraphics);
	void Release();

public:
	static CObjMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CObjMgr* m_pInstance;
	list<CObj*>		m_ObjList[OBJ_END];
	vector<CObj*>	m_TileVector;
};

