#include "RenderState_Manager.h"

CRenderState_Manager::CRenderState_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{

}

HRESULT CRenderState_Manager::Initialize()
{
	if (FAILED(Add_RasterizerState(g_strRS_Default, g_RSDefault_Desc)))
		return E_FAIL;

	if (FAILED(Add_RasterizerState(g_strRS_NonCull, g_RSNonCull_Desc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderState_Manager::Add_RasterizerState(const wstring_t& strRSTag, const D3D11_RASTERIZER_DESC& RSDesc)
{
	ComPtr<ID3D11RasterizerState>	pRaterizerState = { };

	if (FAILED(m_pDevice->CreateRasterizerState(&RSDesc, &pRaterizerState)))
		return E_FAIL;

	m_RaterizerStates.emplace(strRSTag, pRaterizerState);

	return S_OK;
}

HRESULT CRenderState_Manager::Bind_RasterizerState(const wstring_t& strRSTag)
{
	auto	pRasterizerState = Find_RasterizerState(strRSTag);
	if (nullptr == pRasterizerState)
		return E_FAIL;

	m_pContext->RSSetState(pRasterizerState.Get());

	return S_OK;
}

ComPtr<ID3D11RasterizerState> CRenderState_Manager::Find_RasterizerState(const wstring_t& strRSTag)
{
	auto	iter = m_RaterizerStates.find(strRSTag);
	if (iter == m_RaterizerStates.end())
		return nullptr;

	return iter->second;	
}

unique_ptr<CRenderState_Manager> CRenderState_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = unique_ptr<CRenderState_Manager>(new CRenderState_Manager(pDevice, pContext));

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CRenderState_Manager");
		pInstance.reset();
	}

	return pInstance;
}
