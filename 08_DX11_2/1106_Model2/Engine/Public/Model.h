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
	virtual HRESULT Initialize_Prototype(const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Render();

private:
	const aiScene*				m_pAIScene = { nullptr };
	Assimp::Importer			m_Importer = {};

private:
	uint32_t							m_iNumMeshes = {};
	vector<shared_ptr<class CMesh>>		m_Meshes;

private:
	HRESULT Ready_Meshes(fmatrix_t PreTransformMatrix);

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END