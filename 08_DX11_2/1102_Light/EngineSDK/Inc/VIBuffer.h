#pragma once

#include "Component.h"

/* Vertex Buffer를 가진다. */
/* Index Buffer를 가진다. */

/* V + I 버퍼를 생성한다. */
/* VI를 이용해서 그ㅡ린다. */

NS_BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Bind_Resources();
	HRESULT Render();

protected:	
	ComPtr<ID3D11Buffer>			m_pVB = { nullptr };
	ComPtr<ID3D11Buffer>			m_pIB = { nullptr };

protected:
	uint32_t						m_iVertexStride = {}; /* 정점하나의 바이트 크기 */
	uint32_t						m_iNumVertices = {}; 

	uint32_t						m_iIndexStride = {};
	uint32_t						m_iNumIndices = {};

	uint32_t						m_iNumVertexBuffers = {};
	DXGI_FORMAT						m_eIndexFormat = {};

	D3D11_PRIMITIVE_TOPOLOGY		m_PrimitiveTopology = {};

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;
};

NS_END