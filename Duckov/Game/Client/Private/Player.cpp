#include "Player.h"
#include "Inven.h"

const vector_t	g_vZ_Plus = XMVector4Normalize({ 0.f,0.f,+1.f,0.f });
const vector_t	g_vZ_Minus = XMVector4Normalize({ 0.f,0.f,-1.f,0.f });
const vector_t	g_vX_Plus = XMVector4Normalize({ +1.f,0.f,0.f,0.f });
const vector_t	g_vX_Minus = XMVector4Normalize({ -1.f,0.f,0.f,0.f });
const vector_t	g_vY_Plus = XMVector4Normalize({ 0.f,+1.f,0.f,0.f });
const vector_t	g_vY_Minus = XMVector4Normalize({ 0.f,-1.f,0.f,0.f });
const vector_t	g_vQuad1 = XMVector4Normalize({ +1.f,0.f,+1.f,0.f });
const vector_t	g_vQuad2 = XMVector4Normalize({ -1.f,0.f,+1.f,0.f });
const vector_t	g_vQuad3 = XMVector4Normalize({ -1.f,0.f,-1.f,0.f });
const vector_t	g_vQuad4 = XMVector4Normalize({ +1.f,0.f,-1.f,0.f });

CPlayer::CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
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

    rsDesc.FrontCounterClockwise = true;   // 반사되면 감기 순서가 뒤집히므로 앞면 기준도 뒤집음
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
    auto pInven = static_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
        ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
    bool_t bInvenOpen = (nullptr != pInven && pInven->Is_Open());
    if (!bInvenOpen)
    {
        KeyInput(fDeltaTime);
        AdjustPosY();
    }
}

void CPlayer::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
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
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS);
}

HRESULT CPlayer::Render_Reflection(const matrix_t& matReflect)
{
    return Render_Mesh(m_pTransformCom->Get_World() * matReflect, m_pRS_Reflect.Get(), m_pPS);
}

HRESULT CPlayer::Render_Shadow()
{
    XMVECTOR vPlane     = XMLoadFloat4(&m_vGroundPlane);
    XMVECTOR vToLight   = XMVectorSet(-0.5f, 0.5f, -0.5f, 0.f);   // SunLight Direction의 반대, w=0(평행광)

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
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Pyramid,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXCOL,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL,
        TEXT("Com_PS"), m_pPS)))
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
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBDesc, sizeof m_tCBDesc);
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CPlayer::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMStoreFloat4x4(&m_tCBDesc.WorldMatrix, matWorld);
    return S_OK;
}


HRESULT CPlayer::Render_Mesh(const matrix_t& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(pRS);

    Update_ConstantBuffer(matWorld);
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBDesc)))
        return E_FAIL;
    
    if (FAILED(m_pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;
    return S_OK;
}
void CPlayer::AdjustPosY()
{
    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));
    
    vector_t  vPos = m_pTransformCom->Get_State(STATE::POSITION);
    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.5f);
    m_pTransformCom->Set_State(STATE::POSITION, vPos);
    m_vGroundPlane = pHill->GetPlane(x, z);
}
void CPlayer::KeyInput(f32_t fDeltaTime)
{
    bool_t  bPushShift = false;
    if (CGameInstance::Get().Key_Pressing(DIK_LSHIFT))
    {
        m_pTransformCom->Set_Speed(16.f);
        bPushShift = true;
    }
    else
    {
        LookAtMouse(fDeltaTime);
        m_pTransformCom->Set_Speed(8.f);
    }

    vector_t vLook = m_pTransformCom->Get_State(STATE::LOOK);

    if (CGameInstance::Get().Key_Pressing(DIK_W))
    {
        if (CGameInstance::Get().Key_Pressing(DIK_A))
        {
            m_pTransformCom->Move_Position(g_vQuad2, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad2));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) > -XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            }
        }
        else if (CGameInstance::Get().Key_Pressing(DIK_D))
        {
            m_pTransformCom->Move_Position(g_vQuad1, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad1));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) < XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            }
        }
        else
        {
            m_pTransformCom->Move_Position(g_vZ_Plus, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vZ_Plus));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetX(vLook) < 0.f)
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
                else 
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            }
        }
    }
    else if (CGameInstance::Get().Key_Pressing(DIK_S))
    {
        if (CGameInstance::Get().Key_Pressing(DIK_A))
        {
            m_pTransformCom->Move_Position(g_vQuad3, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad3));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) < XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            }
        }
        else if (CGameInstance::Get().Key_Pressing(DIK_D))
        {
            m_pTransformCom->Move_Position(g_vQuad4, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad4));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) > -XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            }
        }
        else
        {
            m_pTransformCom->Move_Position(g_vZ_Minus, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vZ_Minus));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetX(vLook) < 0.f)
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            }
        }
    }
    else if (CGameInstance::Get().Key_Pressing(DIK_A))
    {
        m_pTransformCom->Move_Position(g_vX_Minus, fDeltaTime);
        if (!bPushShift)
            return;
        f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vX_Minus));
        if (XMConvertToDegrees(acosf(dot)) > 2.f)
        {
            if (XMVectorGetZ(vLook) < 0.f)
                m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            else
                m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
        }
    }
    else if (CGameInstance::Get().Key_Pressing(DIK_D))
    {
        m_pTransformCom->Move_Position(g_vX_Plus, fDeltaTime);
        if (!bPushShift)
            return;
        f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vX_Plus));
        if (XMConvertToDegrees(acosf(dot)) > 2.f)
        {
            if (XMVectorGetZ(vLook) < 0.f)
                m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            else
                m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
        }
    }
}
void CPlayer::LookAtMouse(f32_t fDeltaTime)
{
    auto pMouse = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", GO::Client_Mouse);
    vector_t vTargetPos = pMouse->Get_Transform()->Get_State(STATE::POSITION);
    m_pTransformCom->LookAt(vTargetPos);
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
