#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CLight final 
{
private:
	CLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLight() = default;

public:
	HRESULT Initialize(LIGHT eType, const LIGHT_DESC& LightDesc);
	HRESULT Bind_Pixel_ShaderResouce(uint32_t iSlot);

private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };	
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };

	LIGHT								m_eType = { LIGHT::END };
	LIGHT_DESC							m_LightDesc = {};
	shared_ptr<class CConstantBuffer>	m_pCB = { nullptr };

public:
	static shared_ptr<CLight> Create(LIGHT eType, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const LIGHT_DESC& LightDesc);
};

NS_END