#include "SkyBox.h"

CSkyBox::CSkyBox(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CSkyBox::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 상수 버퍼 생성
    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_PER_OBJECT_LIT);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, &m_pCB)))
        return E_FAIL;
    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_NONE;          // D3D11_CULL_BACK , D3D11_CULL_FRONT,D3D11_CULL_NONE
    rsDesc.FrontCounterClockwise = true;        // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // 샘플러 생성
    D3D11_SAMPLER_DESC samplerDesc{};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MaxLOD = 0.f;

    if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
        return E_FAIL;

    return S_OK;
}

HRESULT CSkyBox::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    m_pTransformCom->Set_Scale( 20.f,20.f,20.f );
    if (FAILED(Ready_Components()))
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
    XMMATRIX matWorld = m_pTransformCom->Get_World();

    // 역전치 행렬은 이동 성분을 뺀 복사본으로 계산 (matWorld 자체는 이동 성분 유지)
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    CB_PER_OBJECT_LIT cbData;
    XMStoreFloat4x4(&cbData.mat_World, (matWorld));
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, (matWorldInvTranspos));
    cbData.tMaterial = m_tMaterial;

    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    // 월드 변환을 위한 상수 버퍼
    // Position, Normal 계산을 위해 matWorld, matWorldInvTranspose만 사용
    m_pContext->VSSetConstantBuffers(0, //레지스터 슬롯 번호
        1,
        m_pCB.GetAddressOf());

    // 조명 계산을 위한 상수 버퍼
    // 조명 계산에 필요한 Material만 사용
    m_pContext->PSSetConstantBuffers(0, //레지스터 슬롯 번호
        1,
        m_pCB.GetAddressOf());

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    // 레스터라이즈 설정
    m_pContext->RSSetState(m_pRS.Get());

    // 텍스처 바인드
    if (FAILED(m_pTextureCom->Set_TexturePS(0, 0)))
        return E_FAIL;

    if (FAILED(m_pVS->Begin()))
        return E_FAIL;

    if (FAILED(m_pPS->Begin()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}

HRESULT CSkyBox::Ready_Components()
{
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
