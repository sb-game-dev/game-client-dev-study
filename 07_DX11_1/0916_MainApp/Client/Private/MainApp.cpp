#include "MainApp.h"

CMainApp::CMainApp()
{
}

HRESULT CMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비. */


    return S_OK;
}

void CMainApp::Update()
{
}

HRESULT CMainApp::Render()
{
    return S_OK;
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto pInstance = unique_ptr<CMainApp>(new CMainApp());

    if (FAILED(pInstance->Initialize()))
    {
        pInstance.reset();        
    }

    return pInstance;
}
