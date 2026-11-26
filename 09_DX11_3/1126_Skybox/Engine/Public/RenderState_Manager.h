#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CRenderState_Manager
{
private:
	CRenderState_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CRenderState_Manager() = default;

public:
	HRESULT Initialize();
	HRESULT Add_RasterizerState(const wstring_t& strRSTag, const D3D11_RASTERIZER_DESC& RSDesc);
	HRESULT Bind_RasterizerState(const wstring_t& strRSTag);

private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };


private:
	map<const wstring_t, ComPtr<ID3D11RasterizerState>>		m_RaterizerStates;
	map<const wstring_t, ComPtr<ID3D11DepthStencilState>>	m_DepthStencilStates;
	map<const wstring_t, ComPtr<ID3D11BlendState>>			m_BlendStates;

private:
	ComPtr<ID3D11RasterizerState> Find_RasterizerState(const wstring_t& strRSTag);

public:
	static unique_ptr<CRenderState_Manager> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);


};

NS_END