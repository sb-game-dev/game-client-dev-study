#include "SkyBox.h"

CSkyBox::CSkyBox(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CSkyBox::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_NONE;          // D3D11_CULL_BACK , D3D11_CULL_FRONT,D3D11_CULL_NONE
    rsDesc.FrontCounterClockwise = true;        // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    return S_OK;
}

HRESULT CSkyBox::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    m_pTransformCom->Set_Scale( 20.f,20.f,20.f );
    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
    return S_OK;
}

void CSkyBox::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CSkyBox::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CSkyBox::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    auto pCamera = CGameInstance::Get().Get_MainCamera();
    auto vCamEye = pCamera->GetEye();

    m_pTransformCom->Set_State(STATE::POSITION, { vCamEye.x,vCamEye.y,vCamEye.z,1.f });

    CGameInstance::Get().Add_RenderGroup(RENDERID::PRIORITY, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CSkyBox::Render()
{
    // 레스터라이즈 설정
    m_pContext->RSSetState(m_pRS.Get());
    
    if (FAILED(Bind_Shader(m_pVS,m_pPS)))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(m_pTransformCom->Get_World())))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}

HRESULT CSkyBox::Ready_Components()
{
#ifdef _MAPTOOL
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::MAPTOOL), Proto::Texture_SkyBox,
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::MAPTOOL), Proto::VIBuffer_SkyBox,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::MAPTOOL), Proto::VS_VTXTEX,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_SKYBOX,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
#else
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_SkyBox,
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_SkyBox,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXTEX,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX_SKYBOX,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
#endif // _MAPTOOL
    return S_OK;
}

HRESULT CSkyBox::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CSkyBox::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMStoreFloat4x4(&m_tCBData.mat_World, matWorld);
    return S_OK;
}

HRESULT CSkyBox::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CSkyBox::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    // 샘플러 바인드
    if (FAILED(CGameInstance::Get().Bind_Sampler_Pixel_Shader(g_strSampler_Linear, 0)))
        return E_FAIL;
    // 텍스처 바인드
    if (FAILED(m_pTextureCom->Bind_Pixel_ShaderResource(0, 0)))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CSkyBox> CSkyBox::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CSkyBox>(new CSkyBox(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CSkyBox::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CSkyBox>(new CSkyBox(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
