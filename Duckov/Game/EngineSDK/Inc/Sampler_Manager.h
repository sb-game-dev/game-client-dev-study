#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CSampler_Manager final
{
private:
	CSampler_Manager(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
public:
	~CSampler_Manager() = default;

public:
	HRESULT	Initialize();
	HRESULT	Add_Sampler(const wstring_t& strSamplerTag, const D3D11_SAMPLER_DESC& SamplerDesc);
	HRESULT Bind_Sampler_Pixel_Shader(const wstring_t strSamplerTag, const uint32_t& iSlot);

private:
	ComPtr<ID3D11Device>		m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext> m_pContext = { nullptr };

private:
	map<const wstring_t, ComPtr<ID3D11SamplerState>>		m_Samplers;

private:
	ComPtr<ID3D11SamplerState>	Find_Sampler(const wstring_t& strSamplerTag);

public:
	static unique_ptr<CSampler_Manager> Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);

};

NS_END