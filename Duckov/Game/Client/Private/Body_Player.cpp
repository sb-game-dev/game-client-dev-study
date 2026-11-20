#include "Body_Player.h"

CBody_Player::CBody_Player(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CPartObject{ pDevice, pContext }
{
}

const float4x4_t* CBody_Player::Get_SocketMatrix(const char_t* pBoneName)
{
    return m_pModelCom->Get_CombinedTransformMatrix(pBoneName);
}

HRESULT CBody_Player::Initialize_Prototype()
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

HRESULT CBody_Player::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        auto        pDesc = static_cast<CBody_Player::BODY_DESC*>(pArg);
        m_pGroundPlane = pDesc->pGroundPlane;
    }
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
	return S_OK;
}

void CBody_Player::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CBody_Player::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    m_pModelCom->PlayAnimation(fDeltaTime);
    __super::Update_CombinedWorldMatrix(XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr()));
}

void CBody_Player::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::PLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::OCCLUDEDPLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::REFLECT, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CBody_Player::Render()
{
    return Render_Mesh(XMLoadFloat4x4(&m_CombinedWorldMatrix), m_pRS.Get(), m_pPSCom);
}


HRESULT CBody_Player::Render_Reflection(const matrix_t& matReflect)
{
    return Render_Mesh(XMLoadFloat4x4(&m_CombinedWorldMatrix) * matReflect, m_pRS_Reflect.Get(), m_pPSCom);
}

HRESULT CBody_Player::Render_Shadow()
{
    XMVECTOR vPlane = XMLoadFloat4(m_pGroundPlane);
    XMVECTOR vToLight = XMVectorSet(-0.5f, 0.5f, -0.5f, 0.f);  // SunLight Direction의 반대, w=0(평행광)

    matrix_t matShadow = XMMatrixShadow(vPlane, vToLight);
    matrix_t matOffset = XMMatrixTranslation(0.f, 0.01f, 0.f);  // 지형과 z-fighting 방지

    return Render_Mesh(XMLoadFloat4x4(&m_CombinedWorldMatrix) * matShadow * matOffset, m_pRS.Get(), m_pPS_Shadow);
}

HRESULT CBody_Player::Render_Occluded()
{
    return Render_Mesh(XMLoadFloat4x4(&m_CombinedWorldMatrix), m_pRS.Get(), m_pPS_Occluded);
}

bool_t CBody_Player::Is_Animation_Finished(bool_t IsUpper)
{
    return m_pModelCom->Is_Animation_Finished(IsUpper);
}

void CBody_Player::Set_UpperAnimationInActive(f32_t fBlendDuration)
{
    m_pModelCom->Set_UpperAnimationInActive(fBlendDuration);
}


HRESULT CBody_Player::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CBody_Player::Bind_ShaderResources(const matrix_t& matWorld)
{
    return __super::Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD), matWorld);
}

HRESULT CBody_Player::Render_Mesh(const matrix_t& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
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

void CBody_Player::Change_Animation(PLAYER_ANIM eMoveState, bool_t bUpper, f32_t fAnimPlaySpeed, f32_t fBlendDuration)
{
    m_pModelCom->SetAnimPlaySpeed(fAnimPlaySpeed, bUpper);
    if (bUpper)
    {
        m_eUpperMoveState = eMoveState;
        m_pModelCom->Set_UpperAnimationIndex(ETOUI(m_eUpperMoveState), true, fBlendDuration);
    }
    else
    {
        m_eLowerMoveState = eMoveState;
        m_pModelCom->Set_LowerAnimationIndex(ETOUI(m_eLowerMoveState), fBlendDuration);
    }
}

HRESULT CBody_Player::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Normalize_AssetPath(TEXT("Characters/S12_DuckV2_2/S12_DuckV2_2.fbx")),
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    m_pModelCom->Set_LowerAnimationIndex(ETOUI(m_eLowerMoveState), 0.f);

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

shared_ptr<CBody_Player> CBody_Player::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CBody_Player>(new CBody_Player(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CBody_Player");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CBody_Player::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CBody_Player>(new CBody_Player(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CBody_Player");
        pInstance.reset();
    }
    return pInstance;
}
