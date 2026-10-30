#include "Level_GamePlay.h"

#include "GameInstance.h"
#include "Camera_Free.h"

CLevel_GamePlay::CLevel_GamePlay(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CLevel{ pDevice, pContext }
{
}

HRESULT CLevel_GamePlay::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
        return E_FAIL;

    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;

    return S_OK;
}

void CLevel_GamePlay::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

}

HRESULT CLevel_GamePlay::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

#ifdef _DEBUG
    SetWindowText(g_hWnd, TEXT("게임플레이 레벨입니다."));
#endif

    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const tchar_t* pLayerTag)
{
    CCamera_Free::CAMERA_FREE_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;
    CameraDesc.fSpeedPerSec = 20.f;
    CameraDesc.vEye = float4_t(-10.f, 10.f, -10.f, 1.f);
    CameraDesc.vAt = float4_t(0.f, 0.f, 0.f, 1.f);
    CameraDesc.fFovy = 60.f;
    CameraDesc.fNear = 0.1f;
    CameraDesc.fFar = 1000.f;
    CameraDesc.fSensor = 0.05f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Camera_Free"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag, &CameraDesc)))
        return E_FAIL;

    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Terrain"),
        ETOUI(LEVEL::GAMEPLAY), pLayerTag)))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CLevel_GamePlay> CLevel_GamePlay::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_GamePlay>(new CLevel_GamePlay(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CLevel_GamePlay");
        pInstance.reset();
    }

    return pInstance;
}

