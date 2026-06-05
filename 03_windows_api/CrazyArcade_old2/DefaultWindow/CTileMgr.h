#pragma once
#include "CObj.h"
class CTileMgr
{
private:
	CTileMgr();
	CTileMgr(const CTileMgr& rhs) = delete;
	CTileMgr& operator = (CTileMgr& rCTileMgr) = delete;
	~CTileMgr();

public:
	void Initialize();
	int  Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	void PickingTile(POINT pt);
	void SaveTile();
	void LoadTile();
	void LoadStage();
	vector<CObj*> GetTile() { return m_vecTile; }

public:
	static CTileMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;
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
	static CTileMgr*	m_pInstance;
	vector<CObj*>		m_vecTile;
};

