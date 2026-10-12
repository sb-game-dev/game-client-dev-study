#include "GameObject.h"

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
