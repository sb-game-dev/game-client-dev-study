#include "Mirror.h"

CMirror::CMirror(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CMirror::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 레스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // Material
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 0.5f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    return S_OK;
}

HRESULT CMirror::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    m_pTransformCom->Set_Scale(6.f, 10.f, 1.f);

    if (FAILED(Ready_Components()))
        return E_FAIL;

    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    return S_OK;
}

void CMirror::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CMirror::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CMirror::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CMirror::Render()
{
    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());

    if (FAILED(Bind_Shader(m_pVS, m_pPS)))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}

XMVECTOR CMirror::Get_MirrorPlane()
{
    vector_t vPos = m_pTransformCom->Get_State(STATE::POSITION);

    return XMPlaneFromPointNormal(vPos,XMVectorSet(0.f,0.f,-1.f,0.f));
}

HRESULT CMirror::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Mirror,
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Rect,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXTEX,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
    return S_OK;
}

HRESULT CMirror::Ready_ConstantBuffer()
{
    matrix_t    matNoTrans = m_pTransformCom->Get_World();
    matNoTrans.r[3] = vector_t{ 0.f,0.f,0.f,1.f };
    XMStoreFloat4x4(&m_tCBData.mat_World, m_pTransformCom->Get_World());
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans)));
    m_tCBData.tMaterial = m_tMaterial;
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext,&m_tCBData,sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CMirror::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CMirror::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(CGameInstance::Get().Bind_Sampler_Pixel_Shader(g_strSampler_Linear, 0)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pTextureCom->Set_TexturePS(0, 0)))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CMirror> CMirror::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CMirror>(new CMirror(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CMirror");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CMirror::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CMirror>(new CMirror(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CMirror");
        pInstance.reset();
    }
    return pInstance;
}
