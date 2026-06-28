#include "pch.h"
#include "CSceneMgr.h"
#include "CLogin.h"
#include "CStage1.h"
#include "CStage2.h"
#include "CStage3.h"
#include "CStage4.h"
#include "CStage5.h"
#include "CStage6.h"
#include "CShop.h"
#include "CLogo.h"
#include "CEdit.h"
#include "CMenu.h"
CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr():m_pScene(NULL), m_bSceneReserve(false), m_eNextScene(SC_END), m_eCurScene(SC_END), m_ePlayMode(PLAYMODE_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::ChangeScene(SCENEID eID)
{
	Safe_Delete(m_pScene);
	m_eCurScene = eID;
	switch (eID)
	{
	case SC_LOGO:
		m_pScene = new CLogo;
		break;
	case SC_LOGIN:
		m_pScene = new CLogin;
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
	case SC_STAGE5:
		m_pScene = new CStage5;
		break;
	case SC_STAGE6:
		m_pScene = new CStage6;
		break;
	case SC_SHOP:
		m_pScene = new CShop;
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
