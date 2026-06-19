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
	void			AddObject(OBJID eID, CObj* pObj);
	void			AddTile(CObj* pObj);
	list<CObj*>		GetList(OBJID eID) {return m_ObjList[eID];	}
	list<CObj*>*	GetListPtr(OBJID eID) { return &m_ObjList[eID]; }

	vector<CObj*>	GetTile() { return m_TileVec; }
	vector<CObj*>*	GetTilePtr() { return &m_TileVec; }

public :
	void	Initialize();
	int		Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

public:
	void	ChoiceButton();
	void	PutTile();

	void	SaveTile(int iOption);
	void	LoadTile();
	void	LoadStage1();
	void	LoadStage2();
	void	LoadStage3();
	void	LoadStage4();
	void	LoadStage5();
	void	DeleteObj(OBJID eID);
	void	DeleteTile();
	void	TileSwap(int iLeftIndex, int iRightIndex);

	void	PlayerBombCollision();

	int		GetRemainTile();
	int		GetRemainMonster() { return m_ObjList[OBJ_MONSTER].size(); }
	bool	GetRemainBoss() { return !m_ObjList[OBJ_BOSS].empty(); }
	bool	GetRemainPlayer() {return m_ObjList[OBJ_PLAYER].size();}
	int		GetRemainDart() { return m_ObjList[OBJ_DART].size(); }

	void	ReleaseRenderList();
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
	list<CObj*>		m_RenderList[RENDER_END];
	vector<CObj*>	m_TileVec;
};

