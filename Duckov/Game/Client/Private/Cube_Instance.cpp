#include "Cube_Instance.h"
#include "Hill.h"

CCube_Instance::CCube_Instance(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CCube_Instance::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 정육면체 그리기
    // 정점 정보
    VTXNORM vertices[] =
    {
        // z-
        { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 1.f) },
        { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 0.f) },
        { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 0.f) },
        { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 1.f) },
        // x+
        { float3_t(+0.5f, -0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.f, 1.f) },
        { float3_t(+0.5f, +0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.f, 0.f) },
        { float3_t(+0.5f, +0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(1.f, 0.f) },
        { float3_t(+0.5f, -0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(1.f, 1.f) },
        // z+
        { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.f, 1.f) },
        { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.f, 0.f) },
        { float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(1.f, 0.f) },
        { float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(1.f, 1.f) },
        // x-
        { float3_t(-0.5f, -0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f, 1.f) },
        { float3_t(-0.5f, +0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f, 0.f) },
        { float3_t(-0.5f, +0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(1.f, 0.f) },
        { float3_t(-0.5f, -0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(1.f, 1.f) },
        // y+
        { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.f, 1.f) },
        { float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.f, 0.f) },
        { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(1.f, 0.f) },
        { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(1.f, 1.f) },
        // y-
        { float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.f, 1.f) },
        { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.f, 0.f) },
        { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(1.f, 0.f) },
        { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(1.f, 1.f) },

    };
    
    BoundingBox::CreateFromPoints(m_tLocalBox, size(vertices), &vertices[0].vPosition, sizeof(VTXNORM));

    // 정점 버퍼 생성
    D3D11_BUFFER_DESC   VBDesc{};
    VBDesc.ByteWidth = sizeof(vertices);
    VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  VBData{};
    VBData.pSysMem = vertices;  // 정점 버퍼를 초기화할 자료를 담은 시스템 메모리 배열을 가리키는 포인터
    if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
        return E_FAIL;

    UINT indices[36] = {};
    uint32_t iVtx = 0;
    for (uint32_t i = 0; i < 36; i += 6)
    {
        indices[i] = iVtx;
        indices[i + 1] = iVtx + 1;
        indices[i + 2] = iVtx + 2;

        indices[i + 3] = iVtx;
        indices[i + 4] = iVtx + 2;
        indices[i + 5] = iVtx + 3;

        iVtx += 4;
    }

    // 인덱스 버퍼 생성
    D3D11_BUFFER_DESC IBDesc{};
    IBDesc.ByteWidth = sizeof(indices);
    IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;


    D3D11_SUBRESOURCE_DATA IBData{};
    IBData.pSysMem = indices;
    m_iIndexCnt = size(indices);
    if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
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

HRESULT CCube_Instance::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_InstanceBuffers()))
        return E_FAIL;
    

    return S_OK;
}

void CCube_Instance::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CCube_Instance::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CCube_Instance::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    Cull_Instances();

    if(m_iVisibleCnt > 0)
        CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    if(m_iVisibleShadowCnt > 0)
        CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CCube_Instance::Render()
{
    return Render_Mesh(m_pInstanceVB.Get(), m_pPS->Get_Shader().Get(), m_iNumInstance);
}

HRESULT CCube_Instance::Render_Shadow()
{
    return Render_Mesh(m_pInstanceVB_Shadow.Get(), m_pPS_Shadow->Get_Shader().Get(), m_iVisibleShadowCnt);
}

HRESULT CCube_Instance::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Cube"),
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VS_VTXTEX_INSTANCE"),
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_VTXTEX"),
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_VTXTEX_SHADOW"),
        TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
        return E_FAIL;
    return S_OK;
}

HRESULT CCube_Instance::Ready_InstanceBuffers()
{
    const vector_t  vToLight = vector_t{ -0.5f, 0.5f, -0.5f, 0.f };
    const matrix_t matOffset = XMMatrixTranslation(0.f, 0.01f, 0.0f);

    for (uint32_t i = 0; i < m_iNumInstance; ++i)
    {
        vector_t vPos = vector_t{ 38.2f + 5 * sinf(XM_2PI / 16 * i), 0.f, -207.2f + 5 * cosf(XM_2PI / 16 * i), 1.f};
        vector_t vPlane = vector_t{ 0.f, 1.f, 0.f, 0.f };
        Compute_OnHill(vPos, vPlane);

        matrix_t matWorld = XMMatrixTranslationFromVector(vPos);    // XMMatrixTranslation에서 매개변수가 벡터로 바뀐 버전
        matrix_t matShadow = matWorld * XMMatrixShadow(vPlane, vToLight);

        matShadow = matShadow * (1.f / XMVectorGetW(matShadow.r[3]));
        matShadow = matShadow * matOffset;
        
        XMStoreFloat4x4(&m_WorldMats[i], matWorld);                 
        XMStoreFloat4x4(&m_ShadowMats[i], matShadow);

        m_tLocalBox.Transform(m_ShadowBoxes[i], matShadow);   // 납작해진 그림자를 감싸는 월드 박스
    }

    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(float4x4_t) * m_iNumInstance;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB)))
        return E_FAIL;

    if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB_Shadow)))
        return E_FAIL;

    return S_OK;
}

bool CCube_Instance::Compute_OnHill(vector_t& vPos, vector_t& vGroundPlane)
{
    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));

    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.5f);

    float4_t tempPlane = pHill->GetPlane(x, z);
    vGroundPlane = XMLoadFloat4(&tempPlane);

    return true;
}

void CCube_Instance::Cull_Instances()
{
    const matrix_t  matIdentity = XMMatrixIdentity();
    // 큐브 컬링
    D3D11_MAPPED_SUBRESOURCE tMapped{};

    if (FAILED(m_pContext->Map(m_pInstanceVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
        return;

    auto pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
    m_iVisibleCnt = 0;
    for (uint32_t i = 0; i < m_iNumInstance; ++i)
    {
        if (Is_BoxInFrustum(m_tLocalBox, XMLoadFloat4x4(&m_WorldMats[i])))
            pDst[m_iVisibleCnt++] = m_WorldMats[i];
    }
    m_pContext->Unmap(m_pInstanceVB.Get(), 0);

    // 그림자 컬링
    if (FAILED(m_pContext->Map(m_pInstanceVB_Shadow.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
        return;
    pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
    m_iVisibleShadowCnt = 0;

    for (uint32_t i = 0; i < m_iNumInstance; ++i)
    {
        // 그림자는 로컬스페이스가 없음. 따라서 절두체를 월드까지만 내려야 함.
        // 따라서 월드 -> 로컬로 이동하기 위한 월드^-1 를 만들때 사용할 월드 행렬 매개변수로 항등행렬을 보낸다.
        if (Is_BoxInFrustum(m_ShadowBoxes[i], matIdentity)) 
            pDst[m_iVisibleShadowCnt++] = m_ShadowMats[i];
    }
    m_pContext->Unmap(m_pInstanceVB_Shadow.Get(), 0);
}

HRESULT CCube_Instance::Render_Mesh(ID3D11Buffer* pInstanceVB, ID3D11PixelShader* pPS, uint32_t iInstanceCnt)
{
    CB_PER_OBJECT_LIT cbData;
    XMStoreFloat4x4(&cbData.mat_World, XMMatrixIdentity());
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, XMMatrixIdentity());
    cbData.tMaterial = m_tMaterial;

    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    // 파이프라인에 꽂기
        //IA(입력 조립기 단계)
        // 정점 하나의 크기와 버퍼의 시작 위치 설정
    ID3D11Buffer* pVBs[] = { m_pVB.Get(),pInstanceVB };
    uint32_t iStride[] = { sizeof(VTXNORM),sizeof(float4x4_t) };
    uint32_t iOffset[] = { 0,0 };
    // 버텍스 버퍼 꽂기
    m_pContext->IASetVertexBuffers(0,2, pVBs, iStride, iOffset);                

    // 인덱스 버퍼 꽂기
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 삼각형 그리기 설정
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // InputLayout 꽂기(FVF의 역할)
    m_pContext->IASetInputLayout(m_pVS->Get_InputLayout().Get());

    // VS(버텍스 셰이더 단계) -> 월드변환, 뷰스페이스 변환, 투영 변환 행렬을 전달받아서 버텍스 버퍼에 계산함
    m_pContext->VSSetShader(m_pVS->Get_Shader().Get(), nullptr, 0);

    // VS의 상수버퍼슬롯(b0)에 상수버퍼(변환 행렬 버퍼) 꽂기

    m_pContext->VSSetConstantBuffers(0, 1, m_pCB.GetAddressOf());

    // PS(픽셀 셰이더) -> 지금은 색 밖에 없음
    m_pContext->PSSetShader(pPS, nullptr, 0);

    m_pContext->PSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // 텍스처 바인드
    m_pTextureCom->Set_TexturePS(0, 0);

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());

    // 그리기(DrawIndexedInstanced -> 정점 36개당 인스턴스 1개 적용)
    // for(m_iNumInstance)
    //      for(m_iIndexCnt)
    //
    m_pContext->DrawIndexedInstanced(m_iIndexCnt,       // IndexCnt: 인덱스 버퍼의 크기
                                     iInstanceCnt,    // 인스턴스 개수(월드 행렬의 개수) 
                                     0, 0, 0);

    return S_OK;
}

shared_ptr<CCube_Instance> CCube_Instance::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CCube_Instance>(new CCube_Instance(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CCube_Instance::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CCube_Instance>(new CCube_Instance(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
