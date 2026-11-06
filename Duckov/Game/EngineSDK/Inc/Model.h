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
	virtual	HRESULT			Initialize_Prototype(const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	virtual	HRESULT			Initialize(void* pArg)override;
	virtual HRESULT			Render();

	virtual void			SetUseCulling(bool_t bUse) { m_bUseCulling = bUse; }
	virtual bool_t			IsUseCulling() { return m_bUseCulling; }

	virtual BoundingBox		GetBoundinBox() { return m_tLocalBox; }

private:
	const	aiScene*	m_pAiScene = { nullptr };
	Assimp::Importer	m_pImporter = {};

private:
	vector<shared_ptr <class CMesh>> m_Meshes;
	uint32_t	m_iNumMeshes = {};

	BoundingBox					m_tLocalBox = {};
	bool_t						m_bUseCulling = { false };

private:
	HRESULT	Ready_Meshes(fmatrix_t PreTransformMatrix);

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END