#include "Material.h"

CMaterial::CMaterial(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice { pDevice }
    , m_pContext { pContext }
{
}

HRESULT CMaterial::Initialize(const char_t* pModelFilePath, const aiMaterial* pAIMaterial)
{
    for (uint32_t i = 0; i < AI_TEXTURE_TYPE_MAX; i++)
    {
        uint32_t    iNumTexture = pAIMaterial->GetTextureCount(static_cast<aiTextureType>(i));

        for (uint32_t j = 0; j < iNumTexture; j++)
        {
            aiString        strTexturePath = {};

            if (FAILED(pAIMaterial->GetTexture(static_cast<aiTextureType>(i), j, &strTexturePath)))
                return E_FAIL;

            char            szDrive[MAX_PATH] = {};
            char            szDir[MAX_PATH] = {};
            char            szFileName[MAX_PATH] = {};
            char            szExt[MAX_PATH] = {};

            _splitpath_s(pModelFilePath, szDrive, MAX_PATH, szDir, MAX_PATH, nullptr, 0, nullptr, 0);
            _splitpath_s(strTexturePath.C_Str(), nullptr, 0, nullptr, 0, szFileName, MAX_PATH, szExt, MAX_PATH);

            char            szFilePath[MAX_PATH] = {};
            strcpy_s(szFilePath, szDrive);
            strcat_s(szFilePath, szDir);
            strcat_s(szFilePath, szFileName);
            strcat_s(szFilePath, szExt);

            wchar_t         szPerfectPath[MAX_PATH] = {};
            MultiByteToWideChar(CP_ACP, 0, szFilePath, strlen(szFilePath), szPerfectPath, MAX_PATH);


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

HRESULT CMaterial::Bind_Pixel_ShaderResource(aiTextureType eType, uint32_t iIndex, uint32_t iSlot)
{
    if (iIndex >= m_Materials[eType].size())
        return E_FAIL;


    m_pContext->PSSetShaderResources(iSlot, 1, m_Materials[eType][iIndex].GetAddressOf());

    return S_OK;
}

shared_ptr<CMaterial> CMaterial::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, const aiMaterial* pAIMaterial)
{
    auto pInstance = shared_ptr<CMaterial>(new CMaterial(pDevice, pContext));

    if (FAILED(pInstance->Initialize(pModelFilePath, pAIMaterial)))
    {
        MSG_BOX("Failed to Created : CMaterial");
        pInstance.reset();
    }

    return pInstance;
}
