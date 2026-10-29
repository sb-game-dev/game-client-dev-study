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
    Ready_Layer_BackGround(TEXT("Layer_BackGround"));
    Ready_Layer_GameObject(TEXT("Layer_GameObject"));

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

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Client_Mouse,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Client_Mouse)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Hill,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Hill)))
        return E_FAIL;

    CPlayer::PLAYER_DESC Player_Desc{};
    Player_Desc.fDegreeRotPerSec = 180.f;
    Player_Desc.fPosX = 38.2f;     
    Player_Desc.fPosZ = -207.2f;

    if(FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Player, 
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Player, &Player_Desc)))
        return E_FAIL;

    for (int i = 0; i < 16; ++i)
    {
        CCube::CUBE_DESC Cube_Desc{};
        Cube_Desc.fPosX = 38.2f + 10 * sinf(XM_2PI / 16 * i);
        Cube_Desc.fPosZ = -207.2f + 10 * cosf(XM_2PI / 16 * i);

        if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Cube,
            ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Cube + to_wstring(i), &Cube_Desc)))
            return E_FAIL;
    }

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Cube_Instance,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Cube_Instance)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Wave,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Wave)))
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

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Tree,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Tree)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), Proto::Obj_Scope,
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Scope)))
        return E_FAIL;

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Player);
    auto pMirror = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, GO::Mirror);
    CGameInstance::Get().Set_Mirror(pMirror);

    auto pCamera = CQuarterView_Cam::Create(m_pDevice, m_pContext);
    CGameInstance::Get().Add_Camera(CAMERA::QUARTERVIEW, pCamera);
    CGameInstance::Get().Set_MainCamera(CAMERA::QUARTERVIEW);
    pCamera->SetPlayer(pPlayer);

    //auto pCamera = CFree_Cam::Create(m_pDevice, m_pContext);
    //CGameInstance::Get().Add_Camera(CAMERA::FREE, pCamera);
    //CGameInstance::Get().Set_MainCamera(CAMERA::FREE);
    

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

shared_ptr<CLevel_GamePlay> CLevel_GamePlay::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_GamePlay>(new CLevel_GamePlay(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}