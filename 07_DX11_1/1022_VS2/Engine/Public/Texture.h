#pragma once

#include "Component.h"

NS_BEGIN(Engine)

class ENGINE_DLL CTexture final : public CComponent
{
private:
	CTexture(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	virtual ~CTexture() = default;

public:	
	virtual HRESULT Initialize_Prototype(const tchar_t* pTextureFilePath, uint32_t iNumTextures);
	virtual HRESULT Initialize(void* pArg) override;

private:
	uint32_t											m_iNumTextures = {};
	vector<ComPtr<ID3D11ShaderResourceView>>			m_SRVs;

public:
	static shared_ptr<CTexture> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pTextureFilePath, uint32_t iNumTextures);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END