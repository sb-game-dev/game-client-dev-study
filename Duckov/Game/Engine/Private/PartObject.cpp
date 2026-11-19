#include "PartObject.h"

CPartObject::CPartObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject{ pDevice, pContext }
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
    auto pDesc = static_cast<PARTOBJECT_DESC*>(pArg);

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