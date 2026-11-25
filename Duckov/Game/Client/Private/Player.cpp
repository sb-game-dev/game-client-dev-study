#include "Player.h"
#include "Inven.h"
#include "Hill.h"
#include "Body_Player.h"
#include "Weapon.h"
#include "Helmet.h"
#include "Armor.h"
#include "BackPack.h"
#include "Headset.h"
#include "FaceMask.h"
#include "Client_Mouse.h"
#include "UI_Player.h"

namespace {
    vector_t	g_vY_Plus = XMVector4Normalize({ 0.f,+1.f,0.f,0.f });
    vector_t	g_vY_Minus = XMVector4Normalize({ 0.f,-1.f,0.f,0.f });
}

CPlayer::CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CContainerObject(pDevice, pContext)
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
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_PartObjects()))
        return E_FAIL;

    return S_OK;
}

void CPlayer::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);

    m_bAiming = false;
    m_bFiring = false;
    auto pMouse = m_pClientMouse.lock();
    if (nullptr == pMouse)
    {
        pMouse = dynamic_pointer_cast<CClient_Mouse>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Client_Mouse));
        if (nullptr == pMouse)
            return;
        m_pClientMouse = pMouse;
    }
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
    {
        pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::STATIC), L"Layer_Static", L"GameObject_Inven"));
        if (nullptr == pInven)
            return;
        m_pInven = pInven;
    }

    m_bCurInvenOpen = (nullptr != pInven && pInven->Is_Open());
    if (m_bCurInvenOpen)
        m_tInput = {};
    else
    {
        Key_Input();

        Update_State(fDeltaTime);

        Update_Stamina(fDeltaTime);
        Update_Hunger(fDeltaTime);
        Update_Thirst(fDeltaTime);

        Handle_SlotInput(fDeltaTime);

        AdjustPosY();
    }
    m_bPreInvenOpen = m_bCurInvenOpen;
}

void CPlayer::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CPlayer::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

HRESULT CPlayer::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
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
    BodyDesc.pGroundPlane = &m_vGroundPlane;

    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_Player_Body,
        TEXT("Part_Body"), &BodyDesc)))
        return E_FAIL;
    m_pBodyPlayer = dynamic_pointer_cast<CBody_Player>(m_PartObjects[TEXT("Part_Body")]);

    CWeapon::WEAPON_DESC        WeaponDesc{};
    WeaponDesc.pParentTransformCom = m_pTransformCom;
    WeaponDesc.pSocketMatrix = m_pBodyPlayer->Get_SocketMatrix("Hand.R");
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_Weapon,
        TEXT("Part_Weapon"), &WeaponDesc)))
        return E_FAIL;
    m_pWeapon = dynamic_pointer_cast<CWeapon>(m_PartObjects[TEXT("Part_Weapon")]);

    CHelmet::HELMET_DESC        HelmetDesc{};
    HelmetDesc.pParentTransformCom = m_pTransformCom;
    HelmetDesc.pSocketMatrix = m_pBodyPlayer->Get_SocketMatrix("Head");
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_Helmet,
        TEXT("Part_Helmet"), &HelmetDesc)))
        return E_FAIL;
    
    CArmor::ARMOR_DESC        ArmorDesc{};
    ArmorDesc.pParentTransformCom = m_pTransformCom;
    ArmorDesc.pSocketMatrix = m_pBodyPlayer->Get_SocketMatrix("Spine.001");
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_Armor,
        TEXT("Part_Armor"), &ArmorDesc)))
        return E_FAIL;
    
    CBackPack::BACKPACK_DESC    BackPackDesc{};
    BackPackDesc.pParentTransformCom = m_pTransformCom;
    BackPackDesc.pSocketMatrix = m_pBodyPlayer->Get_SocketMatrix("Spine.001");
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_BackPack,
        TEXT("Part_BackPack"), &BackPackDesc)))
        return E_FAIL;

    CHeadset::HEADSET_DESC    HeadsetDesc{};
    HeadsetDesc.pParentTransformCom = m_pTransformCom;
    HeadsetDesc.pSocketMatrix = m_pBodyPlayer->Get_SocketMatrix("Head");
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_Headset,
        TEXT("Part_Headset"), &HeadsetDesc)))
        return E_FAIL;

    CFaceMask::FACEMASK_DESC    FaceMaskDesc{};
    FaceMaskDesc.pParentTransformCom = m_pTransformCom;
    FaceMaskDesc.pSocketMatrix = m_pBodyPlayer->Get_SocketMatrix("Head");
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_FaceMask,
        TEXT("Part_FaceMask"), &FaceMaskDesc)))
        return E_FAIL;

    CUI_Player::UIPLAYER_DESC    UI_PlayerDesc{};
    UI_PlayerDesc.pParentTransformCom = m_pTransformCom;
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_UI_Player,
        TEXT("Part_UI"), &UI_PlayerDesc)))
        return E_FAIL;

    return S_OK;
}

void CPlayer::AdjustPosY()
{
    auto pHill = m_pHill.lock();
    if (nullptr == pHill)
    {
        pHill = dynamic_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Hill"));
        if (nullptr == pHill)
            return;
        m_pHill = pHill;
    }

    vector_t  vPos = m_pTransformCom->Get_State(STATE::POSITION);
    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.1f);
    m_pTransformCom->Set_State(STATE::POSITION, vPos);
    m_vGroundPlane = pHill->GetPlane(x, z);
}
void CPlayer::Key_Input()
{
    m_tInput = {};
    auto& GI = CGameInstance::Get();
    if (GI.Key_Pressing(DIK_W)) m_tInput.fMoveZ += 1.f;
    if (GI.Key_Pressing(DIK_S)) m_tInput.fMoveZ -= 1.f;
    if (GI.Key_Pressing(DIK_A)) m_tInput.fMoveX -= 1.f;
    if (GI.Key_Pressing(DIK_D)) m_tInput.fMoveX += 1.f;

    m_tInput.bSprint        = GI.Key_Pressing(DIK_LSHIFT);
    m_tInput.bAim           = GI.Mouse_Pressing(DIM::RB);
    m_tInput.bFire          = GI.Mouse_Pressing(DIM::LB);
    m_tInput.bRoll          = GI.Key_Down(DIK_SPACE);
    m_tInput.bSlot1         = GI.Key_Down(DIK_1);
    m_tInput.bSlot2         = GI.Key_Down(DIK_2);
    m_tInput.bSlotMelee     = GI.Key_Down(DIK_V);
}

void CPlayer::Update_State(f32_t fDeltaTime)
{
    switch (m_eState)
    {
    case Client::CPlayer::PLAYER_STATE::IDLE:           Update_State_Idle(fDeltaTime);          break;
    case Client::CPlayer::PLAYER_STATE::WALK:           Update_State_Walk(fDeltaTime);          break;
    case Client::CPlayer::PLAYER_STATE::SPRINT:         Update_State_Sprint(fDeltaTime);        break;
    case Client::CPlayer::PLAYER_STATE::ROLL:           Update_State_Roll(fDeltaTime);          break;
    case Client::CPlayer::PLAYER_STATE::ATTACK:         Update_State_Attack(fDeltaTime);        break;
    }
}

void CPlayer::Initialize_State(PLAYER_STATE eNext)
{
    // 플레이어의 상태가 바뀌는 순간에만 설정해야 하는 값들
    if (eNext == m_eState)
        return;
    m_eState = eNext;
    switch (m_eState)
    {
    case Client::CPlayer::PLAYER_STATE::SPRINT:
        m_bSlowTrun = true;
        m_pTransformCom->Set_Speed(16.f);
        Change_Animation(PLAYER_ANIM::WALK_FORWARD, false, 2.f);
        break;
    case Client::CPlayer::PLAYER_STATE::ROLL:
        if (m_fStamina >= m_fRollStamina)
        {
            m_fStamina -= m_fRollStamina;
            if (m_fStamina <= 0.f)
            {
                m_fStamina = 0.f;
                m_bStaminaLock = true;
            }
            m_bSlowTrun = true;
            m_bRolling = true;
            m_pTransformCom->Set_Speed(20.f);

            XMStoreFloat4(&m_vRollStartMoveDir, Has_MoveInput() ? Calc_MoveDir() : m_pTransformCom->Get_State(STATE::LOOK));
        }
        break;
    case Client::CPlayer::PLAYER_STATE::ATTACK:
        Change_Animation(PLAYER_ANIM::ATTACK_L2R, true, 1.5f, 0.01f);
        break;
    default: 
        m_pTransformCom->Set_Speed(8.f);
        break;
    }
}
void CPlayer::Update_State_Idle(f32_t fDeltaTime)
{
    // IDLE -> ROLL, ATTACK, WALK
    if (m_tInput.bRoll && Can_Roll())                                       { Initialize_State(PLAYER_STATE::ROLL); return; }
    if (m_tInput.bFire && Is_MeleeSlot() && Has_Weapon() && m_bCanAttack)   { Initialize_State(PLAYER_STATE::ATTACK); return; }
    if (Has_MoveInput())                                                    { Initialize_State(PLAYER_STATE::WALK); return; }

    m_bAiming = m_tInput.bAim;
    m_bFiring = m_tInput.bFire;
    
    Change_Animation(PLAYER_ANIM::IDLE);
    LookAtMouse(fDeltaTime);
}
void CPlayer::Update_State_Walk(f32_t fDeltaTime)
{
    // WALK -> ROLL, SPRINT, ATTACK, IDLE
    if (m_tInput.bRoll && Can_Roll())                                       { Initialize_State(PLAYER_STATE::ROLL); return; }
    if (m_tInput.bSprint && Can_Sprint())                                   { Initialize_State(PLAYER_STATE::SPRINT); return; }
    if (m_tInput.bFire && Is_MeleeSlot() && Has_Weapon() && m_bCanAttack)   { Initialize_State(PLAYER_STATE::ATTACK); return; }
    if (!Has_MoveInput())                                                   { Initialize_State(PLAYER_STATE::IDLE);   return; }

    m_bAiming = m_tInput.bAim;
    m_bFiring = m_tInput.bFire;

    auto pMouse = m_pClientMouse.lock();
    if (nullptr == pMouse)
        return;
    vector_t vTargetDir = pMouse->Get_Transform()->Get_State(STATE::POSITION) - m_pTransformCom->Get_State(STATE::POSITION);
    vector_t vMoveDir = Calc_MoveDir();
    f32_t fDot = XMVectorGetX(XMVector3Dot(XMVector4Normalize(vMoveDir), XMVector4Normalize(vTargetDir)));
    
    if(fDot> cosf(XM_PI / 4))        { Change_Animation(PLAYER_ANIM::WALK_FORWARD);}
    else if(fDot < -cosf(XM_PI / 4)) { Change_Animation(PLAYER_ANIM::WALK_BACKWARD);}
    else                             { Change_Animation(PLAYER_ANIM::WALK_LEFT); }

    LookAtMouse(fDeltaTime);
    m_pTransformCom->Move_Position(Calc_MoveDir(), fDeltaTime);
}

void CPlayer::Update_State_Sprint(f32_t fDeltaTime)
{
    // SPRINT -> ROLL, WALK
    if (m_tInput.bRoll && Can_Roll())                               { Initialize_State(PLAYER_STATE::ROLL); return; }
    if (!m_tInput.bSprint || m_bStaminaLock || !Has_MoveInput())    { Initialize_State(Has_MoveInput() ? PLAYER_STATE::WALK : PLAYER_STATE::IDLE); return; }

    vector_t vMoveDir = Calc_MoveDir();
    m_pTransformCom->Move_Position(vMoveDir, fDeltaTime);
    Turn_Toward(vMoveDir, fDeltaTime);
}

void CPlayer::Update_State_Roll(f32_t fDeltaTime)
{
    m_pBodyPlayer->Set_UpperAnimationInActive(0.01f);
    m_bSwapping = false;
    m_bCanAttack = false;
    Change_Animation(PLAYER_ANIM::ROLL, false, 1.f, 0.01f);
    // 키입력이 있다면 이동 방향은 키입력 방향, 없다면 마우스방향(Look 방향)
    vector_t vMoveDir = Has_MoveInput() ? Calc_MoveDir() : m_pTransformCom->Get_State(STATE::LOOK);
    
    // 키입력이 있다면 구를 때 키입력 방향으로 굴러야 한다.
    if (Has_MoveInput())
        m_pTransformCom->LookAt(m_pTransformCom->Get_State(STATE::POSITION) + XMLoadFloat4(&m_vRollStartMoveDir));

    // 구르기 속도 설정
    m_pTransformCom->Set_Speed(m_pTransformCom->Get_Speed() * 0.95f);
    // 구르기 이동
    m_pTransformCom->Move_Position(XMLoadFloat4(&m_vRollStartMoveDir), fDeltaTime);

    // 구르기가 끝났다면 IDLE상태
    if (m_pBodyPlayer->Is_Animation_Finished())
    {
        m_bRolling = false;
        m_bCanAttack = true;
        Initialize_State(PLAYER_STATE::IDLE);
        if (Has_Weapon())
            Change_Animation(PLAYER_ANIM::IDLE_RH, true);
    }
}

void CPlayer::Update_State_Attack(f32_t fDeltaTime)
{
    LookAtMouse(fDeltaTime);

    if (Has_MoveInput())
    {
        Change_Animation(PLAYER_ANIM::WALK_FORWARD);
        m_pTransformCom->Move_Position(Calc_MoveDir(), fDeltaTime);
    }
    else
    {
        Change_Animation(PLAYER_ANIM::IDLE);
    }

    if (m_pBodyPlayer->Is_Animation_Finished(true))
    {
        m_pBodyPlayer->Set_UpperAnimationInActive();
        Initialize_State(Has_MoveInput() ? PLAYER_STATE::WALK : PLAYER_STATE::IDLE);
        if (Has_Weapon())
            Change_Animation(PLAYER_ANIM::IDLE_RH, true);
    }
}

void CPlayer::Play_Swap_Weapon_Anim_WeaponToWeapon(f32_t fDeltaTime)
{
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
        return;
    m_fSwapWeaponTime += fDeltaTime;
    if (m_fSwapWeaponTime < 0.2f)
    {
        Change_Animation(PLAYER_ANIM::WALK_RIGHT, true);
        m_bCanAttack = false;
    }
    else if (m_fSwapWeaponTime < 0.4f)
    {
        if (EQUIP_SLOT::END != m_eSwapNextWeapon)
            pInven->Set_ActiveSlot(m_eSwapNextWeapon);
        Change_Animation(PLAYER_ANIM::IDLE_RH, true);
        m_bCanAttack = false;
    }
    else
    {
        m_bCanAttack = true;
        m_bSwapping = false;
    }
}

void CPlayer::Play_Swap_Weapon_Anim_EdleToWeapon(f32_t fDeltaTime)
{
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
        return;
    m_fSwapWeaponTime += fDeltaTime;
    if (m_fSwapWeaponTime < 0.2f)
    {
        if (EQUIP_SLOT::END != m_eSwapNextWeapon)
            pInven->Set_ActiveSlot(m_eSwapNextWeapon);
        Change_Animation(PLAYER_ANIM::IDLE_RH, true, 0.f);
        m_bCanAttack = false;
    }
    else
    {
        m_bCanAttack = true;
        m_bSwapping = false;
    }
}

void CPlayer::Handle_SlotInput(f32_t fDeltaTime)
{
    if (PLAYER_STATE::ROLL == m_eState || PLAYER_STATE::ATTACK == m_eState)
        return;

    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
        return;
    
    if (pInven->Get_ActiveSlot() == EQUIP_SLOT::GUN_1 && m_tInput.bSlot1) return;
    if (pInven->Get_ActiveSlot() == EQUIP_SLOT::GUN_2 && m_tInput.bSlot2) return;
    if (pInven->Get_ActiveSlot() == EQUIP_SLOT::MELEE && m_tInput.bSlotMelee) return;

    if (m_tInput.bSlot1 || m_tInput.bSlot2 || m_tInput.bSlotMelee || (!m_bCurInvenOpen && m_bPreInvenOpen) )
    {
        m_bPreHasWeapon = Has_Weapon();
        m_bSwapping = true;
        m_fSwapWeaponTime = 0.f;
    }
    
    if (m_tInput.bSlot1)            m_eSwapNextWeapon = EQUIP_SLOT::GUN_1;
    else if (m_tInput.bSlot2)       m_eSwapNextWeapon = EQUIP_SLOT::GUN_2;
    else if (m_tInput.bSlotMelee)   m_eSwapNextWeapon = EQUIP_SLOT::MELEE;

    if (m_bSwapping)
    {
        if (nullptr == pInven->GetEquipSlot(m_eSwapNextWeapon))
        {
            // 무기 슬롯이 없는 곳으로 이동하면 자동으로 상체 애니메이션을 끄고 스왑 상태를 끈다.
            // 스왑상태를 꺼서 아래의 스왑 애니메이션이 작동하지 않고 하체의 애니메이션(IDLE or Walk)과 보간된다.
            pInven->Set_ActiveSlot(m_eSwapNextWeapon);
            m_pBodyPlayer->Set_UpperAnimationInActive();
            m_bSwapping = false;
        }
        else if (m_bPreHasWeapon)
            Play_Swap_Weapon_Anim_WeaponToWeapon(fDeltaTime);
        else
            Play_Swap_Weapon_Anim_EdleToWeapon(fDeltaTime);
    }
}

bool_t CPlayer::Has_Weapon()
{
    return nullptr != m_pInven.lock() && m_pInven.lock()->Get_ActiveItem() != nullptr;
}

bool_t CPlayer::Is_MeleeSlot()
{
    return nullptr != m_pInven.lock() && m_pInven.lock()->Get_ActiveSlot() == EQUIP_SLOT::MELEE;
}

vector_t CPlayer::Calc_MoveDir()
{
    matrix_t matCamWorld = CGameInstance::Get().Get_Perspective_Transform_Inverse(D3DTS::VIEW);
    vector_t vCamRight = XMVector3Normalize(XMVectorSetY(matCamWorld.r[0], 0.f));
    vector_t vCamLook = XMVector3Normalize(XMVectorSetY(matCamWorld.r[2], 0.f));

    return XMVector3Normalize(vCamRight * m_tInput.fMoveX + vCamLook * m_tInput.fMoveZ);
}

void CPlayer::Turn_Toward(vector_t vMoveDir, f32_t fDeltaTime)
{
    vector_t vLook = m_pTransformCom->Get_State(STATE::LOOK);
    vLook = XMVector3Normalize(XMVectorSetY(vLook, 0.f));
    f32_t fDot = XMVectorGetX(XMVector3Dot(vLook, vMoveDir));
    if (fDot < cosf(XMConvertToRadians(2.f)))
    {
        f32_t fCrossY = XMVectorGetY(XMVector3Cross(vLook, vMoveDir));
        m_pTransformCom->Turn(fCrossY > 0.f ? g_vY_Plus : g_vY_Minus, fDeltaTime);
    }
}

void CPlayer::LookAtMouse(f32_t fDeltaTime)
{
    auto pMouse = m_pClientMouse.lock();
    if (nullptr == pMouse)
        return;
    vector_t vTargetDir = pMouse->Get_Transform()->Get_State(STATE::POSITION) - m_pTransformCom->Get_State(STATE::POSITION);

    vector_t vLook = m_pTransformCom->Get_State(STATE::LOOK);
    vLook = XMVector3Normalize(XMVectorSetY(vLook, 0.f));
    
    f32_t fDot = XMVectorGetX(XMVector3Dot(vLook, vTargetDir));
    if (m_bSlowTrun)
    {
        if (fDot < cosf(XMConvertToRadians(0.01f)))
        {
            f32_t fCrossY = XMVectorGetY(XMVector3Cross(vLook, vTargetDir));
            m_pTransformCom->Turn(fCrossY > 0.f ? g_vY_Plus : g_vY_Minus, fDeltaTime * 5);
        }
        else
        {
            m_bSlowTrun = false;
        }
    }
    else
    {
        m_pTransformCom->LookAt(pMouse->Get_Transform()->Get_State(STATE::POSITION));
    }
}
void CPlayer::Change_Animation(PLAYER_ANIM eMoveState, bool_t bUpper, f32_t fAnimPlaySpeed, f32_t fBlendDuration)
{
    m_pBodyPlayer->Change_Animation(eMoveState, bUpper, fAnimPlaySpeed, fBlendDuration);
}

void CPlayer::Update_Stamina(f32_t fDeltaTime)
{
    if (PLAYER_STATE::SPRINT == m_eState)
    {
        m_fStamina -= fDeltaTime * m_fStaminaDecayRate;
        if (m_fStamina <= 0.f) { m_fStamina = 0.f; m_bStaminaLock = true; }
    }
    else if (PLAYER_STATE::ROLL != m_eState)
    {
        m_fStamina = min(m_fStamina + fDeltaTime * m_fStaminaRegenRate, m_fMaxStamina);
        if (m_fStamina > 20.f) m_bStaminaLock = false;
    }
}

void CPlayer::Update_Hunger(f32_t fDeltaTime)
{
    if (m_fHunger > fDeltaTime * m_fHungerDecayRate)
        m_fHunger -= fDeltaTime * m_fHungerDecayRate;
    else
        m_fHunger = 0.f;
}
void CPlayer::Update_Thirst(f32_t fDeltaTime)
{
    if (m_fThirst > fDeltaTime * m_fThirstDecayRate)
        m_fThirst -= fDeltaTime * m_fThirstDecayRate;
    else
        m_fThirst = 0.f;
}
shared_ptr<CPlayer> CPlayer::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CPlayer>(new CPlayer(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CPlayer");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CPlayer::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CPlayer>(new CPlayer(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CPlayer");
        pInstance.reset();
    }
    return pInstance;
}
