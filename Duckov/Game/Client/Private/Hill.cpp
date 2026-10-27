#include "Hill.h"
#include <fstream>

CHill::CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CHill::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // Material
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         
    rsDesc.CullMode = D3D11_CULL_BACK;          
    rsDesc.FrontCounterClockwise = false;       
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    return S_OK;
}

HRESULT CHill::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
    return S_OK;
}

void CHill::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CHill::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CHill::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CHill::Render()
{
    // 레스터라이즈 설정
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

f32_t CHill::GetHeight(f32_t x, f32_t z)
{
    return static_pointer_cast<CVIBuffer_Terrain>(__super::Find_Component(L"Com_Buffer"))->GetHeight(x, z);
}

float4_t CHill::GetPlane(f32_t x, f32_t z)
{
    return static_pointer_cast<CVIBuffer_Terrain>(__super::Find_Component(L"Com_Buffer"))->GetPlane(x, z);
}

HRESULT CHill::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Terrain_Blend,
        TEXT("Com_Texture"), m_pBlendCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Terrain_Layer,
        TEXT("Com_Blend"), m_pLayerCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_TERRAIN,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_TERRAIN,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Terrain,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CHill::Ready_ConstantBuffer()
{
    matrix_t matWorld = m_pTransformCom->Get_World();
    matrix_t matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    matrix_t matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));
    m_tCBData.tMaterial = m_tMaterial;

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CHill::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(m_pVS->Begin()))
        return E_FAIL;

    if (FAILED(m_pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CHill::Bind_ShaderResources(const matrix_t& matWorld)
{
    // 샘플러 바인드
    if (FAILED(CGameInstance::Get().Bind_Sampler_Pixel_Shader(g_strSampler_Linear, 0)))
        return E_FAIL;

    // 텍스처 바인드
    if (FAILED(m_pLayerCom->Set_TexturePS(0, 2)))   // Layer0 잔디     -> t2
        return E_FAIL;
    if (FAILED(m_pLayerCom->Set_TexturePS(1, 3)))   // Layer1 흙       -> t3
        return E_FAIL;
    if (FAILED(m_pLayerCom->Set_TexturePS(2, 4)))   // Layer2 아스팔트 -> t4
        return E_FAIL;
    if (FAILED(m_pBlendCom->Set_TexturePS(0, 5)))   // 혼합맵          -> t5
        return E_FAIL;

    // 상수버퍼 바인드
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CHill> CHill::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CHill>(new CHill(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CHill::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CHill>(new CHill(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
