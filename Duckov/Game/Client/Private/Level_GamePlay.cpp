#include "Level_GamePlay.h"
#include "Cube.h"
#include "Player.h"
#include "Hill.h"
#include "Player_PointLight.h"
#include "Player_SpotLight.h"
#include "SunLight.h"

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
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_SkyBox"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_SkyBox"))))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_ClientMouse"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_ClientMouse"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Hill"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Hill"))))
        return E_FAIL;

    CPlayer::PLAYER_DESC Player_Desc{};
    Player_Desc.fDegreeRotPerSec = 180.f;
    if(FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Player"), 
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Player"), &Player_Desc)))
        return E_FAIL;

    for (int i = 0; i < 16; ++i)
    {
        CCube::CUBE_DESC Cube_Desc{};
        Cube_Desc.fPosX = 5 * sinf(XM_2PI / 16 * i);
        Cube_Desc.fPosZ = 5 * cosf(XM_2PI / 16 * i);

        if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Prototype_GameObject_Cube",
            ETOUI(LEVEL::GAMEPLAY), pLayerTag, L"GameObject_Cube" + to_wstring(i), &Cube_Desc)))
            return E_FAIL;
    }

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Prototype_GameObject_CubeInstance",
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, L"GameObject_CubeInstance")))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Wave"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Wave"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Fog"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Fog"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Mirror"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Mirror"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Tree"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Tree"))))
        return E_FAIL;

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Player"));
    auto pMirror = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Mirror"));
    CGameInstance::Get().Set_Mirror(pMirror);

    auto m_pCamera = CQuarterView_Cam::Create(m_pDevice, m_pContext);
    CGameInstance::Get().Add_Camera(TEXT("QuarterViewCam"), m_pCamera);
    
    m_pCamera->SetPlayer(pPlayer);

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