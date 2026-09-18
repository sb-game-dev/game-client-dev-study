#include "MainApp.h"
#include "Engine_Define.h"
#include "Client_Defines.h"

CMainApp::CMainApp()
{

}

HRESULT CMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비 */



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
    auto    pInstance = unique_ptr<CMainApp>(new CMainApp());
    //unique_ptr<CMainApp>    pInstance = unique_ptr<CMainApp>(new CMainApp());
    
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();  // 유저가 임의로 삭제 + nullptr로 채워줌. 나중에 삭제하지 않고 즉시 삭제
    
    return pInstance;
}
