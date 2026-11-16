#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class ENGINE_DLL CConstantBuffer final 
{
private:
	CConstantBuffer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CConstantBuffer() = default;

public:
	HRESULT Initialize(const void* pBuffer, uint32_t iBufferLength);
	HRESULT Bind_Vertex_ShaderResource(uint32_t iSlot, const void* pBuffer);
	HRESULT Bind_Pixel_ShaderResource(uint32_t iSlot, const void* pBuffer);

private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };
	ComPtr<ID3D11Buffer>			m_pCB = { nullptr };
	uint32_t						m_iByteLength = {};

public:
	static shared_ptr<CConstantBuffer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const void* pBuffer, uint32_t iBufferLength);
};

NS_END