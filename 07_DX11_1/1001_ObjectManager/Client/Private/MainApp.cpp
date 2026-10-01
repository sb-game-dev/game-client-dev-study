#include "MainApp.h"

#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
    CGameInstance::Get().Release_Engine();
}

HRESULT CMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비. */
    ENGINE_DESC     EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iWinSizeX;
    EngineDesc.iWinSizeY = g_iWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;

    if (FAILED(Start_Level(LEVEL::LOGO)))
        return E_FAIL;









    return S_OK;
}

void CMainApp::Update(f32_t fTimeDelta)
{
    CGameInstance::Get().Update_Engine(fTimeDelta);
}

HRESULT CMainApp::Render()
{
    float4_t       vClearColor = float4_t(0.f, 0.f, 1.f, 1.f);
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Draw();

    CGameInstance::Get().Present();
    return S_OK;
}

HRESULT CMainApp::Start_Level(LEVEL eStartLevelID)
{
    if (FAILED(CGameInstance::Get().Change_Level(ETOI(LEVEL::LOADING),
        CLevel_Loading::Create(m_pDevice, m_pContext, eStartLevelID))))
        return E_FAIL;

    return S_OK;
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto pInstance = unique_ptr<CMainApp>(new CMainApp());

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CMainApp");
        pInstance.reset();        
    }

    return pInstance;
}
