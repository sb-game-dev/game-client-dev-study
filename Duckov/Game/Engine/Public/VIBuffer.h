#pragma once
#include "Component.h"

NS_BEGIN(Engine)
class  ENGINE_DLL CVIBuffer : public CComponent
{
protected:
	CVIBuffer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CVIBuffer() = default;
public:
	virtual HRESULT	Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual HRESULT Bind_Resources();
	virtual HRESULT Render();

protected:
	ComPtr<ID3D11Buffer>		m_pVB;
	ComPtr<ID3D11Buffer>		m_pIB;

protected:
	uint32_t					m_iVertexStride = {};
	uint32_t					m_iNumVertices = {};

	uint32_t					m_iIndexStride = {};
	uint32_t					m_iNumIndices = {};

	uint32_t					m_iNumVertexBuffers = {};
	DXGI_FORMAT					m_eIndexFormat = {};

	D3D11_PRIMITIVE_TOPOLOGY	m_ePrimitiveTopology = {};

	BoundingBox					m_tLocalBox = {};
	bool_t						m_bUseCulling = { false };

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) PURE;
};

NS_END