#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CLight_Manager final 
{
private:
	CLight_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLight_Manager() = default;

public:
	HRESULT Add_Light(LIGHT eType, const LIGHT_DESC& LightDesc);
	HRESULT Bind_Pixel_ShaderResource(uint32_t iIndex, uint32_t iSlot);
private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };

	list<shared_ptr<class CLight>>	m_Lights;

public:
	static unique_ptr<CLight_Manager> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

};

NS_END