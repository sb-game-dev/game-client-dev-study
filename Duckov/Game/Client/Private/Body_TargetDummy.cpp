#include "Body_TargetDummy.h"

CBody_TargetDummy::CBody_TargetDummy(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CPartObject{ pDevice, pContext }
{
}

const float4x4_t* CBody_TargetDummy::Get_SocketMatrix(const char_t* pBoneName)
{
    return m_pModelCom->Get_CombinedTransformMatrix(pBoneName);
}

HRESULT CBody_TargetDummy::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    return S_OK;
}

HRESULT CBody_TargetDummy::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
    return S_OK;
}

void CBody_TargetDummy::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CBody_TargetDummy::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    m_fHitTimeRemaining = max(0.f, m_fHitTimeRemaining - fDeltaTime);
    __super::Update_CombinedWorldMatrix(XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr()));
}

void CBody_TargetDummy::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CBody_TargetDummy::Render()
{
    return Render_Mesh(XMLoadFloat4x4(&m_CombinedWorldMatrix), m_pPSCom);
}


HRESULT CBody_TargetDummy::Render_Shadow()
{
    XMVECTOR vPlane = XMLoadFloat4(&m_vGroundPlane);
    XMVECTOR vToLight = XMVectorSet(-0.5f, 0.5f, -0.5f, 0.f);  // SunLight Direction의 반대, w=0(평행광)

    matrix_t matShadow = XMMatrixShadow(vPlane, vToLight);
    matrix_t matOffset = XMMatrixTranslation(0.f, 0.01f, 0.f);  // 지형과 z-fighting 방지

    return Render_Mesh(XMLoadFloat4x4(&m_CombinedWorldMatrix) * matShadow * matOffset, m_pPS_Shadow);
}


HRESULT CBody_TargetDummy::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CBody_TargetDummy::Bind_ShaderResources(const matrix_t& matWorld)
{
    Update_ConstantBuffer();
    return __super::Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD), matWorld);
}

HRESULT CBody_TargetDummy::Render_Mesh(const matrix_t& matWorld, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    if (FAILED(Bind_Shader(m_pVSCom, pPS)))
        return E_FAIL;

    if (FAILED(m_pCBHitRatio->Bind_Pixel_ShaderResource(7, &m_vHitRatio)))
        return E_FAIL;
    if (FAILED(Bind_ShaderResources(matWorld)))
        return E_FAIL;

    uint32_t    iNumMeshes = m_pModelCom->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModelCom->Bind_BoneMatrix(i, 2)))
            return E_FAIL;
        if (FAILED(m_pModelCom->Bind_Material(i, ModelFile::TEXTURE_TYPE::DIFFUSE, 0, 0)))
            return E_FAIL;

        //if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_NORMALS, 0, 1)))
        //    return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }
    ID3D11Buffer* pNull = nullptr;
    m_pContext->PSSetConstantBuffers(7, 1, &pNull);
    return S_OK;
}

HRESULT CBody_TargetDummy::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::ZEROZONE), Proto::Model_TargetDummy,
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_MODEL,
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_VTXCOL_SHADOW,
        TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
        return E_FAIL;
    return S_OK;
}

HRESULT CBody_TargetDummy::Ready_ConstantBuffer()
{
    m_pCBHitRatio = CConstantBuffer::Create(m_pDevice, m_pContext, &m_vHitRatio, sizeof(m_vHitRatio));
    if (nullptr == m_pCBHitRatio)
        return E_FAIL;
    return S_OK;
}

HRESULT CBody_TargetDummy::Update_ConstantBuffer()
{
    m_vHitRatio.x = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.y = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.z = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.w = m_fHitTimeRemaining / m_fHitDuration;
    return S_OK;
}

shared_ptr<CBody_TargetDummy> CBody_TargetDummy::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CBody_TargetDummy>(new CBody_TargetDummy(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CBody_TargetDummy");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CBody_TargetDummy::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CBody_TargetDummy>(new CBody_TargetDummy(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CBody_TargetDummy");
        pInstance.reset();
    }
    return pInstance;
}
