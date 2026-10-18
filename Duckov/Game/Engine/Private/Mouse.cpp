#include "Mouse.h"

CMouse::CMouse(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject{ pDevice,pContext }
{
}

HRESULT CMouse::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    return S_OK;
}

HRESULT CMouse::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    return S_OK;
}

void CMouse::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CMouse::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
}

void CMouse::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
}
HRESULT CMouse::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}
HRESULT CMouse::Ready_Components()
{
    return S_OK;
}