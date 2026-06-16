#include "pch.h"
#include "CSceneMgr.h"
#include "CStage1.h"
#include "CStage2.h"
#include "CStage3.h"
#include "CStage4.h"
#include "CLogo.h"
#include "CEdit.h"
#include "CMenu.h"
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
	case SC_MENU:
		m_pScene = new CMenu;
		break;
	case SC_EDIT:
		m_pScene = new CEdit;
		break;
	case SC_STAGE1:
		m_pScene = new CStage1;
		break;
	case SC_STAGE2:
		m_pScene = new CStage2;
		break;
	case SC_STAGE3:
		m_pScene = new CStage3;
		break;
	case SC_STAGE4:
		m_pScene = new CStage4;
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
void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);
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
