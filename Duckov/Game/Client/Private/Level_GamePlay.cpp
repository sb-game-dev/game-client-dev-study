#include "Level_GamePlay.h"
#include "Cube.h"
#include "Player.h"
#include "Hill.h"
#include "Player_PointLight.h"
#include "Player_SpotLight.h"
#include "SunLight.h"
#include "Mirror.h"
#include "Free_Cam.h"
#include "QuarterView_Cam.h"

CLevel_GamePlay::CLevel_GamePlay(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_GamePlay::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"GamePlay_Level");
    if(FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    if(FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
        return E_FAIL;

    return S_OK;
}

void CLevel_GamePlay::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

HRESULT CLevel_GamePlay::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}
HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_SkyBox,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::SkyBox)))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Inven,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Inven)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_HUD,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::HUD)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Client_Mouse,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Client_Mouse)))
        return E_FAIL;

    CHill::HILL_DESC Hill_Desc{};
    Hill_Desc.iLevelIndex = ETOUI(LEVEL::GAMEPLAY);
    Hill_Desc.strMeshPath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw");  // ÁöÇü ¹öÆÛ + ³ôÀÌ¸Ê
    Hill_Desc.strTexturePath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png");            // È¥ÇÕ¸Ê
    Hill_Desc.strLayerPath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png");              // ·¹ÀÌ¾î
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Hill,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Hill, &Hill_Desc)))
        return E_FAIL;

    CPlayer::PLAYER_DESC Player_Desc{};
    Player_Desc.fDegreeRotPerSec = 180.f;
    Player_Desc.iLevelIndex = ETOUI(LEVEL::GAMEPLAY);
    Player_Desc.vPosition = { 38.2f ,0.f,-207.2f };
    //Player_Desc.strMeshPath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw");  // Mesh
    //Player_Desc.strTexturePath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png");            // Texture

    if(FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Player, 
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Player, &Player_Desc)))
        return E_FAIL;

    for (int i = 0; i < 16; ++i)
    {
        CCube::CUBE_DESC Cube_Desc{};
        f32_t fPosX = 38.2f + 10 * sinf(XM_2PI / 16 * i);
        f32_t fPosZ = -207.2f + 10 * cosf(XM_2PI / 16 * i);
    
        Cube_Desc.vPosition = { fPosX ,0.f,fPosZ };
        Cube_Desc.iLevelIndex = ETOUI(LEVEL::GAMEPLAY);
        Cube_Desc.strMeshPath = Proto::VIBuffer_Cube;
        Cube_Desc.strTexturePath = Proto::Texture_Cube;
        //Cube_Desc.strTexturePath;
        if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Cube,
            ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Cube + to_wstring(i), &Cube_Desc)))
            return E_FAIL;
    }

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Cube_Instance,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Cube_Instance)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Tree_Instance,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Tree_Instance)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Fog,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Fog)))
        return E_FAIL;

    CMirror::MIRROR_DESC Mirror_Desc{};
    Mirror_Desc.fPosX = 50.2f;
    Mirror_Desc.fPosY = 0.f;
    Mirror_Desc.fPosZ = -180.2f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Mirror,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Mirror, &Mirror_Desc)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Scope,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Scope)))
        return E_FAIL;

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Player);
    auto pMirror = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Mirror);
    CGameInstance::Get().Set_Mirror(pMirror);    

    auto pPlayer_PointLight = CPlayer_PointLight::Create(m_pDevice, m_pContext);
    pPlayer_PointLight->SetPlayer(pPlayer);
    CGameInstance::Get().AddLight(L"Player_PointLight", pPlayer_PointLight);

    auto pPlayer_SpotLight = CPlayer_SpotLight::Create(m_pDevice, m_pContext);
    pPlayer_SpotLight->SetPlayer(pPlayer);
    CGameInstance::Get().AddLight(L"Player_SpotLight", pPlayer_SpotLight);

    auto SunLight = CSunLight::Create(m_pDevice, m_pContext);
    CGameInstance::Get().AddLight(L"SunLight", SunLight);

    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const tchar_t* pLayerTag)
{
    CQuarterView_Cam::CAMERA_QUATER_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;
    CameraDesc.fSpeedPerSec = 20.f;
    CameraDesc.vEye = float4_t(-10.f, 10.f, -10.f, 1.f);
    CameraDesc.vAt = float4_t(0.f, 0.f, 0.f, 1.f);
    CameraDesc.fFovy = 20.f;
    CameraDesc.fNear = 0.3f;
    CameraDesc.fFar = 300.f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_QuaterViewCam,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::QuaterViewCam, &CameraDesc)))
        return E_FAIL;

    auto pQuaterViewCam = dynamic_pointer_cast<CQuarterView_Cam>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::QuaterViewCam));
    CGameInstance::Get().Add_Camera(CAMERA::QUARTERVIEW, pQuaterViewCam);
    CGameInstance::Get().Set_MainCamera(CAMERA::QUARTERVIEW);
    return S_OK;
}

shared_ptr<CLevel_GamePlay> CLevel_GamePlay::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_GamePlay>(new CLevel_GamePlay(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}