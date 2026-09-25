#include "Level.h"

CLevel::CLevel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:m_pDevice{pDevice}
	,m_pContext{pContext}
{
}


HRESULT CLevel::Initialize()
{
	return S_OK;
}
void CLevel::Update(f32_t fDeltaTime)
{
	for (auto pObj : m_mapObject)
		pObj.second->Update(fDeltaTime);
}
void CLevel::LateUpdate(f32_t fDeltaTime)
{
	for (auto pObj : m_mapObject)
		pObj.second->LateUpdate(fDeltaTime);
}
HRESULT	CLevel::Render()
{
	for (auto pObj : m_mapObject)
		pObj.second->Render();
	return S_OK;
}