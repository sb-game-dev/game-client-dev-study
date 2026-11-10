#include "Light_Manager.h"
#include "Light.h"

CLight_Manager::CLight_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
}

HRESULT CLight_Manager::Add_Light(LIGHT eType, const LIGHT_DESC& LightDesc)
{
	auto		pLight = CLight::Create(eType, m_pDevice, m_pContext, LightDesc);
	if (nullptr == pLight)
		return E_FAIL;

	m_Lights.push_back(pLight);

	return S_OK;
}

HRESULT CLight_Manager::Bind_Pixel_ShaderResource(uint32_t iIndex, uint32_t iSlot)
{
	auto	iter = m_Lights.begin();

	if (iter == m_Lights.end())
		return S_OK;

	for (uint32_t i = 0; i < iIndex; i++)
		++iter;	

	return (*iter)->Bind_Pixel_ShaderResouce(iSlot);	
}

unique_ptr<CLight_Manager> CLight_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	return unique_ptr<CLight_Manager>(new CLight_Manager(pDevice, pContext));
}
