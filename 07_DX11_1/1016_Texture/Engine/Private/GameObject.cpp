#include "GameObject.h"

#include "GameInstance.h"

CGameObject::CGameObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CPrototype { pDevice, pContext }
{
}

HRESULT CGameObject::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CGameObject::Initialize(void* pArg)
{
    auto        pDesc = static_cast<GAMEOBJECT_DESC*>(pArg);

    m_iData = pDesc->iData;

    m_pTransformCom = CTransform::Create(m_pDevice, m_pContext);
    if (nullptr == m_pTransformCom)
        return E_FAIL;

    if (FAILED(m_pTransformCom->Initialize(pArg)))
        return E_FAIL;

    m_Components.emplace(g_strTransformComTag, m_pTransformCom);

    return S_OK;
}

void CGameObject::Priority_Update(f32_t fTimeDelta)
{
}

void CGameObject::Update(f32_t fTimeDelta)
{
}

void CGameObject::Late_Update(f32_t fTimeDelta)
{
}

HRESULT CGameObject::Render()
{
    return S_OK;
}

shared_ptr<CComponent> CGameObject::Find_Component(const wstring& strComponentTag)
{
    auto    iter = m_Components.find(strComponentTag);
    if (iter == m_Components.end())
        return nullptr;

    return iter->second;    
}
