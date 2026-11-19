#include "Player.h"

#include "Body_Player.h"

CPlayer::CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CContainerObject { pDevice, pContext }
{
}

HRESULT CPlayer::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
    PLAYER_DESC         PlayerDesc{};

    PlayerDesc.fSpeedPerSec = 10.f;
    PlayerDesc.fDegreeRotPerSec = 180.f;   

    if (FAILED(__super::Initialize(&PlayerDesc)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    if (FAILED(Ready_PartObjects()))
        return E_FAIL;

    return S_OK;
}

void CPlayer::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CPlayer::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
}

void CPlayer::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
}

HRESULT CPlayer::Render()
{
    return S_OK;
}

HRESULT CPlayer::Ready_Components()
{
    return S_OK;
}

HRESULT CPlayer::Ready_PartObjects()
{
    CBody_Player::BODY_DESC     BodyDesc{};

    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObejct_Body_Player"),
        TEXT("Part_Body"), &BodyDesc)))
        return E_FAIL;



    return S_OK;
}

shared_ptr<CPlayer> CPlayer::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CPlayer>(new CPlayer(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CPlayer");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CPlayer::Clone(void* pArg)
{
    shared_ptr<CPlayer> pInstance = shared_ptr<CPlayer>(new CPlayer(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CPlayer");
        pInstance.reset();
    }

    return pInstance;
}