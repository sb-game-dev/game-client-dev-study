#include "Player.h"
#include "Inven.h"
#include "Hill.h"

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

    // 레스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    rsDesc.FrontCounterClockwise = true;        // 반사되면 감기 순서가 뒤집히므로 앞면 기준도 뒤집음
    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS_Reflect.GetAddressOf());
    return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    return S_OK;
}

void CPlayer::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);

    m_bAiming = false;
    m_bFiring = false;

    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
    {
        pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
        if (nullptr == pInven)
            return;
        m_pInven = pInven;
    }


    bool_t bInvenOpen = (nullptr != pInven && pInven->Is_Open());
    if (bInvenOpen)
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
}

void CPlayer::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    m_pModelCom->PlayAnimation(fDeltaTime);
}
void CPlayer::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    CGameInstance::Get().Add_RenderGroup(RENDERID::PLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::OCCLUDEDPLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::REFLECT, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CPlayer::Render()
{
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPSCom);
}

HRESULT CPlayer::Render_Reflection(const matrix_t& matReflect)
{
    return Render_Mesh(m_pTransformCom->Get_World() * matReflect, m_pRS_Reflect.Get(), m_pPSCom);
}

HRESULT CPlayer::Render_Shadow()
{
    XMVECTOR vPlane     = XMLoadFloat4(&m_vGroundPlane);
    XMVECTOR vToLight   = XMVectorSet(-0.5f, 0.5f, -0.5f, 0.f);  // SunLight Direction의 반대, w=0(평행광)

    matrix_t matShadow  = XMMatrixShadow(vPlane, vToLight);
    matrix_t matOffset  = XMMatrixTranslation(0.f, 0.01f, 0.f);  // 지형과 z-fighting 방지

    return Render_Mesh(m_pTransformCom->Get_World() * matShadow * matOffset, m_pRS.Get(), m_pPS_Shadow);
}

HRESULT CPlayer::Render_Occluded()
{
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS_Occluded);
}

HRESULT CPlayer::Ready_Components()
{
    if(FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Normalize_AssetPath(TEXT("Characters/S12_DuckV2_2/S12_DuckV2_2.fbx")),
        TEXT("Com_Model"),m_pModelCom)))
        return E_FAIL;

    m_pModelCom->Set_LowerAnimationIndex(ETOUI(m_eLowerMoveState),0.f);
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::WALK_FORWARD));
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::WALK_FORWARD_RH));
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::WALK_BACKWARD));
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::WALK_BACKWARD_RH));
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::WALK_LEFT));
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::WALK_LEFT_RH_OUT));
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::IDLE));
    m_pModelCom->Set_Animation_Loop(ETOUI(PLAYER_ANIM::IDLE_RH));

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_ANIM_MODEL,
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_SHADOW,
        TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_OCCLUDED,
        TEXT("Com_PS_OCCLUDED"), m_pPS_Occluded)))
        return E_FAIL;

    return S_OK;
}

HRESULT CPlayer::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof m_tCBData);
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

HRESULT CPlayer::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));

    return S_OK;
}

HRESULT CPlayer::Render_Mesh(const matrix_t& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(pRS);

    if (FAILED(Bind_Shader(m_pVSCom, pPS)))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(matWorld)))
        return E_FAIL;

    uint32_t    iNumMeshes = m_pModelCom->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModelCom->Bind_BoneMatrix(i, 2)))
            return E_FAIL;
        if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0)))
            return E_FAIL;

        //if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_NORMALS, 0, 1)))
        //    return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }
    return S_OK;
}

HRESULT CPlayer::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CPlayer::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
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
        Change_Animation(PLAYER_ANIM::WALK_FORWARD);
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
            m_pTransformCom->Set_Speed(20.f);

            XMStoreFloat4(&m_vRollStartMoveDir, Has_MoveInput() ? Calc_MoveDir() : m_pTransformCom->Get_State(STATE::LOOK));
            
            Change_Animation(PLAYER_ANIM::ROLL, false, 1.f, 0.01f);
        }
        break;
    case Client::CPlayer::PLAYER_STATE::ATTACK:
        if(m_bCanAttack) Change_Animation(rand() % 2 ? PLAYER_ANIM::ATTACK : PLAYER_ANIM::ATTACK_L2R, true, 1.5f, 0.01f);
        break;
    default: 
        m_pTransformCom->Set_Speed(8.f);
        break;
    }
}
void CPlayer::Update_State_Idle(f32_t fDeltaTime)
{
    // IDLE -> ROLL, ATTACK, WALK
    if (m_tInput.bRoll && Can_Roll())                       { Initialize_State(PLAYER_STATE::ROLL); return; }
    if (m_tInput.bFire && Is_MeleeSlot() && Has_Weapon())   { Initialize_State(PLAYER_STATE::ATTACK); return; }
    if (Has_MoveInput())                                    { Initialize_State(PLAYER_STATE::WALK); return; }

    m_bAiming = m_tInput.bAim;
    m_bFiring = m_tInput.bFire;
    
    Change_Animation(PLAYER_ANIM::IDLE);
    LookAtMouse(fDeltaTime);
}
void CPlayer::Update_State_Walk(f32_t fDeltaTime)
{
    // WALK -> ROLL, SPRINT, ATTACK, IDLE
    if (m_tInput.bRoll && Can_Roll())                       { Initialize_State(PLAYER_STATE::ROLL); return; }
    if (m_tInput.bSprint && Can_Sprint())                   { Initialize_State(PLAYER_STATE::SPRINT); return; }
    if (m_tInput.bFire && Is_MeleeSlot() && Has_Weapon())   { Initialize_State(PLAYER_STATE::ATTACK); return; }
    if (!Has_MoveInput())                                   { Initialize_State(PLAYER_STATE::IDLE);   return; }

    m_bAiming = m_tInput.bAim;
    m_bFiring = m_tInput.bFire;

    auto pMouse = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", GO::Client_Mouse);
    vector_t vTargetDir = pMouse->Get_Transform()->Get_State(STATE::POSITION) - m_pTransformCom->Get_State(STATE::POSITION);
    vector_t vMoveDir = Calc_MoveDir();
    f32_t fDot = XMVectorGetX(XMVector3Dot(XMVector4Normalize(vMoveDir), XMVector4Normalize(vTargetDir)));
    
    if(fDot> cosf(XM_PI / 4))        { Change_Animation(PLAYER_ANIM::WALK_FORWARD, false, 1.f, 0.25f);}
    else if(fDot < -cosf(XM_PI / 4)) { Change_Animation(PLAYER_ANIM::WALK_BACKWARD, false, 1.f, 0.25f);}
    else                             { Change_Animation(PLAYER_ANIM::WALK_LEFT, false, 1.5f, 0.25f); }

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
    if (m_pModelCom->Is_Animation_Finished())
        Initialize_State(PLAYER_STATE::IDLE);
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

    if (m_pModelCom->Is_Animation_Finished(true))
    {
        m_pModelCom->Set_UpperAnimationInActive();
        m_eUpperMoveState = PLAYER_ANIM::END;
        Initialize_State(Has_MoveInput() ? PLAYER_STATE::WALK : PLAYER_STATE::IDLE);
    }
}

void CPlayer::Play_Swap_Weapon_Anim(f32_t fDeltaTime)
{
    // 상체는 바꾸는 애니메이션(팔 내렸다 올렸다.) -> 무기를 들고있는 상황에서만 호출
    // 하체는 키입력에 따라 IDLE, WALK, SPRINT
    // SWAP_WEAPON -> IDLE, WALK, SPRINT
    m_fSwapWeaponTime += fDeltaTime;
    if (m_fSwapWeaponTime < 0.2f)
    {
        Change_Animation(PLAYER_ANIM::IDLE, true, 1.f, 0.2f);
        m_bCanAttack = false;
    }
    else if (m_fSwapWeaponTime < 0.4f)
    {
        Change_Animation(PLAYER_ANIM::IDLE_RH, true, 1.f, 0.2f);
        m_bCanAttack = false;
    }
    else
    {
        m_bCanAttack = true;
    }

}

void CPlayer::Handle_SlotInput(f32_t fDeltaTime)
{
    if (PLAYER_STATE::ROLL == m_eState || PLAYER_STATE::ATTACK == m_eState)
        return;
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
        return;

    if (m_tInput.bSlot1)     pInven->Set_ActiveSlot(EQUIP_SLOT::GUN_1); 
    if (m_tInput.bSlot2)     pInven->Set_ActiveSlot(EQUIP_SLOT::GUN_2);
    if (m_tInput.bSlotMelee) pInven->Set_ActiveSlot(EQUIP_SLOT::MELEE);

    if ((m_tInput.bSlot1 || m_tInput.bSlot2 || m_tInput.bSlotMelee) && Has_Weapon())
    {
        m_fSwapWeaponTime = 0.f;
        Play_Swap_Weapon_Anim(fDeltaTime);
    }
    else
    {
        Change_Animation(PLAYER_ANIM::IDLE, true);
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
    auto pMouse = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", GO::Client_Mouse);
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
    m_pModelCom->SetAnimPlaySpeed(fAnimPlaySpeed, bUpper);
    if (bUpper)
    {
        if (eMoveState == m_eUpperMoveState)
            return;
        m_eUpperMoveState = eMoveState;
        m_pModelCom->Set_UpperAnimationIndex(ETOUI(m_eUpperMoveState),true, fBlendDuration);
    }
    else
    {
        if (eMoveState == m_eLowerMoveState)
            return;
        m_eLowerMoveState = eMoveState;
        m_pModelCom->Set_LowerAnimationIndex(ETOUI(m_eLowerMoveState), fBlendDuration);
    }
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
