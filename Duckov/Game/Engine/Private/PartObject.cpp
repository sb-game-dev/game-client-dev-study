#include "PartObject.h"

CPartObject::CPartObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject{ pDevice, pContext }
{
}

HRESULT CPartObject::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    return S_OK;
}

HRESULT CPartObject::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof m_tCBData);
    if (nullptr == m_pCB)
        return E_FAIL;

    if (nullptr == pArg)
        return S_OK;
    auto pDesc = static_cast<PARTOBJECT_DESC*>(pArg);

    m_pParentTransformCom = pDesc->pParentTransformCom;

    return S_OK;
}

void CPartObject::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CPartObject::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

void CPartObject::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

HRESULT CPartObject::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}

void CPartObject::Update_CombinedWorldMatrix(fmatrix_t ChildMatrix)
{
    XMStoreFloat4x4(&m_CombinedWorldMatrix, ChildMatrix * XMLoadFloat4x4(m_pParentTransformCom->Get_WorldMatrixPtr()));
}

HRESULT CPartObject::Bind_Vertex_ShaderResource(uint32_t iSlot, const matrix_t& matWorld)
{
    matrix_t matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);

    XMStoreFloat4x4(&m_tCBData.mat_World, matWorld);
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans)));

    return m_pCB->Bind_Vertex_ShaderResource(iSlot, &m_tCBData);
}

shared_ptr<CPartObject> CPartObject::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CPartObject>(new CPartObject(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CPartObject");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CPartObject::Clone(void* pArg)
{
    shared_ptr<CPartObject> pInstance = shared_ptr<CPartObject>(new CPartObject(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CPartObject");
        pInstance.reset();
    }

    return pInstance;
}