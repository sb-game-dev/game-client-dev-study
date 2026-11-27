#include "Font_Manager.h"

#include "CustomFont.h"

CFont_Manager::CFont_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice { pDevice }
    , m_pContext { pContext }
{

}

HRESULT CFont_Manager::Add_Font(const wstring_t& strFontTag, const tchar_t* pFontFilePath)
{
    if (nullptr != Find_Font(strFontTag))
        return E_FAIL;

    auto        pFont = CCustomFont::Create(m_pDevice, m_pContext, pFontFilePath);
    if (nullptr == pFont)
        return E_FAIL;

    m_Fonts.emplace(strFontTag, pFont);

    return S_OK;
}

shared_ptr<class CCustomFont> CFont_Manager::Find_Font(const wstring_t& strFontTag)
{
    auto        iter = m_Fonts.find(strFontTag);
    if (iter == m_Fonts.end())
        return nullptr;

    return iter->second; 
}

unique_ptr<CFont_Manager> CFont_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    return unique_ptr<CFont_Manager>(new CFont_Manager(pDevice, pContext));
}
