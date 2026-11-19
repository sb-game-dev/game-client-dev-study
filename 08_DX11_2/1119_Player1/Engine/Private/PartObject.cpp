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



