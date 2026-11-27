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

	if (FAILED(Add_DepthStencilState(g_strDSS_Default, g_DSSDefault_Desc)))
		return E_FAIL;

	if (FAILED(Add_DepthStencilState(g_strDSS_NonZ, g_DSSNonZ_Desc)))
		return E_FAIL; 

	
	if (FAILED(Add_BlendState(g_strBS_Default, g_BSDefault_Desc)))
		return E_FAIL;

	
	if (FAILED(Add_BlendState(g_strBS_AlphaBlend, g_BSAlphaBlend_Desc)))
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

HRESULT CRenderState_Manager::Add_DepthStencilState(const wstring_t& strDSSTag, const D3D11_DEPTH_STENCIL_DESC& DSSDesc)
{
	ComPtr<ID3D11DepthStencilState>	pDepthStencilState = { };

	if (FAILED(m_pDevice->CreateDepthStencilState(&DSSDesc, &pDepthStencilState)))
		return E_FAIL;

	m_DepthStencilStates.emplace(strDSSTag, pDepthStencilState);

	return S_OK;
}

HRESULT CRenderState_Manager::Add_BlendState(const wstring_t& strBSTag, const D3D11_BLEND_DESC& BSDesc)
{
	ComPtr<ID3D11BlendState>	pBlendState = { };

	if (FAILED(m_pDevice->CreateBlendState(&BSDesc, &pBlendState)))
		return E_FAIL;

	m_BlendStates.emplace(strBSTag, pBlendState);

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

HRESULT CRenderState_Manager::Bind_DepthStencilState(const wstring_t& strDSSTag)
{
	auto	pDepthStencilState = Find_DepthStencilState(strDSSTag);
	if (nullptr == pDepthStencilState)
		return E_FAIL;

	m_pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 0);

	return S_OK;
}

HRESULT CRenderState_Manager::Bind_BlendState(const wstring_t& strBSTag, const float4_t* pBlendFactor)
{
	auto	pBlendState = Find_BlendState(strBSTag);
	if (nullptr == pBlendState)
		return E_FAIL;

	f32_t		fFactor[4] = {};
	if (nullptr != pBlendFactor)
		memcpy(fFactor, pBlendFactor, sizeof f32_t * 4);

	m_pContext->OMSetBlendState(pBlendState.Get(), fFactor, 0xffffffff);

	return S_OK;
}


ComPtr<ID3D11RasterizerState> CRenderState_Manager::Find_RasterizerState(const wstring_t& strRSTag)
{
	auto	iter = m_RaterizerStates.find(strRSTag);
	if (iter == m_RaterizerStates.end())
		return nullptr;

	return iter->second;	
}

ComPtr<ID3D11DepthStencilState> CRenderState_Manager::Find_DepthStencilState(const wstring_t& strDSSTag)
{
	auto	iter = m_DepthStencilStates.find(strDSSTag);
	if (iter == m_DepthStencilStates.end())
		return nullptr;

	return iter->second;
}

ComPtr<ID3D11BlendState> CRenderState_Manager::Find_BlendState(const wstring_t& strBSTag)
{
	auto	iter = m_BlendStates.find(strBSTag);
	if (iter == m_BlendStates.end())
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
