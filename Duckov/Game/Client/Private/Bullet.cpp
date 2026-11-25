#include "Bullet.h"

CBullet::CBullet(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{ pDevice, pContext }
{
}

HRESULT CBullet::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CBullet::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        auto        pDesc = static_cast<CBullet::BULLET_DESC*>(pArg);

    }

    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_NONE;  
    rsDesc.DepthClipEnable = TRUE;
    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    if (FAILED(Ready_Components()))
        return E_FAIL;

    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    m_tDamageDesc.fDamage = 10.f;
    m_tDamageDesc.pWeapon = static_pointer_cast<CGameObject>(shared_from_this());
    m_tDamageDesc.iDamageType = ETOUI(DAMAGE_TYPE::BULLET);
    m_tDamageDesc.pAttackObject = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC),L"Layer_Static",GO::Player);

    m_bActive = false;
    return S_OK;
}

void CBullet::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
    m_pTransformCom->Go_Straight(fDeltaTime);
    m_fMoveDistance += fDeltaTime * m_pTransformCom->Get_Speed();
    if (m_fMoveDistance >= 100)
        Set_Active(false);
}

void CBullet::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

void CBullet::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    
    CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CBullet::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    if (FAILED(Bind_Shader()))
        return E_FAIL;
    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    m_pContext->RSSetState(m_pRS.Get());

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;
    return S_OK;
}

void CBullet::Bullet_Active(const float3_t vPos, const float3_t& vDir, f32_t fSpeed)
{
    vector_t vPosition = XMVectorSetW(XMLoadFloat3(&vPos), 1.f);

    m_pTransformCom->Set_State(STATE::POSITION, vPosition);

    m_pTransformCom->LookAt(vPosition + XMLoadFloat3(&vDir));

    m_pTransformCom->Set_Speed(fSpeed);

    Clear_Hit_Targets();

    m_fMoveDistance = { 0.f };

    m_bActive = true;
}

void CBullet::TriggerEnter(shared_ptr<class CCollider> pOtherCollider)
{
    if (false == m_pCube_Collider->Get_Active())
        return;
    m_bActive = false;
    auto pOtherObject = pOtherCollider->Get_Owner().lock();

    for (auto pHit_Target : m_Hit_Targets)
    {
        if (pHit_Target.lock() == pOtherObject)
            return;
    }
    pOtherObject->Take_Damage(m_tDamageDesc);
    m_Hit_Targets.push_back(pOtherObject);
}

void CBullet::Clear_Hit_Targets()
{
    m_Hit_Targets.clear();
}

HRESULT CBullet::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_TRAIL, TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_TRAIL, TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VIBuffer_Rect, TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Cube_Collider, TEXT("Com_Cube_Collider"), m_pCube_Collider)))
        return E_FAIL;

    m_pCube_Collider->Set_Extents({ m_fWidth ,m_fWidth ,m_fWidth });
    return S_OK;
}

HRESULT CBullet::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CBullet::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;
    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CBullet::Bind_ShaderResources()
{
    // 총알의 앞 뒤 길이 -> 이동한 거리만큼 길어지도록 설정.
    // 다만 이동할수록 길어짐 -> 최대값을 설정
    f32_t fHeight = min(m_pTransformCom->Get_Speed() * 0.04f, m_fMoveDistance);    

    matrix_t matLocal = XMMatrixScaling(m_fWidth, fHeight, 1.f)     // 폭 , 길이 설정
        * XMMatrixRotationX(XM_PI / 2.f)                         // x축 90도 회전(x,z평면으로 눕히기)
        * XMMatrixTranslation(0.f, 0.f, -fHeight * 0.5f);        // 중심점을 총알 투사체의 시작점으로 설정 
                                                                 // -> 이 설정을 하지 않으면 충돌 검사를 총알 투사체의 중심과 하게 됨

    XMStoreFloat4x4(&m_tCBData.mat_World, matLocal * m_pTransformCom->Get_World());
    m_pCB->Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD), &m_tCBData); 
    return S_OK;
}

shared_ptr<CBullet> CBullet::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    shared_ptr<CBullet> pInstance = shared_ptr<CBullet>(new CBullet(pDevice,pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Create : CBullet");
        pInstance.reset();
    }

    return pInstance;
}

shared_ptr<CPrototype> CBullet::Clone(void* pArg)
{
    shared_ptr<CBullet> pInstance = shared_ptr<CBullet>(new CBullet(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CBullet");
        pInstance.reset();
    }

    return pInstance;
}