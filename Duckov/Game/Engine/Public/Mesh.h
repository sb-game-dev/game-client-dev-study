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
	HRESULT	Initialize_Prototype(MODEL eType, shared_ptr<class CModel> pModel, const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix);
	HRESULT	Initialize(void* pArg);
	HRESULT	Render_Instanced(ID3D11Buffer* pInstanceVB, uint32_t iInstanceStride, uint32_t iNumInstances);

private:
	uint32_t			m_iMaterialIndex = {};

	uint32_t			m_iNumBones = {};
	/* 이 메시에게 영향을 주는 뼈들이 모델이들고있는 전체 뼈들중의 인덱스들을 보관한다. */
	vector<uint32_t>	m_BoneIndices;

private:
	HRESULT				Ready_Meshes_For_NonAnim(const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix);
	HRESULT				Ready_Meshes_For_Anim(shared_ptr<class CModel> pModel, const aiMesh* pAIMesh);

public:
	static shared_ptr<CMesh> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, shared_ptr<class CModel> pModel, const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	virtual shared_ptr<CPrototype> Clone(void* pArg)override;
};

NS_END