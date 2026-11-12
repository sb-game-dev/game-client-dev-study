#pragma once

#include "Engine_Defines.h"
/* FBX의 머티리얼(aiMaterial) 하나를 받아서 그 머티리얼이 쓰는 텍스처 파일을 전부 SRV로 로드해둔다. */
/* 텍스처는 종류(aiTextureType)별로 따로 보관한다.*/
/*
m_Textures[aiTextureType_DIFFUSE]  = { 디퓨즈 SRV, ... }
m_Textures[aiTextureType_NORMALS]  = { 노멀 SRV, ... }
m_Textures[aiTextureType_EMISSIVE] = { ... }
*/

/* Model이 들고있는 부품 */


NS_BEGIN(Engine)

class CMaterial
{
private:
	CMaterial(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CMaterial();

public:
	HRESULT	Initialize(const char_t* pModelFilePath, const aiMaterial* pAIMaterial);
	HRESULT	Initialize(const char_t* pModelFilePath, FILE* pFile);
	HRESULT	Bind_Pixel_ShaderResource(aiTextureType eType, uint32_t iIndex, uint32_t iSlot);

public:
	const wstring_t& Get_Name() const { return m_strName; }

private:
	ComPtr<ID3D11Device>						m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>					m_pContext = { nullptr };
	vector<ComPtr<ID3D11ShaderResourceView>>	m_Materials[AI_TEXTURE_TYPE_MAX];
	wstring_t									m_strName;
private:
	static bool_t	To_AiTextureType(ModelFile::TEXTURE_TYPE eType, aiTextureType& eOutType);
public:
	static shared_ptr<CMaterial> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, const aiMaterial* pAIMaterial);
	static shared_ptr<CMaterial> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, FILE* pFile);
};

NS_END