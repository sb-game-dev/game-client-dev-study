#pragma once
#include "Engine_Defines.h"
#include "Component.h"
NS_BEGIN(Engine)
class ENGINE_DLL CTexture : public CComponent
{
private:
	CTexture(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CTexture() = default;


public:
	HRESULT	Initialize_Prototype(const tchar_t* pTextureFilePath, uint32_t iNumTextures);
	HRESULT	Initialize(void* pArg) override;

	HRESULT	Set_TexturePS(const uint32_t& iIndex, const uint32_t& iStartSlot); //Bind_Pixel_ShaderResource(Slot,Index)
	HRESULT	Set_TextureCS(const uint32_t& iIndex, const uint32_t& iStartSlot);

private:
	uint32_t									m_iNumTextures = {};
	vector<ComPtr<ID3D11ShaderResourceView>>	m_SRVs;

public:
	static shared_ptr<CTexture> Create(ComPtr<ID3D11Device> pDevice, 
									   ComPtr<ID3D11DeviceContext> pContext, 
									   const tchar_t* pTextureFilePath, 
									   uint32_t iNumTextures);
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END