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
	HRESULT	Initialize_Prototype(const aiMesh* pAiMesh);
	HRESULT	Initialize(void* pArg);

public:
	static shared_ptr<CMesh> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const aiMesh* pAiMesh);
	virtual shared_ptr<CPrototype> Clone(void* pArg)override;
};

NS_END