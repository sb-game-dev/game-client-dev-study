#include "Level_GamePlay.h"
#include "Cube.h"
#include "Player.h"
#include "Hill.h"
#include "Player_PointLight.h"
#include "Player_SpotLight.h"
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
    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    if(FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Player"), 
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Player"))))
        return E_FAIL;

    for (int i = 0; i < 16; ++i)
    {
        if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Prototype_GameObject_Cube" + to_wstring(i),
            ETOUI(LEVEL::GAMEPLAY), pLayerTag, L"Prototype_GameObject_Cube" + to_wstring(i))))
            return E_FAIL;
    }
    
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Hill"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Hill"))))
        return E_FAIL;

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Player"));
    auto pHill = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Hill"));

    auto m_pCamera = CQuarterView_Cam::Create(m_pDevice, m_pContext);
    CGameInstance::Get().Add_Camera(TEXT("QuarterViewCam"), m_pCamera);
    CGameInstance::Get().Set_MainCamera(TEXT("QuarterViewCam"));
    
    m_pCamera->SetPlayer(pPlayer);
    static_pointer_cast<CPlayer>(pPlayer)->SetHill(static_pointer_cast<CHill>(pHill));

    auto pPlayer_PointLight = CPlayer_PointLight::Create(m_pDevice, m_pContext);
    pPlayer_PointLight->SetPlayer(pPlayer);
    CGameInstance::Get().AddLight(L"Player_PointLight", pPlayer_PointLight);


    auto pPlayer_SpotLight = CPlayer_SpotLight::Create(m_pDevice, m_pContext);
    pPlayer_SpotLight->SetPlayer(pPlayer);
    CGameInstance::Get().AddLight(L"Player_SpotLight", pPlayer_SpotLight);

    return S_OK;
}

shared_ptr<CLevel_GamePlay> CLevel_GamePlay::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_GamePlay>(new CLevel_GamePlay(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}