#include "ContainerObject.h"

CContainerObject::CContainerObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{ pDevice, pContext }
{
}

HRESULT CContainerObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CContainerObject::Initialize(void* pArg)
{
	return S_OK;
}

void CContainerObject::Priority_Update(f32_t fDeltaTime)
{
}

void CContainerObject::Update(f32_t fDeltaTime)
{
}

void CContainerObject::Late_Update(f32_t fDeltaTime)
{
}

HRESULT CContainerObject::Render()
{
	return S_OK;
}
