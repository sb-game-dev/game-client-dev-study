#include "Level_ZeroZone.h"
#include "Cube.h"
#include "Player.h"
#include "Hill.h"
#include "Player_PointLight.h"
#include "Player_SpotLight.h"
#include "SunLight.h"
#include "Mirror.h"
#include "Free_Cam.h"
#include "QuarterView_Cam.h"
#include "Bullet.h"
#include "Weapon.h"
#include "TargetDummy.h"
#include "Bullet_Manager.h"

CLevel_ZeroZone::CLevel_ZeroZone(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_ZeroZone::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    CGameInstance::Get().Set_LayerActive(ETOUI(LEVEL::STATIC), L"Layer_Static", true);

    //auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Player);
    //pPlayer->Get_Transform()->Set_State(STATE::POSITION, XMVectorSet(-4.96f, 0.038f, -87.38f, 1.f));

    SetWindowText(g_hWnd, L"GamePlay_Level");
    if(FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    if(FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
        return E_FAIL;
    if(FAILED(Load_Scene(TEXT("../../../Resource/SceneData/exData.bin"),ETOUI(LEVEL::ZEROZONE),TEXT("Layer_GameObject"))))
        return E_FAIL;



    return S_OK;
}

void CLevel_ZeroZone::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    auto Player = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), TEXT("Layer_Static"), GO::Player);
    if (nullptr == Player)
        return;
    auto pBulletManager = dynamic_pointer_cast<CBullet_Manager>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), TEXT("Layer_Static"), GO::Bullet_Manager));
    if (nullptr == pBulletManager)
        return;
    auto Weapon = dynamic_pointer_cast<CPlayer>(Player)->Get_Weapon();
    auto GamePlayLevelObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::ZEROZONE), TEXT("Layer_GameObject"));

    shared_ptr<CCollider> pCollider;
    vector<shared_ptr<CGameObject>> Objects;

    for (auto& [strName, GamePlayLevelObject] : *GamePlayLevelObjects)
    {
        if (SUCCEEDED(GamePlayLevelObject->Get_Component(pCollider)))
            Objects.push_back(GamePlayLevelObject);
    }
    pBulletManager->Check_Collision(Objects);

    Objects.push_back(Weapon);
    Process_Collision(Objects);

    //Process_Collision(*StaticObjects,*GamePlayLevelObjects);
}

HRESULT CLevel_ZeroZone::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}
HRESULT CLevel_ZeroZone::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::ZEROZONE), Proto::Obj_SkyBox,
        ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::SkyBox)))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_ZeroZone::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    CHill::HILL_DESC Hill_Desc{};
    Hill_Desc.iLevelIndex = ETOUI(LEVEL::ZEROZONE);
    Hill_Desc.strMeshPath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw");  // ÁöÇü ¹öÆÛ + ³ôÀÌ¸Ê
    Hill_Desc.strTexturePath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png");            // È¥ÇÕ¸Ê
    Hill_Desc.strLayerPath = TEXT("Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png");              // ·¹ÀÌ¾î
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::ZEROZONE), Proto::Obj_Hill,
        ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::Hill, &Hill_Desc)))
        return E_FAIL;

    for (int i = 0; i < 16; ++i)
    {
        CTargetDummy::TARGETDUMMY_DESC TargetDummy_Desc{};
        f32_t fPosX = 38.2f + 10 * sinf(XM_2PI / 16 * i);
        f32_t fPosZ = -207.2f + 10 * cosf(XM_2PI / 16 * i);
    
        TargetDummy_Desc.vPosition = { fPosX ,0.f,fPosZ };
        TargetDummy_Desc.iLevelIndex = ETOUI(LEVEL::ZEROZONE);
        if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::ZEROZONE), Proto::Obj_TargetDummy,
            ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::TargetDummy + to_wstring(i), &TargetDummy_Desc)))
            return E_FAIL;
    }

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::ZEROZONE), Proto::Obj_Fog,
        ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::Fog)))
        return E_FAIL;

    CMirror::MIRROR_DESC Mirror_Desc{};
    Mirror_Desc.fPosX = 50.2f;
    Mirror_Desc.fPosY = 0.f;
    Mirror_Desc.fPosZ = -180.2f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::ZEROZONE), Proto::Obj_Mirror,
        ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::Mirror, &Mirror_Desc)))
        return E_FAIL;

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Player);
    auto pMirror = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::Mirror);
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

HRESULT CLevel_ZeroZone::Ready_Layer_Camera(const tchar_t* pLayerTag)
{
    CQuarterView_Cam::CAMERA_QUATER_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;
    CameraDesc.fSpeedPerSec = 20.f;
    CameraDesc.vEye = float4_t(-10.f, 10.f, -10.f, 1.f);
    CameraDesc.vAt = float4_t(0.f, 0.f, 0.f, 1.f);
    CameraDesc.fFovy = 20.f;
    CameraDesc.fNear = 0.3f;
    CameraDesc.fFar = 300.f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::ZEROZONE), Proto::Obj_QuaterViewCam,
        ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::QuaterViewCam, &CameraDesc)))
        return E_FAIL;

    auto pQuaterViewCam = dynamic_pointer_cast<CQuarterView_Cam>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::ZEROZONE), pLayerTag, GO::QuaterViewCam));
    CGameInstance::Get().Add_Camera(CAMERA::QUARTERVIEW, pQuaterViewCam);
    CGameInstance::Get().Set_MainCamera(CAMERA::QUARTERVIEW);
    return S_OK;
}

shared_ptr<CLevel_ZeroZone> CLevel_ZeroZone::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_ZeroZone>(new CLevel_ZeroZone(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}