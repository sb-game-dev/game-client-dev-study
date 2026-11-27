#include "CustomFont.h"

CCustomFont::CCustomFont(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice { pDevice }
    , m_pContext { pContext }
{
}

HRESULT CCustomFont::Initialize(const tchar_t* pFontFilePath)
{
    m_pFont = make_shared<SpriteFont>(m_pDevice.Get(), pFontFilePath);
    m_pBatch = make_shared<SpriteBatch>(m_pContext.Get());

    return S_OK;
}

shared_ptr<CCustomFont> CCustomFont::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pFontFilePath)
{
    auto pInstance = shared_ptr<CCustomFont>(new CCustomFont(pDevice, pContext));

    if (FAILED(pInstance->Initialize(pFontFilePath)))
    {
        MSG_BOX("Failed to Created : CCustomFont");
        pInstance.reset();
    }

    return pInstance;
}
