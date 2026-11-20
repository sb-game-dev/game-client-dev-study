#include "Player.h"

#include "Body_Player.h"
#include "Weapon.h"

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
    if (GetKeyState(VK_LEFT) & 0x8000)
    {
        m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta * -1.f);
    }
    if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta);
    }
    if (GetKeyState(VK_DOWN) & 0x8000)
    {
        m_pTransformCom->Go_Backward(fTimeDelta);
    }
    if (GetKeyState(VK_UP) & 0x8000)
    {
        m_pTransformCom->Go_Straight(fTimeDelta);

        if(m_iState & STATE::IDLE)
            m_iState ^= STATE::IDLE;

        m_iState |= STATE::RUN;
    }
    else
    {
        if (m_iState & STATE::RUN)
            m_iState ^= STATE::RUN;

        m_iState |= STATE::IDLE;
    }

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
    BodyDesc.pParentTransformCom = m_pTransformCom;
    BodyDesc.pParentState = &m_iState;

    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Body_Player"),
        TEXT("Part_Body"), &BodyDesc)))
        return E_FAIL;

    CWeapon::WEAPON_DESC     WeaponDesc{};
    WeaponDesc.pParentTransformCom = m_pTransformCom;
    WeaponDesc.pParentState = &m_iState;
    WeaponDesc.pSocketMatrix = dynamic_pointer_cast<CBody_Player>(m_PartObjects[TEXT("Part_Body")])->Get_SocketMatrix("SWORD");

    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Weapon"),
        TEXT("Part_Weapon"), &WeaponDesc)))
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