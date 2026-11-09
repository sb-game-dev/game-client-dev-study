#pragma once
#include "VIBuffer.h"
NS_BEGIN(Engine)
class ENGINE_DLL CMesh : public CVIBuffer
{
private:
	CMesh(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CMesh() = default;
public:
	uint32_t Get_MaterialIndex() const {
		return m_iMaterialIndex;
	}
public:
	HRESULT	Initialize_Prototype(const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix);
	HRESULT	Initialize(void* pArg);
private:
	uint32_t			m_iMaterialIndex = {};
public:
	static shared_ptr<CMesh> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	virtual shared_ptr<CPrototype> Clone(void* pArg)override;
};

NS_END