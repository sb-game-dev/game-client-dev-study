#pragma once

#include "Component.h"

NS_BEGIN(Engine)

class ENGINE_DLL CModel final : public CComponent
{
private:
	CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	CModel(const CModel& Prototype);
public:
	virtual ~CModel() = default;

public:
	uint32_t Get_NumMeshes() const {
		return m_iNumMeshes;
	}

	bool_t isFinished() const {
		return m_isFinished;
	}

	int32_t Get_BoneIndex(const char_t* pBoneName);

public:
	virtual HRESULT Initialize_Prototype(MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	virtual HRESULT Initialize(void* pArg) override;

public:
	void Set_Animation(uint32_t iAnimIndex, bool_t isLoop);
	void Play_Animation(f32_t fTimeDelta);
	HRESULT Bind_Material(uint32_t iMeshIndex, aiTextureType eType, uint32_t iIndex, uint32_t iSlot);
	HRESULT Bind_BoneMatrices(uint32_t iMeshIndex, uint32_t iSlot);
	HRESULT Render(uint32_t iMeshIndex);




private:
	const aiScene*				m_pAIScene = { nullptr };
	Assimp::Importer			m_Importer = {};

private:
	MODEL								m_eType = { MODEL::END };
	float4x4_t							m_PreTransformMatrix = {};
	uint32_t							m_iNumMeshes = {};
	vector<shared_ptr<class CMesh>>		m_Meshes;

	uint32_t							m_iNumMaterials = {};
	vector<shared_ptr<class CMaterial>>	m_Materials;

	vector<shared_ptr<class CBone>>		m_Bones;

	uint32_t								m_iNumAnimations = {};
	vector<shared_ptr<class CAnimation>>	m_Animations;
	int32_t								m_iCurrentAnimIndex = {-1};
	bool_t									m_isLoop = {};
	bool_t									m_isFinished = {};

private:
	HRESULT Ready_Meshes(fmatrix_t PreTransformMatrix);
	HRESULT Ready_Materials(const char_t* pModelFilePath);
	HRESULT Ready_Bones(const aiNode* pAINode, int32_t iPIndex);
	HRESULT Ready_Animations();

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END