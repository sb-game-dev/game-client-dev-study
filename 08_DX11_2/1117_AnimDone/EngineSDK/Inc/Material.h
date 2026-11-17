#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CMaterial final
{
private:
	CMaterial(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CMaterial() = default;

public:
	HRESULT Initialize(const char_t* pModelFilePath, const aiMaterial* pAIMaterial);
	HRESULT Bind_Pixel_ShaderResource(aiTextureType eType, uint32_t iIndex, uint32_t iSlot);
private:
	ComPtr<ID3D11Device>								m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>							m_pContext = { nullptr };
	vector<ComPtr<ID3D11ShaderResourceView>>			m_Materials[AI_TEXTURE_TYPE_MAX];

public:
	static shared_ptr<CMaterial> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, const aiMaterial* pAIMaterial);

};

NS_END