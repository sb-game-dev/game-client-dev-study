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
void CLevel::Priority_Update(f32_t fDeltaTime)
{
	for (auto pObj : m_mapObject)
		pObj.second->Priority_Update(fDeltaTime);
}
void CLevel::Update(f32_t fDeltaTime)
{
	for (auto pObj : m_mapObject)
		pObj.second->Update(fDeltaTime);
}
void CLevel::Late_Update(f32_t fDeltaTime)
{
	for (auto pObj : m_mapObject)
		pObj.second->Late_Update(fDeltaTime);
}
HRESULT	CLevel::Render()
{
	for (auto pObj : m_mapObject)
		pObj.second->Render();
	return S_OK;
}