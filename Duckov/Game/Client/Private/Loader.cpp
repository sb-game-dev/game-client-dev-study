#include "Loader.h"
#include "BackGround.h"
#include "Cube.h"
#include "Player.h"
#include "Hill.h"
#include "QuarterView_Cam.h"
#include "Wave.h"
#include "Fog.h"
#include "Mirror.h"
#include "SkyBox.h"
#include "Tree.h"
#include "Cube_Instance.h"
#include "Client_Mouse.h"
#include "Scope.h"
#include "Inven.h"

CLoader::CLoader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice{pDevice}
    , m_pContext{ pContext }
{
}

CLoader::~CLoader()
{
    Free();
}

// 서브 스레드
uint32_t APIENTRY ThreadMain(void* pArg)
{
    auto       pLoader = static_cast<CLoader*>(pArg);

    // 서브 스레드
    if (FAILED(pLoader->Loading()))
        return 1;

    return 0;
}

HRESULT CLoader::Initialize(LEVEL eNextLevel)
{
    InitializeCriticalSection(&m_CriticalSection);

    m_eNextLevelID = eNextLevel;

    m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadMain, this, 0, nullptr);
    if (0 == m_hThread)
        return E_FAIL;

    return S_OK;
}

HRESULT CLoader::Loading()
{
    //메모리를 공유하는 임계영역에 접근
    EnterCriticalSection(&m_CriticalSection);

    // 현재 스레드에서 COM 라이브러리를 사용할 수 있도록 초기화
    CoInitializeEx(nullptr, 0);

    HRESULT hr = {};
    switch (m_eNextLevelID)
    {
    case Client::LEVEL::LOGO:
        hr = Loading_For_LogoLV();//S_OK or E_FAIL
        break;
    case Client::LEVEL::GAMEPLAY:
        hr = Loading_For_GamePlayLV();
        break;
    }
    if (FAILED(hr))
        return E_FAIL;
    // 현재 스레드에서 COM 라이브러리를 사용할 수 있도록 초기화 해체
    CoUninitialize();
    //메모리를 공유하는 임계영역을 떠남
    LeaveCriticalSection(&m_CriticalSection);

    return S_OK;
}

// 메인 스레드
HRESULT CLoader::Draw_Debug()
{
    SetWindowText(g_hWnd, m_szLoadingText);
    return S_OK;
}

// 서브 스레드
HRESULT CLoader::Loading_For_LogoLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("모델을 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("셰이더를 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("객체원형 준비중입니다."));
    CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::LOGO), TEXT("Prototype_GameObject_BackGround"),
        CBackGround::Create(m_pDevice, m_pContext));

    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;
    return S_OK;
}

HRESULT CLoader::Loading_For_GamePlayLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Cube,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/WireFence.dds"), 1))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Hill,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/grass.dds"), 1))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Wave,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/water2.dds"), 1))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Tree,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/tree%d.dds"), 4))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_SkyBox,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/SkyCube.dds"), 1))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Mirror,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/ice.dds"), 1))))
        return E_FAIL;


    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Terrain_Blend,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png"), 1))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Terrain_Layer,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png"), 3))))
        return E_FAIL;

    // 마우스 조준선
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Mouse,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/UI/Mouse/cursor%d.png"), 4))))
        return E_FAIL;

    // 아이템 아이콘
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_ItemIcons,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Inventory/IconArray/icons_test_128.dds"), 1))))
        return E_FAIL;

    lstrcpy(m_szLoadingText, TEXT("모델을 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Cube,
        CVIBuffer_Cube::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_SkyBox,
        CVIBuffer_SkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Pyramid,
        CVIBuffer_Pyramid::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Rect,
        CVIBuffer_Rect::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    

    lstrcpy(m_szLoadingText, TEXT("셰이더를 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VS_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_UI.hlsl",
            VTXUI_INSTANCE::Elements, VTXUI_INSTANCE::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_UI,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_UI.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXCOL,
        CVertexShader::Create(m_pDevice, m_pContext,L"../Bin/Shader/Shader_VtxCol.hlsl",VTXCOL::Elements,VTXCOL::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxCol.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_SCOPE,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxCol.hlsl", "PS_SCOPE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_SHADOW,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxCol.hlsl", "PS_SHADOW"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_OCCLUDED,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxCol.hlsl", "PS_OCCLUDEDPLAYER"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXTEX,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXTEX_INSTANCE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", VTXNORM_INSTANCE::Elements, VTXNORM_INSTANCE::iNumElements, "VS_MAIN_INST"))))
        return E_FAIL;
    
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX_SHADOW,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_SHADOW"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX_SKYBOX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_SKY"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX_NOLIGHT,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_NOLIGHT"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::VS_TERRAIN,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_TERRAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::PS_TERRAIN,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_TERRAIN"))))
        return E_FAIL;

    lstrcpy(m_szLoadingText, TEXT("객체원형 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Player,
        CPlayer::Create(m_pDevice, m_pContext))))
        return E_FAIL;


    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Cube,
        CCube::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Cube_Instance,
        CCube_Instance::Create(m_pDevice, m_pContext))))
        return E_FAIL;
   
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_SkyBox,
        CSkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Hill,
        CHill::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Wave,
        CWave::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Fog,
        CFog::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Mirror,
        CMirror::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Tree,
        CTree::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Client_Mouse,
        CClient_Mouse::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Scope,
        CScope::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Inven,
        CInven::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;
    return S_OK;
}
shared_ptr<CLoader> CLoader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID)
{
    auto pInstance = shared_ptr<CLoader>(new CLoader(pDevice, pContext));

    if (FAILED(pInstance->Initialize(eNextLevelID)))
        pInstance.reset();
    return pInstance;
}
void CLoader::Free()
{
    WaitForSingleObject(m_hThread, INFINITE);

    //DeleteObject(m_hThread);

    CloseHandle(m_hThread);

    DeleteCriticalSection(&m_CriticalSection);
}