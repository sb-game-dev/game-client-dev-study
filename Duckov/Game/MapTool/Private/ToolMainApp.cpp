#include "MapTool_Defines.h"
#include "ToolMainApp.h"

#include "Level_Loading_MapTool.h"
CToolMainApp::~CToolMainApp()
{

    CGameInstance::Get().Release_Engine();
}

HRESULT CToolMainApp::Initialize()
{   
    /* 엔진 프로젝트에 대한 준비 */
//#ifdef _DEBUG
//
//    if (::AllocConsole() == TRUE)
//    {
//        FILE* nfp[3];
//        freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//        freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//        freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//        std::ios::sync_with_stdio();
//    }
//
//#endif // _DEBUG

    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iToolWinSizeX;
    EngineDesc.iWinSizeY = g_iToolWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);
    EngineDesc.hInstance = hInst;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;
    
    if (FAILED(Start_Level(LEVEL::MAPTOOL)))
        return E_FAIL;


    
    CGameInstance::Get().Set_DrawToBackBuffer(false);

    return S_OK;
}

void CToolMainApp::Update(f32_t fDeltaTime)
{
    
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

HRESULT CToolMainApp::Render()
{
    // Clear
    float4_t    vClearColor = float4_t{ 0.f, 0.f, 0.f, 1.f };
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Bind_PipeLine_Vertex_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Pixel_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Geometry_ShaderResource(1);

    CGameInstance::Get().Draw();
    
    

    CGameInstance::Get().Present();
    return S_OK;
}





HRESULT CToolMainApp::Start_Level(LEVEL eStartLevelID)
{
    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::LOADING),
        CLevel_Loading_MapTool::Create(m_pDevice, m_pContext, eStartLevelID))))
        return E_FAIL;
    return S_OK;
}


unique_ptr<CToolMainApp> CToolMainApp::Create()
{
    auto    pInstance = unique_ptr<CToolMainApp>(new CToolMainApp());

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CToolMainApp");
        pInstance.reset();
    }
    return pInstance;
}
