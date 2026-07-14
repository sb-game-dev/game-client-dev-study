#include "pch.h"
#include "CMainApp.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{

	//return E_FAIL;

	return S_OK;
}

int CMainApp::Update_MaintApp(const float& fTimeDelta)
{
	return 0;
}

void CMainApp::LateUpdate_MainApp(const float& fTimeDelta)
{
}

void CMainApp::Render_MainApp()
{
}

CMainApp* CMainApp::Create()
{
	CMainApp* pMainApp = new CMainApp;

	if (FAILED(pMainApp->Ready_MainApp()))
	{
		delete pMainApp;
		pMainApp = nullptr;

		return nullptr;
	}

	return pMainApp;
}

void CMainApp::Free()
{
}
