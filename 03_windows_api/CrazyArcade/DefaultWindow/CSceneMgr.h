#pragma once
#include "Define.h"
#include "CScene.h"
class CSceneMgr
{
private:
	CSceneMgr();
	CSceneMgr(const CSceneMgr& rhs) = delete;
	CSceneMgr& operator = (CSceneMgr& rCSceneMgr) = delete;
	~CSceneMgr();
public:
	void	SceneChange(SCENEID eID);
	int		Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

public:
	static CSceneMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr*	m_pInstance;

	CScene*				m_pScene;

	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;
};

