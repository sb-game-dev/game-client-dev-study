#pragma once

#include "VIBuffer.h"

NS_BEGIN(Engine)

class ENGINE_DLL CMesh final : public CVIBuffer
{
private:
	CMesh(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CMesh() = default;

public:
	uint32_t Get_MaterialIndex() const {
		return m_iMaterialIndex;
	}

public:
	virtual HRESULT Initialize_Prototype(MODEL eType, shared_ptr<class CModel> pModel, const aiMesh* pAIMesh, fmatrix_t PreTransformMatrix);
	virtual HRESULT Initialize(void* pArg) override;

private:
	uint32_t			m_iMaterialIndex = {};
	uint32_t			m_iNumBones = {};
	/* 이ㅏ 메시에게 영향을 주는 뼈들이 모델이들공 ㅣㅆ는 전체 뼈들중의 인덱스들을 보관한다. */
	vector<uint32_t>	m_BoneIndices; 

private:
	HRESULT Ready_Meshes_For_NonAnim(const aiMesh* pAIMesh, fmatrix_t PreTransformMatrix);
	HRESULT Ready_Meshes_For_Anim(shared_ptr<class CModel> pModel, const aiMesh* pAIMesh);

public:
	static shared_ptr<CMesh> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, shared_ptr<class CModel> pModel, const aiMesh* pAIMesh, fmatrix_t PreTransformMatrix);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END