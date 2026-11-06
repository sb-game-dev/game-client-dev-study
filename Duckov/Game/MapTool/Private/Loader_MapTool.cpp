#include "Loader_MapTool.h"
#include "SkyBox.h"
#include "MapTool_Cam.h"
#include "StaticProp.h"
#include "Hill.h"
#include "Cube.h"
#include "Fog.h"
CLoader_MapTool::CLoader_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice{ pDevice }
    , m_pContext{ pContext }
{
}

CLoader_MapTool::~CLoader_MapTool()
{
    Free();
}

// 서브 스레드
uint32_t APIENTRY ThreadMain_MapTool(void* pArg)
{
    auto       pLoader = static_cast<CLoader_MapTool*>(pArg);

    if (FAILED(pLoader->Loading()))
        return 1;

    return 0;
}

HRESULT CLoader_MapTool::Initialize(LEVEL eNextLevel)
{
    InitializeCriticalSection(&m_CriticalSection);

    m_eNextLevelID = eNextLevel;

    m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadMain_MapTool, this, 0, nullptr);
    if (0 == m_hThread)
        return E_FAIL;

    return S_OK;
}

HRESULT CLoader_MapTool::Loading()
{
    EnterCriticalSection(&m_CriticalSection);

    CoInitializeEx(nullptr, 0);       // WIC 텍스처(png) 로드에 필요

    HRESULT hr = {};
    switch (m_eNextLevelID)
    {
    case Client::LEVEL::MAPTOOL:
        hr = Loading_For_MapToolLV();
        break;
    }
    if (FAILED(hr))
        return E_FAIL;

    CoUninitialize();
    LeaveCriticalSection(&m_CriticalSection);

    return S_OK;
}

// 메인 스레드
HRESULT CLoader_MapTool::Draw_Debug()
{
    SetWindowText(g_hWnd, m_szLoadingText);
    return S_OK;
}

HRESULT CLoader_MapTool::Loading_For_MapToolLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Texture_SkyBox,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/proc_preview.png"), 1))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Normalize_AssetPath(TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png")),
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png"), 1))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Normalize_AssetPath(TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png")),
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png"), 3))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Normalize_AssetPath(TEXT("Ex/WireFence.dds")),
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/WireFence.dds"), 1))))
        return E_FAIL;

    lstrcpy(m_szLoadingText, TEXT("모델을 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VIBuffer_SkyBox,
        CVIBuffer_SkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Normalize_AssetPath(TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw")),
        CVIBuffer_Terrain::Create(m_pDevice, m_pContext, L"../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw"))))
        return E_FAIL;

    matrix_t PreTransformMatrix = XMMatrixRotationY(180.f);
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL),
        Normalize_AssetPath(TEXT("Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.fbx")),
        CModel::Create(m_pDevice, m_pContext,
            "../../../Resource/Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.fbx"))))
        return E_FAIL;

    PreTransformMatrix = XMMatrixRotationY(180.f);
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL),
        Normalize_AssetPath(TEXT("Mesh/Tree/Pfb_Tree_01_1.fbx")),
        CModel::Create(m_pDevice, m_pContext,
            "../../../Resource/Mesh/Tree/Pfb_Tree_01_1.fbx"))))
        return E_FAIL;


    lstrcpy(m_szLoadingText, TEXT("셰이더를 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_VTXTEX,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_SKYBOX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_SKY"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_NOLIGHT,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_NOLIGHT"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_TERRAIN,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_TERRAIN"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_TERRAIN,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_TERRAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_MODEL,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXMESH::Elements, VTXMESH::iNumElements, "VS_MAIN_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_MODEL,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_MODEL"))))
        return E_FAIL;

    lstrcpy(m_szLoadingText, TEXT("객체원형 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        CSkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        CMapTool_Cam::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_StaticProp,
        CStaticProp::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Hill,
        CHill::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Cube,
        CCube::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Fog,
        CFog::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;
    return S_OK;
}

shared_ptr<CLoader_MapTool> CLoader_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID)
{
    auto pInstance = shared_ptr<CLoader_MapTool>(new CLoader_MapTool(pDevice, pContext));

    if (FAILED(pInstance->Initialize(eNextLevelID)))
        pInstance.reset();
    return pInstance;
}

void CLoader_MapTool::Free()
{
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
    DeleteCriticalSection(&m_CriticalSection);
}