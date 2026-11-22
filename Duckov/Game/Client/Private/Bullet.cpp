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

    //if (FAILED(Ready_Components()))
    //    return E_FAIL;
    return S_OK;
}

void CBullet::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CBullet::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

void CBullet::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

HRESULT CBullet::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}

HRESULT CBullet::Ready_Components()
{
    return S_OK;
}

HRESULT CBullet::Bind_Shader()
{
    return S_OK;
}

HRESULT CBullet::Bind_ShaderResources(const matrix_t& matWorld)
{
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