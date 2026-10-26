#include "Renderer.h"

#include "GameObject.h"

CRenderer::CRenderer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice { pDevice }
    , m_pContext { pContext }
{

}

HRESULT CRenderer::Initialize()
{
    return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eGroupID, shared_ptr<class CGameObject> pRenderObject)
{
    if (eGroupID >= RENDERGROUP::END)
        return E_FAIL;

    m_RenderGroups[ETOUI(eGroupID)].push_back(pRenderObject);

    return S_OK;
}

HRESULT CRenderer::Draw()
{
    if (FAILED(Render_Priority()))
        return E_FAIL;

    if (FAILED(Render_NonBlend()))
        return E_FAIL;

    if (FAILED(Render_Blend()))
        return E_FAIL;

    if (FAILED(Render_UI()))
        return E_FAIL;

    return S_OK;
}

HRESULT CRenderer::Render_Priority()
{
    for (auto& pRenderObject : m_RenderGroups[ETOUI(RENDERGROUP::PRIORITY)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();
    }

    m_RenderGroups[ETOUI(RENDERGROUP::PRIORITY)].clear();

    return S_OK;
}

HRESULT CRenderer::Render_NonBlend()
{
    for (auto& pRenderObject : m_RenderGroups[ETOUI(RENDERGROUP::NONBLEND)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();
    }

    m_RenderGroups[ETOUI(RENDERGROUP::NONBLEND)].clear();

    return S_OK;
}

HRESULT CRenderer::Render_Blend()
{
    for (auto& pRenderObject : m_RenderGroups[ETOUI(RENDERGROUP::BLEND)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();
    }

    m_RenderGroups[ETOUI(RENDERGROUP::BLEND)].clear();

    return S_OK;
}

HRESULT CRenderer::Render_UI()
{
    for (auto& pRenderObject : m_RenderGroups[ETOUI(RENDERGROUP::UI)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();
    }

    m_RenderGroups[ETOUI(RENDERGROUP::UI)].clear();

    return S_OK;
}

unique_ptr<CRenderer> CRenderer::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = unique_ptr<CRenderer>(new CRenderer(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CRenderer");
        pInstance.reset();
    }

    return pInstance;
}
