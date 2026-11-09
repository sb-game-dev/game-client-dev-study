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
	virtual	HRESULT			Initialize_Prototype(const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	virtual	HRESULT			Initialize(void* pArg)override;

public:
	virtual HRESULT			Render(uint32_t iMeshIndex);
	virtual	HRESULT			Bind_Material(uint32_t iMeshIndex, aiTextureType eType, uint32_t iIndex, uint32_t iSlot);

	virtual void			SetUseCulling(bool_t bUse) { m_bUseCulling = bUse; }
	virtual bool_t			IsUseCulling() { return m_bUseCulling; }

	virtual BoundingBox		GetBoundinBox() { return m_tLocalBox; }

private:
	const	aiScene*	m_pAiScene = { nullptr };
	Assimp::Importer	m_pImporter = {};

private:
	vector<shared_ptr <class CMesh>>	m_Meshes;
	uint32_t							m_iNumMeshes = {};

	vector<shared_ptr<class CMaterial>> m_Materials;
	uint32_t							m_iNumMaterials = {};

	BoundingBox					m_tLocalBox = {};
	bool_t						m_bUseCulling = { false };

private:
	HRESULT	Ready_Meshes(fmatrix_t PreTransformMatrix);
	HRESULT	Ready_Materials(const char_t* pModelFilePath);

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END