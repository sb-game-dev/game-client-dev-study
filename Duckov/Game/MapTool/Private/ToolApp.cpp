#include "imgui.h" 
#include "ToolApp.h"
#include "ImGui_Manager.h"
#include "Level_MapTool.h"
#include "Tool.h"
CToolApp::~CToolApp()
{
    m_pTool.reset();
    m_pImGui_Manager.reset();
    CGameInstance::Get().Release_Engine();
}

HRESULT CToolApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비 */

    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iToolWinSizeX;
    EngineDesc.iWinSizeY = g_iToolWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);
    EngineDesc.hInstance = hInst;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;
    m_pImGui_Manager = CImGui_Manager::Create(g_hWnd, m_pDevice, m_pContext);
    if (nullptr == m_pImGui_Manager)
        return E_FAIL;
    m_pTool = CTool::Create();
    if (nullptr == m_pTool)
        return E_FAIL;
    
    // 씬 생성
    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::MAPTOOL),
        CLevel_MapTool::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    CGameInstance::Get().Set_DrawToBackBuffer(false);

    return S_OK;
}

void CToolApp::Update(f32_t fDeltaTime)
{
    m_pImGui_Manager->Begin_Frame();
    m_pTool->Update(fDeltaTime);
    CGameInstance::Get().Update_Engine(fDeltaTime);

}

HRESULT CToolApp::Render()
{
    // Clear
    float4_t    vClearColor = float4_t{ 0.f, 0.f, 0.f, 1.f };
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Draw();
    
    m_pImGui_Manager->Render();

    CGameInstance::Get().Present();
    return S_OK;
}



unique_ptr<CToolApp> CToolApp::Create()
{
    auto    pInstance = unique_ptr<CToolApp>(new CToolApp());

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CToolApp");
        pInstance.reset();
    }
    return pInstance;
}
