#include "Asset_Manager.h"
#include "GameInstance.h"

CAsset_Manager::CAsset_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:m_pDevice{pDevice}
	,m_pContext{pContext}
{
}

HRESULT CAsset_Manager::Get_Or_Load_Texture(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag)
{
    strTag = Normalize_AssetPath(strPath);

    if (CGameInstance::Get().Has_Prototype(iLevelIndex, strTag))
        return S_OK;

    if (m_FailedTags.count(strTag))
        return E_FAIL;

    wstring_t strLoadPath = wstring_t(g_strResourceRoot) + strTag;
    auto pTexture = CTexture::Create(m_pDevice, m_pContext, strLoadPath.c_str(), 1);  
    if (nullptr == pTexture)
    {
        m_FailedTags.insert(strTag);
        return E_FAIL;
    }
    return CGameInstance::Get().Add_Prototype(iLevelIndex, strTag, pTexture);         
}

HRESULT CAsset_Manager::Get_or_Load_Mesh(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag)
{
    strTag = Normalize_AssetPath(strPath);

    if (CGameInstance::Get().Has_Prototype(iLevelIndex, strTag))
        return S_OK;
    if (m_FailedTags.count(strTag))
        return E_FAIL;

    shared_ptr<CPrototype> pMesh;
    if (0 == strTag.rfind(g_strBuiltinPrefix, 0))
        pMesh = Create_BuiltinMesh(strTag);

    if (nullptr == pMesh)
    {
        m_FailedTags.insert(strTag);
        return E_FAIL;
    }
    return CGameInstance::Get().Add_Prototype(iLevelIndex, strTag, pMesh);
}

shared_ptr<CPrototype> CAsset_Manager::Create_BuiltinMesh(const wstring_t& strTag)
{
    if (strTag == L"builtin/cube")  
        return CVIBuffer_Cube::Create(m_pDevice, m_pContext);
    if (strTag == L"builtin/rect")
        return CVIBuffer_Rect::Create(m_pDevice, m_pContext);
    return nullptr;
}

unique_ptr<CAsset_Manager> CAsset_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	return unique_ptr<CAsset_Manager>(new CAsset_Manager(pDevice,pContext));
}
