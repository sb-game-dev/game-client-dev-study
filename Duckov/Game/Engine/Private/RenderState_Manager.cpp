#include "RenderState_Manager.h"

CRenderState_Manager::CRenderState_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice{pDevice}
    , m_pContext{pContext}
{
}

HRESULT CRenderState_Manager::Initialize()
{
    if (FAILED(Ready_RasterizeState()))
        return E_FAIL;
    if (FAILED(Ready_DepthStencilState()))
        return E_FAIL;
    if (FAILED(Ready_BlendState()))
        return E_FAIL;
    Bind_RasterizerState(g_strRS_Default);
    return S_OK;
}

HRESULT CRenderState_Manager::Add_RasterizerState(const wstring_t& strRSTag, const D3D11_RASTERIZER_DESC& RSDesc)
{
    if (nullptr != Find_RasterizerState(strRSTag))
        return E_FAIL;

    ComPtr<ID3D11RasterizerState> RS = {};
    if(FAILED(m_pDevice->CreateRasterizerState(&RSDesc, RS.GetAddressOf())))
        return E_FAIL;
    
    m_RasterizerStates.emplace(strRSTag, RS);
    
    return S_OK;
}

HRESULT CRenderState_Manager::Bind_RasterizerState(const wstring_t& strRSTag)
{
    auto pRasterizerState = Find_RasterizerState(strRSTag);
    if (nullptr == pRasterizerState)
        return E_FAIL;
    
    m_pContext->RSSetState(pRasterizerState.Get());

    return S_OK;
}

HRESULT CRenderState_Manager::Add_DepthStencilState(const wstring_t& strDSSTag, const D3D11_DEPTH_STENCIL_DESC& DSSDesc)
{
    if (nullptr != Find_DepthStencilState(strDSSTag))
        return E_FAIL;

    ComPtr<ID3D11DepthStencilState> DSS = {};
    if (FAILED(m_pDevice->CreateDepthStencilState(&DSSDesc, DSS.GetAddressOf())))
        return E_FAIL;

    m_DepthStensilStates.emplace(strDSSTag, DSS);

    return S_OK;
}

HRESULT CRenderState_Manager::Bind_DepthStencilState(const wstring_t& strDSSTag, uint32_t StencilRef)
{
    auto pDepthStencilState = Find_DepthStencilState(strDSSTag);
    if (nullptr == pDepthStencilState)
        return E_FAIL;

    m_pContext->OMSetDepthStencilState(pDepthStencilState.Get(), StencilRef);
    return S_OK;
}

HRESULT CRenderState_Manager::Add_BlendState(const wstring_t& strBlendTag, const D3D11_BLEND_DESC& BlendDesc)
{
    if (nullptr != Find_BlendState(strBlendTag))
        return E_FAIL;

    ComPtr<ID3D11BlendState> BS = {};
    if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, BS.GetAddressOf())))
        return E_FAIL;

    m_BlendStates.emplace(strBlendTag, BS);
    return S_OK;
}

HRESULT CRenderState_Manager::Bind_BlendState(const wstring_t& strBlendTag, f32_t* pBlendFactor, uint32_t SampleMask)
{
    auto pBlendState = Find_BlendState(strBlendTag);
    if (nullptr == pBlendState)
        return E_FAIL;

    f32_t		fFactor[4] = {};
    if (nullptr != pBlendFactor)
        memcpy(fFactor, pBlendFactor, sizeof f32_t * 4);

    m_pContext->OMSetBlendState(pBlendState.Get(), fFactor, SampleMask);
    return S_OK;
}

ComPtr<ID3D11RasterizerState> CRenderState_Manager::Find_RasterizerState(const wstring_t& strRSTag)
{
    auto iter = m_RasterizerStates.find(strRSTag);
    if (m_RasterizerStates.end() == iter)
        return nullptr;
    return iter->second;
}

ComPtr<ID3D11DepthStencilState> CRenderState_Manager::Find_DepthStencilState(const wstring_t& strRSTag)
{
    auto iter = m_DepthStensilStates.find(strRSTag);
    if (m_DepthStensilStates.end() == iter)
        return nullptr;
    return iter->second;
}

ComPtr<ID3D11BlendState> CRenderState_Manager::Find_BlendState(const wstring_t& strRSTag)
{
    auto iter = m_BlendStates.find(strRSTag);
    if (m_BlendStates.end() == iter)
        return nullptr;
    return iter->second;
}

HRESULT CRenderState_Manager::Ready_RasterizeState()
{
    if (FAILED(Add_RasterizerState(g_strRS_Default, g_RS_DefaultDesc)))
        return E_FAIL;
    if (FAILED(Add_RasterizerState(g_strRS_Cull_None, g_RS_Cull_None)))
        return E_FAIL;
    if (FAILED(Add_RasterizerState(g_strRS_Cull_Front, g_RS_Cull_Front)))
        return E_FAIL;
    return S_OK;
}

HRESULT CRenderState_Manager::Ready_DepthStencilState()
{
    if (FAILED(Add_DepthStencilState(g_strDSS_Default, g_DSS_Default_Desc)))
        return E_FAIL;
    if (FAILED(Add_DepthStencilState(g_strDSS_NonZ, g_DSS_NonZ_Desc)))
        return E_FAIL;
    if (FAILED(Add_DepthStencilState(g_strDSS_MirrorMark, g_DSS_MirrorMark_Desc)))
        return E_FAIL;
    if (FAILED(Add_DepthStencilState(g_strDSS_MirrorReflect, g_DSS_MirrorReflect_Desc)))
        return E_FAIL;
    if (FAILED(Add_DepthStencilState(g_strDSS_SilhouetteMark, g_DSS_MarkSilhouetteMark_Desc)))
        return E_FAIL;
    if (FAILED(Add_DepthStencilState(g_strDSS_NoDoubleBlend, g_DSS_NoDoubleBlend_Desc)))
        return E_FAIL;
    if (FAILED(Add_DepthStencilState(g_strDSS_Alpha, g_DSS_Alpha_Desc)))
        return E_FAIL;
    return S_OK;
}

HRESULT CRenderState_Manager::Ready_BlendState()
{
    if (FAILED(Add_BlendState(g_strBS_Default, g_BS_Default_Desc)))
        return E_FAIL;
    if (FAILED(Add_BlendState(g_strBS_AlphaBlend, g_BS_AlphaBlend_Desc)))
        return E_FAIL;
    if (FAILED(Add_BlendState(g_strBS_NoColor, g_BS_NoColor_Desc)))
        return E_FAIL;
    return S_OK;
}

unique_ptr<CRenderState_Manager> CRenderState_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = unique_ptr<CRenderState_Manager>(new CRenderState_Manager(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Create : CRenderState_Manager");
        pInstance.reset();
    }
    return pInstance;
}
