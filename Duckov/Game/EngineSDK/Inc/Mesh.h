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
	HRESULT	Initialize_Prototype(FILE* pFile, fmatrix_t PreTransformMatrix);
	HRESULT	Initialize(void* pArg);
	HRESULT	Render_Instanced(ID3D11Buffer* pInstanceVB, uint32_t iInstanceStride, uint32_t iNumInstances);
	HRESULT	Bind_BoneMatrix(vector<shared_ptr<class CBone>>& Bones, uint32_t iSlot);

private:
	/* 
	뼈가 없는 메시일 수 있으니(mNumBones = 0), 메시의 이름으로 뼈와 매칭
	아무 처리를 하지 않으면 뼈 행렬이 아무것도 없게 되기 때문에 제대로 그려지지 않는다
	*/
	char_t m_szName[MAX_PATH];

	/* 이 메시에 입힐 머티리얼 인덱스*/
	uint32_t			m_iMaterialIndex = {};

	uint32_t			m_iNumBones = {};
	/* 이 메시에게 영향을 주는 뼈들이 모델이들고있는 전체 뼈들중의 인덱스들을 보관한다. */
	vector<uint32_t>	m_BoneIndices;
	/* 이 메시에게 영향을 주는 뼈들의 로컬 스페이스로 이동시키기 위한 행렬 */
	vector<float4x4_t>	m_OffsetMatrices;

	/* 이 메시에 최종으로 곱할 행렬 -> 상수버퍼로 전달할 데이터*/
	shared_ptr<class CConstantBuffer>	m_pCB = { nullptr };
	float4x4_t							m_BoneMatrices[512] = {};

private:
	HRESULT				Ready_Meshes_For_NonAnim(const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix);
	HRESULT				Ready_Meshes_For_Anim(shared_ptr<class CModel> pModel, const aiMesh* pAIMesh);

public:
	static shared_ptr<CMesh> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, shared_ptr<class CModel> pModel, const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	static shared_ptr<CMesh> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, FILE* pFile, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	virtual shared_ptr<CPrototype> Clone(void* pArg)override;
};

NS_END