#include "Texture.h"

CTexture::CTexture(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CComponent{pDevice, pContext}
{
}

HRESULT CTexture::Initialize_Prototype(const tchar_t* pTextureFilePath, uint32_t iNumTextures)
{
	m_iNumTextures = iNumTextures;
	for (uint32_t i = 0; i < iNumTextures; ++i)
	{
		ComPtr<ID3D11ShaderResourceView>	pSRV = { nullptr };

		tchar_t		szTextureFilePath[MAX_PATH] = {};
		wsprintf(szTextureFilePath, pTextureFilePath, i);

		tchar_t szEXT[MAX_PATH] = {};
		_wsplitpath_s(szTextureFilePath, nullptr, 0, nullptr, 0, nullptr, 0, szEXT, MAX_PATH);

		HRESULT		hr = {};

		if (false == lstrcmp(szEXT, TEXT(".dds")))
			hr = CreateDDSTextureFromFile(m_pDevice.Get(), szTextureFilePath, nullptr, &pSRV);
		else if(false == lstrcmp(szEXT,TEXT(".tga")))
			hr = E_FAIL;
		else
			hr = CreateWICTextureFromFile(m_pDevice.Get(), szTextureFilePath, nullptr, &pSRV);

		if (FAILED(hr))
			return E_FAIL;
		m_SRVs.push_back(pSRV);
	}
	return S_OK;
}

HRESULT CTexture::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CTexture::Bind_Pixel_ShaderResource(const uint32_t& iSlot, const uint32_t& iIndex)
{
	if (m_SRVs.size() <= iIndex)
		return E_FAIL;

	m_pContext->PSSetShaderResources(iSlot, 1, m_SRVs[iIndex].GetAddressOf());
	return S_OK;
}

HRESULT CTexture::Bind_Pixel_ShaderResources(const uint32_t& iSlot)
{
	if (m_iNumTextures >= D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
		return E_FAIL;

	ID3D11ShaderResourceView* pSRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = {};

	uint32_t        iNumTextures = {};

	for (auto& pSRV : m_SRVs)
	{
		pSRVs[iNumTextures++] = pSRV.Get();
	}

	m_pContext->PSSetShaderResources(iSlot, iNumTextures, pSRVs);

	return S_OK;
}

HRESULT CTexture::Set_TexturePS(const uint32_t& iIndex, const uint32_t& iStartSlot)
{
	if (m_SRVs.size() <= iIndex)
		return E_FAIL;

	m_pContext->PSSetShaderResources(iStartSlot, 1, m_SRVs[iIndex].GetAddressOf());
	return S_OK;
}
HRESULT CTexture::Set_TextureCS(const uint32_t& iIndex, const uint32_t& iStartSlot)
{
	if (m_SRVs.size() <= iIndex)
		return E_FAIL;

	m_pContext->CSSetShaderResources(iStartSlot, 1, m_SRVs[iIndex].GetAddressOf());
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