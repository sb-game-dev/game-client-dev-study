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
    if(FAILED(__super::Initialize(pArg)))
        return E_FAIL;
	return S_OK;
}

void CMouse::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CMouse::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

void CMouse::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

HRESULT CMouse::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CMouse> CMouse::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CMouse>(new CMouse(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CMouse");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CMouse::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CMouse>(new CMouse(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CMouse");
        pInstance.reset();
    }
    return pInstance;
}
