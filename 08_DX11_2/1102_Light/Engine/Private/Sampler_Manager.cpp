#include "Sampler_Manager.h"

CSampler_Manager::CSampler_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
}

HRESULT CSampler_Manager::Initialize()
{
	if (FAILED(Add_Sampler(g_strSampler_Point, g_Sampler_Point_Desc)))
		return E_FAIL;
	if (FAILED(Add_Sampler(g_strSampler_Linear, g_Sampler_Linear_Desc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CSampler_Manager::Add_Sampler(const wstring_t& strSamplerTag, const D3D11_SAMPLER_DESC& SamplerDesc)
{
	if (nullptr != Find_Sampler(strSamplerTag))
		return E_FAIL;

	ComPtr<ID3D11SamplerState>		pSamplerState = { nullptr };

	if (FAILED(m_pDevice->CreateSamplerState(&SamplerDesc, &pSamplerState)))
		return E_FAIL;

	m_Samplers.emplace(strSamplerTag, pSamplerState);

	return S_OK;
}

HRESULT CSampler_Manager::Bind_Sampler_Pixel_Shader(const wstring_t& strSamplerTag, uint32_t iSlot)
{
	auto		pSampler = Find_Sampler(strSamplerTag);
	if (nullptr == pSampler)
		return E_FAIL;

	ID3D11SamplerState* pSamplers[] = {
		pSampler.Get()
	};

	m_pContext->PSSetSamplers(iSlot, 1, pSamplers);

	return S_OK;
}

ComPtr<ID3D11SamplerState> CSampler_Manager::Find_Sampler(const wstring_t& strSamplerTag)
{
	auto	iter = m_Samplers.find(strSamplerTag);
	if (iter == m_Samplers.end())
		return nullptr;

	return iter->second;	
}

unique_ptr<CSampler_Manager> CSampler_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = unique_ptr<CSampler_Manager>(new CSampler_Manager(pDevice, pContext));

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CSampler_Manager");
		pInstance.reset();
	}

	return pInstance;
}
