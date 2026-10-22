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
	HRESULT Initialize(const aiMaterial* pAIMaterial, const char_t* pModelFilePath); 
	HRESULT Bind_Material(aiTextureType eType, uint32_t iTextureIndex, uint32_t iSlot);

	uint32_t Get_NumTextures(aiTextureType eType) const {
		return static_cast<uint32_t>(m_Textures[eType].size());
	}
private:
	ComPtr<ID3D11Device>						m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>					m_pContext = { nullptr };

	vector<ComPtr<ID3D11ShaderResourceView>>	m_Textures[AI_TEXTURE_TYPE_MAX];

public:
	static shared_ptr<CMaterial> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const aiMaterial* pAIMaterial, const char_t* pModelFilePath);
};

NS_END