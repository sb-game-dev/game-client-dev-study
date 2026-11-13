#pragma once
#include "Engine_Defines.h"
#include "Component.h"

NS_BEGIN(Engine)
class ENGINE_DLL CModel : public CComponent
{
private:
	CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	CModel(const CModel& rhs);
public:
	~CModel() = default; 

public:
	uint32_t Get_NumMeshes() const {return m_iNumMeshes;}

public:
	virtual	HRESULT			Initialize_Prototype(MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	virtual	HRESULT			Initialize(void* pArg)override;

public:
	virtual HRESULT			Render(uint32_t iMeshIndex);
	virtual	HRESULT			Render_Instanced(uint32_t iMeshIndex, ID3D11Buffer* pInstanceVB, uint32_t iInstanceStride, uint32_t iNumInstances);
	virtual	HRESULT			Bind_Material(uint32_t iMeshIndex, aiTextureType eType, uint32_t iIndex, uint32_t iSlot);
	virtual HRESULT			Bind_BoneMatrix(uint32_t iMeshIndex, uint32_t iSlot);

	virtual void			SetUseCulling(bool_t bUse) { m_bUseCulling = bUse; }
	virtual bool_t			IsUseCulling() { return m_bUseCulling; }

	virtual int32_t			Get_BoneIndex(const char_t* pBoneName);

	virtual BoundingBox		GetBoundinBox() { return m_tLocalBox; }

	virtual	void			PlayAnimation(f32_t fDeltaTime);
private:
	const	aiScene*	m_pAiScene = { nullptr };
	Assimp::Importer	m_pImporter = {};

private:
	MODEL								m_eType = { MODEL::END };

	vector<shared_ptr <class CMesh>>	m_Meshes;
	uint32_t							m_iNumMeshes = {};

	vector<shared_ptr<class CMaterial>> m_Materials;
	uint32_t							m_iNumMaterials = {};

	vector<shared_ptr<class CBone>>		m_Bones;

	BoundingBox					m_tLocalBox = {};
	bool_t						m_bUseCulling = { false };

	float4x4_t					m_PreTransformMatrix = {};

private:
	HRESULT	Ready_Meshes(MODEL eType, fmatrix_t PreTransformMatrix);
	HRESULT	Ready_Materials(const char_t* pModelFilePath);
	HRESULT	Ready_Bones(const aiNode* pAINode, int32_t iParentIndex);

	HRESULT	Load_Binary(const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	HRESULT	Read_Header(FILE* pFile);
	HRESULT Read_Meshes(FILE* pFile, fmatrix_t PreTranformMatrix);
	HRESULT Read_Materials(FILE* pFile, const char_t* pModelFilePath);

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END