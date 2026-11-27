#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CRenderState_Manager
{
private:
	CRenderState_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext>pContext);
public:
	~CRenderState_Manager() = default;

public:
	HRESULT Initialize();
	HRESULT Add_RasterizerState(const wstring_t& strRSTag, const D3D11_RASTERIZER_DESC& RSDesc);
	HRESULT Bind_RasterizerState(const wstring_t& strRSTag);

	HRESULT Add_DepthStencilState(const wstring_t& strDSSTag, const D3D11_DEPTH_STENCIL_DESC& DSSDesc);
	HRESULT Bind_DepthStencilState(const wstring_t& strDSSTag, uint32_t StencilRef);
	
	HRESULT	Add_BlendState(const wstring_t& strBlendTag, const D3D11_BLEND_DESC& BlendDesc);
	HRESULT Bind_BlendState(const wstring_t& strBlendTag, f32_t* pBlendFactor = nullptr, uint32_t SampleMask = 0xffffffff);

private:
	ComPtr<ID3D11Device> m_pDevice;
	ComPtr<ID3D11DeviceContext>m_pContext;

private:
	map<const wstring_t, ComPtr<ID3D11RasterizerState>>		m_RasterizerStates;
	map<const wstring_t, ComPtr<ID3D11DepthStencilState>>	m_DepthStensilStates;
	map<const wstring_t, ComPtr<ID3D11BlendState>>			m_BlendStates;

private:
	ComPtr<ID3D11RasterizerState>		 Find_RasterizerState(const wstring_t& strRSTag);
	ComPtr<ID3D11DepthStencilState>		 Find_DepthStencilState(const wstring_t& strRSTag);
	ComPtr<ID3D11BlendState >			 Find_BlendState(const wstring_t& strRSTag);

	HRESULT Ready_RasterizeState();
	HRESULT Ready_DepthStencilState();
	HRESULT Ready_BlendState();
public:
	static	unique_ptr<CRenderState_Manager> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext>pContext);
};

NS_END