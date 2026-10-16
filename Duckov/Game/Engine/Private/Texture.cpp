#include "Texture.h"

CTexture::CTexture(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CComponent{pDevice, pContext}
{
}

HRESULT CTexture::Initialize_Prototype(const tchar_t* pTextureFilePath, uint32_t iNumTextures)
{
	return S_OK;
}

HRESULT CTexture::Initialize(void* pArg)
{
	return S_OK;
}

shared_ptr<CTexture> CTexture::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pTextureFilePath, uint32_t iNumTextures)
{
	auto pInstance = shared_ptr<CTexture>(new CTexture(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype(pTextureFilePath,iNumTextures)))
	{
		MSG_BOX("Clone Failed : CTransform");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CPrototype> CTexture::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CPrototype>(new CTexture(*this));

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : CTexture");
		pInstance.reset();
	}
	return pInstance;
}