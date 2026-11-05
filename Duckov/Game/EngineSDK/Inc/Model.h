#pragma once
#include "Engine_Defines.h"
#include "Component.h"

NS_BEGIN(Engine)
class CModel : public CComponent
{
private:
	CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	CModel(const CModel& rhs);
public:
	~CModel() = default;

public:
	virtual	HRESULT Initialize_Prototype(const char_t* pModelFilePath);
	virtual	HRESULT Initialize(void* pArg)override;

private:
	const aiScene*		m_pAiScene = { nullptr };
	Assimp::Importer	m_pImporter = {};

private:
	vector<shared_ptr <class CMesh>> m_Meshes;

private:
	HRESULT	Ready_Meshes();

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath);
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END