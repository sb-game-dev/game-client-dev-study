#include "Loader.h"
#include "BackGround.h"
#include "Cube.h"
#include "Hill.h"
#include "QuarterView_Cam.h"
#include "Fog.h"
#include "Mirror.h"
#include "SkyBox.h"
#include "Cube_Instance.h"
#include "Tree_Instance.h"
#include "StaticProp.h"


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
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_SkyBox,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/SkyCube.dds"), 1))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Mirror,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/ice.dds"), 1))))
        return E_FAIL;


    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Normalize_AssetPath(L"../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png"),
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png"), 1))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Normalize_AssetPath(L"../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png"),
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png"), 3))))
        return E_FAIL;

    lstrcpy(m_szLoadingText, TEXT("모델을 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Normalize_AssetPath(TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw")),  
        CVIBuffer_Terrain::Create(m_pDevice, m_pContext,
            TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw")))))  
        return E_FAIL;

    matrix_t PreTransformMatrix = XMMatrixRotationY(180.f);

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Proto::Model_Tree_01,
        CModel::Create(m_pDevice, m_pContext,MODEL::NONANIM,
            "../../../Resource/Mesh/Tree/Pfb_Tree_01_1.bin"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Proto::Model_Boss_Wu,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Proto::Model_Container_Back,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/Mesh/SM_Container/SM_Container_Back.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Proto::Model_Container_Ceiling,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/Mesh/SM_Container/SM_Container_Ceiling.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Proto::Model_Container_Ground,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/Mesh/SM_Container/SM_Container_Ground.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Proto::Model_Container_L,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/Mesh/SM_Container/SM_Container_L.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY),
        Proto::Model_Container_R,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/Mesh/SM_Container/SM_Container_R.bin"))))
        return E_FAIL;

    lstrcpy(m_szLoadingText, TEXT("셰이더를 준비중입니다."));
    

    lstrcpy(m_szLoadingText, TEXT("객체원형 준비중입니다."));

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_QuaterViewCam,
        CQuarterView_Cam::Create(m_pDevice, m_pContext))))
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

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Fog,
        CFog::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Mirror,
        CMirror::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Tree_Instance,
        CTree_Instance::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_StaticProp,
        CStaticProp::Create(m_pDevice, m_pContext))))
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