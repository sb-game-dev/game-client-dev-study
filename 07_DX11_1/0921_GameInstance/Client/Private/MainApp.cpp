#include "MainApp.h"

#include "GameInstance.h"

CMainApp::CMainApp()
{
}

HRESULT CMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비. */
    ENGINE_DESC     EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = 800;
    EngineDesc.iWinSizeY = 600;
    EngineDesc.eWinMode = WINMODE::WIN;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;



    return S_OK;
}

void CMainApp::Update(f32_t fTimeDelta)
{

}

HRESULT CMainApp::Render()
{
    float4_t       vClearColor = float4_t(0.f, 0.f, 1.f, 1.f);
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Present();
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
