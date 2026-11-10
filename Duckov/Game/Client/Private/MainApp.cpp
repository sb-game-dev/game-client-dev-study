#include "MainApp.h"
#include "Client_Defines.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
{

}

CMainApp::~CMainApp()
{
#ifdef _DEBUG
    // 디바이스가 살아있을 때 디버그 인터페이스를 미리 확보 (pDebug도 디바이스 참조를 1개 가짐)
    ComPtr<ID3D11Debug> pDebug;
    m_pDevice.As(&pDebug);

    // 파이프라인에 바인딩된 내부 참조 해제 + 지연 삭제 처리 -> Refcount 0 객체 정리
    m_pContext->ClearState();
    m_pContext->Flush();
#endif

    CGameInstance::Get().Release_Engine();

#ifdef _DEBUG
    m_pContext.Reset();
    m_pDevice.Reset();

    // 남은 객체 = 진짜 누수 (디바이스 Refcount 1은 pDebug 몫이라 정상)
    if (nullptr != pDebug)
        pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL | D3D11_RLDO_IGNORE_INTERNAL);
#endif
}



HRESULT CMainApp::Initialize()
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
    EngineDesc.iWinSizeX = g_iWinSizeX;
    EngineDesc.iWinSizeY = g_iWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);
    EngineDesc.hInstance = hInst;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc,m_pDevice,m_pContext)))
        return E_FAIL;
    // 씬 생성
    if (FAILED(Start_Level(LEVEL::GAMEPLAY)))
        return E_FAIL;
    if (FAILED(Ready_Prototype_For_StaticLV()))
        return E_FAIL;

    return S_OK;
}

void CMainApp::Update(f32_t fDeltaTime)
{
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

HRESULT CMainApp::Render()
{
// Clear
    float4_t    vClearColor = float4_t{ 0.75, 0.75, 0.75, 1 };
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Bind_PipeLine_Vertex_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Pixel_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Geometry_ShaderResource(1);

    CGameInstance::Get().Draw();

    CGameInstance::Get().Present();
    return S_OK;
}


HRESULT CMainApp::Start_Level(LEVEL eStartLevelID)
{
    if(FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::LOADING), 
                                                CLevel_Loading::Create(m_pDevice, m_pContext, eStartLevelID))))
        return E_FAIL;
    return S_OK;
}

HRESULT CMainApp::Ready_Prototype_For_StaticLV()
{
    return S_OK;
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto    pInstance = unique_ptr<CMainApp>(new CMainApp());
    
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();  // 유저가 임의로 삭제 + nullptr로 채워줌. 나중에 삭제하지 않고 즉시 삭제
    
    return pInstance;
}
