#include "Cube.h"
#include "Hill.h"

CCube::CCube(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject(pDevice,pContext)
{
}

HRESULT CCube::Initialize_Prototype()
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
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // 샘플러 생성
    D3D11_SAMPLER_DESC samplerDesc{};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
        return E_FAIL;

    // Material
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

	return S_OK;
}

HRESULT CCube::Initialize(void* pArg)
{
    if(FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));

    vector_t  vPos = m_pTransformCom->Get_State(STATE::POSITION);
    m_pTransformCom->Set_Scale(2.f,2.f,2.f);
    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.5f);
    m_pTransformCom->Set_State(STATE::POSITION, vPos);
    m_vGroundPlane = pHill->GetPlane(x, z);

    return S_OK;
}

void CCube::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CCube::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CCube::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    if(Is_InFrustum())
        CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));

    // 그림자 : 월드 공간 박스 + 단위 행렬
    BoundingBox tShadowBox;
    m_tLocalBox.Transform(tShadowBox, Get_ShadowWorld());   // 그림자를 감싸는 월드 박스

    if (Is_BoxInFrustum(tShadowBox, XMMatrixIdentity()))
        CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CCube::Render()
{    
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS);
}

HRESULT CCube::Render_Shadow()
{
    return Render_Mesh(Get_ShadowWorld(), m_pRS.Get(), m_pPS_Shadow);
}

HRESULT CCube::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Cube,
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Cube,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXTEX,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX_SHADOW,
        TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
        return E_FAIL;

    return S_OK;
}

HRESULT CCube::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    CB_PER_OBJECT_LIT cbData;
    XMStoreFloat4x4(&cbData.mat_World, (matWorld));
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, (matWorldInvTranspos));
    cbData.tMaterial = m_tMaterial;

    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    // VS의 상수버퍼슬롯(b0)에 상수버퍼(변환 행렬 버퍼) 꽂기
    m_pContext->VSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    m_pContext->PSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(pRS);

    // 텍스처 바인드
    if (FAILED(m_pTextureCom->Set_TexturePS(0, 0)))
        return E_FAIL;

    if(FAILED(m_pVS->Begin()))
        return E_FAIL;

    if(FAILED(pPS->Begin()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}

matrix_t CCube::Get_ShadowWorld()
{
    vector_t    vPlane = XMLoadFloat4(&m_vGroundPlane);
    vector_t    vToLight = vector_t{ -0.5f,0.5f,-0.5f,0.f };

    matrix_t    matShadow = XMMatrixShadow(vPlane, vToLight);
    matShadow = matShadow * (1.f / XMVectorGetW(matShadow.r[3]));
    matrix_t    matOffset = XMMatrixTranslation(0.f, 0.01f, 0.f);

    return m_pTransformCom->Get_World() * matShadow * matOffset;
}

shared_ptr<CCube> CCube::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CCube>(new CCube(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CCube::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CCube>(new CCube(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
