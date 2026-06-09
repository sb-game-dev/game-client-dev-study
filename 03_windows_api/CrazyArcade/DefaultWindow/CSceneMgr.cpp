#include "pch.h"
#include "CSceneMgr.h"
#include "CStage3.h"
#include "CLogo.h"
#include "CEdit.h"
CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr():m_pScene(NULL), m_bSceneReserve(false), m_eNextScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::ChangeScene(SCENEID eID)
{
	Safe_Delete(m_pScene);
	switch (eID)
	{
	case SC_LOGO:
		m_pScene = new CLogo;
		break;
	case SC_EDIT:
		m_pScene = new CEdit;
		break;
	case SC_STAGE1:
		//m_pScene = new CLogo;
		break;
	case SC_STAGE2:
		//m_pScene = new CLogo;
		break;
	case SC_STAGE3:
		m_pScene = new CStage3;
		break;
	default:
		break;
	}
	m_pScene->Initialize();
}

int	 CSceneMgr::Update()
{
	if (m_pScene)
		m_pScene->Update();
	return 0;
}
void CSceneMgr::LateUpdate()
{
	if (m_pScene)
		m_pScene->LateUpdate();
}
void CSceneMgr::Render(Graphics* _pGraphics)
{
	if (m_pScene)
		m_pScene->Render(_pGraphics);
}
void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}

void CSceneMgr::SceneChangeReserve(SCENEID eID)
{
	if (m_bSceneReserve == false)
	{
		m_bSceneReserve = true;
		m_eNextScene = eID;
	}
}

void CSceneMgr::SceneProcess()
{
	if (m_bSceneReserve)
	{
		m_bSceneReserve = false;
		ChangeScene(m_eNextScene);
		m_eNextScene = SC_END;
	}
}
