#include "StaticProp.h"

CStaticProp::CStaticProp (ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject(pDevice, pContext)
{
}

HRESULT CStaticProp::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_NONE;          // D3D11_CULL_BACK , D3D11_CULL_FRONT,D3D11_CULL_NONE
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // Material
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    return S_OK;
}

HRESULT CStaticProp::Initialize(void* pArg)
{
    //auto pDesc = static_cast<STATICPROP_DESC*>(pArg);

    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    return S_OK;
}

void CStaticProp ::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CStaticProp ::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CStaticProp ::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));


}

HRESULT CStaticProp ::Render()
{
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS);
}

HRESULT CStaticProp ::Ready_Components()
{
    //if (FAILED(__super::Add_Component(m_iLevelIndex, m_strTexturePath,
    //    TEXT("Com_Texture"), m_pTextureCom)))
    //    return E_FAIL;
//
    //if (FAILED(__super::Add_Component(m_iLevelIndex, m_strMeshPath ,
    //    TEXT("Com_Buffer"), m_pBufferCom)))
    //    return E_FAIL;

    if (FAILED(Ready_Mesh()))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::VS_VTXTEX,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::PS_VTXTEX_NOLIGHT,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    return S_OK;
}

HRESULT CStaticProp ::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

HRESULT CStaticProp::Ready_Mesh()
{
    wstring_t strMeshTag;
    if (FAILED(CGameInstance::Get().Get_or_Load_Mesh(m_iLevelIndex, m_strMeshPath, strMeshTag)))
        return E_FAIL;
    m_strMeshPath = strMeshTag;                     // 정규화된 값으로 보관 → 저장도 이 값으로

    if (0 == strMeshTag.rfind(g_strBuiltinPrefix, 0))
    {
        if (FAILED(__super::Add_Component(m_iLevelIndex, strMeshTag, TEXT("Com_Buffer"), m_pBufferCom)))
            return E_FAIL;

        wstring_t strTexTag;
        if (FAILED(CGameInstance::Get().Get_Or_Load_Texture(m_iLevelIndex, m_strTexturePath, strTexTag)))
            return E_FAIL;
        m_strTexturePath = strTexTag;

        if (FAILED(__super::Add_Component(m_iLevelIndex, strTexTag, TEXT("Com_Texture"), m_pTextureCom)))
            return E_FAIL;
    }
    else
    {
        return E_FAIL;      // 10단계: 모델
    }
    return S_OK;
}

HRESULT CStaticProp::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));
    m_tCBData.tMaterial = m_tMaterial;

    return S_OK;
}

HRESULT CStaticProp::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Bind_Sampler_Pixel_Shader(g_strSampler_Linear, 0)))
        return E_FAIL;

    if (FAILED(m_pTextureCom->Bind_Pixel_ShaderResource(0, 0)))
        return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    m_pContext->RSSetState(pRS);

    if (FAILED(Bind_ShaderResources(matWorld)))
        return E_FAIL;

    if (FAILED(Bind_Shader(m_pVS, pPS)))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CStaticProp > CStaticProp::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CStaticProp >(new CStaticProp (pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CStaticProp::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CStaticProp >(new CStaticProp (*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
