#include "Material.h"

CMaterial::CMaterial(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
{
}

CMaterial::~CMaterial()
{
}

HRESULT CMaterial::Initialize(const char_t* pModelFilePath, const aiMaterial* pAIMaterial)
{
	// 텍스처 경로 = 모델의 경로 + 텍스처 파일 이름 
	for (uint32_t i = 0; i < AI_TEXTURE_TYPE_MAX; ++i)
	{
		uint32_t	iNumTexture = pAIMaterial->GetTextureCount(static_cast<aiTextureType>(i));
		for (uint32_t j = 0; j < iNumTexture; ++j)
		{
			aiString strTexturePath = {};
			// pAIMaterial로부터 텍스처의 경로를 가져온다.
			// 다만 이 경로는 실제 경로가 아닐 수 있기 때문에 파일 이름만 추출한다.
			if (FAILED(pAIMaterial->GetTexture(static_cast<aiTextureType>(i), j, &strTexturePath)))
				return E_FAIL;
			
			// 모델의 경로
			char	szDrive[MAX_PATH] = {};
			char	szDir[MAX_PATH] = {};
			
			// 텍스처 파일 이름 + 확장자
			char	szFileName[MAX_PATH] = {};
			char	szExt[MAX_PATH] = {};

			// 모델 경로 추출
			_splitpath_s(pModelFilePath, szDrive, MAX_PATH, szDir, MAX_PATH, nullptr, 0, nullptr, 0);

			// 텍스처 파일이름 + 확장자 추출
			_splitpath_s(strTexturePath.C_Str(), nullptr, 0, nullptr, 0, szFileName, MAX_PATH, szExt, MAX_PATH);	//strTexturePath.C_Str() -> aiString 내부 문자열을 const char*로 꺼낸다

			// 파일 경로 문자열 조립
			char	szTempFilePath[MAX_PATH] = {};
			strcpy_s(szTempFilePath, szDrive);
			strcat_s(szTempFilePath, szDir);
			strcat_s(szTempFilePath, szFileName);
			strcat_s(szTempFilePath, szExt);

			// 최종 텍스처 경로 완성
			wchar_t		szPerfectPath[MAX_PATH] = {};
			MultiByteToWideChar(CP_ACP, 0, szTempFilePath, strlen(szTempFilePath), szPerfectPath, MAX_PATH);

			// 텍스처 추출
			HRESULT         hr = {};
			ComPtr<ID3D11ShaderResourceView>        pSRV = { nullptr };

			if (false == strcmp(szExt, ".dds"))
				hr = CreateDDSTextureFromFile(m_pDevice.Get(), szPerfectPath, nullptr, &pSRV);

			else if (false == strcmp(szExt, ".tga"))
				hr = E_FAIL;

			else
				hr = CreateWICTextureFromFile(m_pDevice.Get(), szPerfectPath, nullptr, &pSRV);

			if (FAILED(hr))
				return E_FAIL;

			m_Materials[i].push_back(pSRV);
		}
	}
	return S_OK;
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

		aiTextureType eAiType = {};
		To_AiTextureType(static_cast<Engine::ModelFile::TEXTURE_TYPE>(iType), eAiType);
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

		m_Materials[eAiType].push_back(pSRV);
	}

	return S_OK;
}

HRESULT CMaterial::Bind_Pixel_ShaderResource(aiTextureType eType, uint32_t iIndex, uint32_t iSlot)
{
	if (iIndex >= m_Materials[eType].size())
		return E_FAIL;

	m_pContext->PSSetShaderResources(iSlot, 1, m_Materials[eType][iIndex].GetAddressOf());
	return S_OK;
}



bool_t CMaterial::To_AiTextureType(ModelFile::TEXTURE_TYPE eType, aiTextureType& eOutType)
{
	switch (eType)
	{
	case ModelFile::TEXTURE_TYPE::DIFFUSE:	eOutType = aiTextureType_DIFFUSE;	return true;
	case ModelFile::TEXTURE_TYPE::NORMALS:	eOutType = aiTextureType_NORMALS;	return true;
	case ModelFile::TEXTURE_TYPE::SPECULAR:	eOutType = aiTextureType_SPECULAR;	return true;
	case ModelFile::TEXTURE_TYPE::EMISSIVE:	eOutType = aiTextureType_EMISSIVE;	return true;
	default:								return false;
	}
}

shared_ptr<CMaterial> CMaterial::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, const aiMaterial* pAIMaterial)
{
	auto pInstance = shared_ptr<CMaterial>(new CMaterial(pDevice, pContext));
	if (FAILED(pInstance->Initialize(pModelFilePath, pAIMaterial)))
	{
		MSG_BOX("Failed to Create : Material");
		pInstance.reset();
	}
	return pInstance;
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