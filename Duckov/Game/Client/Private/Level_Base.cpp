#include "Level_Base.h"
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

CLevel_Base::CLevel_Base(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_Base::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    CGameInstance::Get().Set_LayerActive(ETOUI(LEVEL::STATIC), L"Layer_Static", true);

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Player);
    pPlayer->Get_Transform()->Set_State(STATE::POSITION, XMVectorSet(-4.96f, 0.038f, -87.38f, 1.f));

    SetWindowText(g_hWnd, L"GamePlay_Level");
    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
        return E_FAIL;
    //if (FAILED(Load_Scene(TEXT("../../../Resource/SceneData/exData.bin"), ETOUI(LEVEL::BASE), TEXT("Layer_GameObject"))))
    //    return E_FAIL;

    return S_OK;
}

void CLevel_Base::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    auto Player = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), TEXT("Layer_Static"), GO::Player);
    if (nullptr == Player)
        return;
    auto pBulletManager = dynamic_pointer_cast<CBullet_Manager>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), TEXT("Layer_Static"), GO::Bullet_Manager));
    if (nullptr == pBulletManager)
        return;
    auto Weapon = dynamic_pointer_cast<CPlayer>(Player)->Get_Weapon();
    auto BaseLevelObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::BASE), TEXT("Layer_GameObject"));

    shared_ptr<CCollider> pCollider;
    vector<shared_ptr<CGameObject>> Objects;

    for (auto& [strName, GamePlayLevelObject] : *BaseLevelObjects)
    {
        if (SUCCEEDED(GamePlayLevelObject->Get_Component(pCollider)))
            Objects.push_back(GamePlayLevelObject);
    }
    pBulletManager->Check_Collision(Objects);

    Objects.push_back(Weapon);
    Process_Collision(Objects);

    //Process_Collision(*StaticObjects,*BaseLevelObjects);
}

HRESULT CLevel_Base::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}
HRESULT CLevel_Base::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::BASE), Proto::Obj_BaseTerrain1,
        ETOUI(LEVEL::BASE), pLayerTag, GO::BaseTerrain1)))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_Base::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    const f32_t fDummyZ[] = { -75.001f, -73.211f, -71.411f, -69.691f, -67.991f, -66.271f };

    const wchar_t* pHelmetTags[] = {nullptr,Proto::Model_Helmet_LV1,Proto::Model_Helmet_LV2 ,Proto::Model_Helmet_LV3 ,Proto::Model_Helmet_LV4 ,Proto::Model_Helmet_LV5 };
    const wchar_t* pArmorTags[] = {nullptr,Proto::Model_Armor_LV1,Proto::Model_Armor_LV2 ,Proto::Model_Armor_LV3 ,Proto::Model_Armor_LV4 ,Proto::Model_Armor_LV5 };
    for(uint32_t i=0;i<6;++i)
    {
        f32_t fZ = fDummyZ[i];
        CTargetDummy::TARGETDUMMY_DESC TargetDummy_Desc{};
        TargetDummy_Desc.iLevelIndex = ETOUI(LEVEL::BASE);
        TargetDummy_Desc.vPosition = { -44.691f, 0.f, fZ };
        TargetDummy_Desc.pHelmetTag = pHelmetTags[i];
        TargetDummy_Desc.pArmorTag = pArmorTags[i];

        if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::BASE), Proto::Obj_TargetDummy,
            ETOUI(LEVEL::BASE), pLayerTag, GO::TargetDummy + to_wstring(i), &TargetDummy_Desc)))
            return E_FAIL;
    }

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::BASE), Proto::Obj_Fog,
        ETOUI(LEVEL::BASE), pLayerTag, GO::Fog)))
        return E_FAIL;

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Player);

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

HRESULT CLevel_Base::Ready_Layer_Camera(const tchar_t* pLayerTag)
{
    CQuarterView_Cam::CAMERA_QUATER_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;
    CameraDesc.fSpeedPerSec = 20.f;
    CameraDesc.vEye = float4_t(-10.f, 10.f, -10.f, 1.f);
    CameraDesc.vAt = float4_t(0.f, 0.f, 0.f, 1.f);
    CameraDesc.fFovy = 20.f;
    CameraDesc.fNear = 0.3f;
    CameraDesc.fFar = 300.f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::BASE), Proto::Obj_QuaterViewCam,
        ETOUI(LEVEL::BASE), pLayerTag, GO::QuaterViewCam, &CameraDesc)))
        return E_FAIL;

    auto pQuaterViewCam = dynamic_pointer_cast<CQuarterView_Cam>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::BASE), pLayerTag, GO::QuaterViewCam));
    CGameInstance::Get().Add_Camera(CAMERA::QUARTERVIEW, pQuaterViewCam);
    CGameInstance::Get().Set_MainCamera(CAMERA::QUARTERVIEW);
    return S_OK;
}

shared_ptr<CLevel_Base> CLevel_Base::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_Base>(new CLevel_Base(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}