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
    
    if (FAILED(Ready_Prototype_For_StaticLV()))
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

HRESULT CToolMainApp::Ready_Prototype_For_StaticLV()
{
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl",
            VTXUI_INSTANCE::Elements, VTXUI_INSTANCE::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_UI,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_UI_CIRCLE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl",
            VTXUI_INSTANCE_CIRCLE::Elements, VTXUI_INSTANCE_CIRCLE::iNumElements, "VS_MAIN_CIRCLE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_UI_CIRCLE,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl", "PS_MAIN_CIRCLE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXCOL_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_VertexShader.hlsl", VTXCOL::Elements, VTXCOL::iNumElements, "VS_UI_SCOPE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXCOL_SCOPE,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_PixelShader.hlsl", "PS_SCOPE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXCOL_SHADOW,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_SHADOW_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXCOL_OCCLUDED,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_OCCLUDEDPLAYER"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX_INSTANCE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM_INSTANCE::Elements, VTXNORM_INSTANCE::iNumElements, "VS_MAIN_INST"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX_INSTANCE_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_VertexShader.hlsl", VTXNORM_INSTANCE::Elements, VTXNORM_INSTANCE::iNumElements, "VS_MAIN_INST_UI"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX_SHADOW,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_SHADOW"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX_SKYBOX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_SKY"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX_NOLIGHT,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_NOLIGHT"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_TERRAIN,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_TERRAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_TERRAIN,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_TERRAIN"))))
        return E_FAIL;


    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_MODEL,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXMESH::Elements, VTXMESH::iNumElements, "VS_MAIN_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_ANIM_MODEL,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXANIMMESH::Elements, VTXANIMMESH::iNumElements, "VS_MAIN_ANIM_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_MODEL,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_MODEL_INSTANCE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl",
            VTXMESH_INSTANCE::Elements, VTXMESH_INSTANCE::iNumElements, "VS_MAIN_MODEL_INST"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN_UI"))))
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
