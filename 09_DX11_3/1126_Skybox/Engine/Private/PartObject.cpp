#include "PartObject.h"

#include "GameInstance.h"



CPartObject::CPartObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject{ pDevice, pContext }
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

    if (nullptr == pArg)
        return S_OK;

    auto        pDesc = static_cast<PARTOBJECT_DESC*>(pArg);

    m_pParentTransformCom = pDesc->pParentTransformCom;

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_CombinedWorldMatrix, sizeof m_CombinedWorldMatrix);
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

void CPartObject::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CPartObject::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
}

void CPartObject::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
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

HRESULT CPartObject::Bind_Vertex_ShaderResource(uint32_t iSlot)
{
    return m_pCB->Bind_Vertex_ShaderResource(iSlot, &m_CombinedWorldMatrix);    
}



