#pragma once

#include "Component.h"

NS_BEGIN(Engine)

class ENGINE_DLL CModel final : public CComponent
{
private:
	CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CModel() = default;

public:
	virtual HRESULT Initialize_Prototype(const char_t* pModelFilePath);
	virtual HRESULT Initialize(void* pArg) override;

private:
	const aiScene*				m_pAIScene = { nullptr };
	Assimp::Importer			m_Importer = {};

private:
	vector<shared_ptr<class CMesh>>		m_Meshes;

private:
	HRESULT Ready_Meshes();

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath);
	virtual shared_ptr<CPrototype> Clone(void* pArg);
};

NS_END