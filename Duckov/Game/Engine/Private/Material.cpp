#include "Material.h"

CMaterial::CMaterial(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
{
}

CMaterial::~CMaterial()
{
}

HRESULT CMaterial::Initialize(const char_t* pModelFilePath, FILE* pFile)
{
	// 텍스처 파일 경로 부분을 모델 경로로부터 뽑아내기
	char_t	szDrive[MAX_PATH] = {};
	char_t	szDir[MAX_PATH] = {};
	_splitpath_s(pModelFilePath, szDrive, MAX_PATH, szDir, MAX_PATH, nullptr, 0, nullptr, 0);

	uint32_t iNumTextures = {};
	fread(&iNumTextures, sizeof(uint32_t), 1, pFile);

	for (uint32_t i = 0; i < iNumTextures; ++i)
	{
		uint32_t iType = {};
		uint32_t iLength = {};
		fread(&iType, sizeof(uint32_t), 1, pFile);
		fread(&iLength, sizeof(uint32_t), 1, pFile);

		char_t szFileName[MAX_PATH] = {};
		fread(szFileName, sizeof(char_t), iLength, pFile);

		char_t	szTempFilePath[MAX_PATH] = {};
		strcpy_s(szTempFilePath, szDrive);
		strcat_s(szTempFilePath, szDir);
		strcat_s(szTempFilePath, szFileName);

		wchar_t	szPerfectPath[MAX_PATH] = {};
		MultiByteToWideChar(CP_ACP, 0, szTempFilePath, -1, szPerfectPath, MAX_PATH);

		char_t	szExt[MAX_PATH] = {};
		_splitpath_s(szFileName, nullptr, 0, nullptr, 0, nullptr, 0, szExt, MAX_PATH);

		HRESULT		hr = {};
		ComPtr<ID3D11ShaderResourceView>	pSRV = { nullptr };

		if (0 == strcmp(szExt, ".dds"))
			hr = CreateDDSTextureFromFile(m_pDevice.Get(), szPerfectPath, nullptr, &pSRV);
		else if (0 == strcmp(szExt, ".tga"))
			hr = E_FAIL;
		else
			hr = CreateWICTextureFromFile(m_pDevice.Get(), szPerfectPath, nullptr, &pSRV);

		if (FAILED(hr))
		{
			MSG_BOX("Failed to Load : Texture");
			return E_FAIL;
		}
		m_Materials[iType].push_back(pSRV);
	}

	return S_OK;
}

HRESULT CMaterial::Bind_Pixel_ShaderResource(ModelFile::TEXTURE_TYPE eType, uint32_t iIndex, uint32_t iSlot)
{
	if (iIndex >= m_Materials[ETOUI(eType)].size())
		return E_FAIL;

	m_pContext->PSSetShaderResources(iSlot, 1, m_Materials[ETOUI(eType)][iIndex].GetAddressOf());
	return S_OK;
}

shared_ptr<CMaterial> CMaterial::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, FILE* pFile)
{
	auto pInstance = shared_ptr<CMaterial>(new CMaterial(pDevice, pContext));
	if (FAILED(pInstance->Initialize(pModelFilePath, pFile)))
	{
		MSG_BOX("Failed to Create : Material (Binary)");
		pInstance.reset();
	}
	return pInstance;
}