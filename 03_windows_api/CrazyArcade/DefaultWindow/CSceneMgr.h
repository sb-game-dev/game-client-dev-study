#pragma once
#include "Define.h"
#include "CScene.h"
class CSceneMgr
{
public:
	CSceneMgr();
	CSceneMgr(const CSceneMgr* rhs) = delete;
	CSceneMgr& operator=(const CSceneMgr* rhs) = delete;
	~CSceneMgr();

public:
	void ChangeScene(SCENEID eID);
	int	 Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();


	void SceneChangeReserve(SCENEID eID);
	void SceneProcess();
public:
	static CSceneMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;


	bool				m_bSceneReserve;
	SCENEID				m_eNextScene;
};	

