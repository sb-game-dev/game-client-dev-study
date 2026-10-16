#include "SkyBox.h"

CSkyBox::CSkyBox(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CSkyBox::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 정육면체 그리기
    // 정점 정보

    VTXNORM vertices[] =
    {
        // z-
        { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 2.f / 3.f) },
        { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 1.f / 3.f) },
        { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.75f,  1.f / 3.f) },
        { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.75f,  2.f / 3.f) },
        // x+
        { float3_t(+0.5f, -0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.75f,  2.f / 3.f) },
        { float3_t(+0.5f, +0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.75f,  1.f / 3.f) },
        { float3_t(+0.5f, +0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.5f, 1.f / 3.f) },
        { float3_t(+0.5f, -0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.5f, 2.f / 3.f) },
        // z+
        { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.5f, 2.f / 3.f) },
        { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.5f, 1.f / 3.f) },
        { float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.25f,  1.f / 3.f) },
        { float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.25f,  2.f / 3.f) },
        // x-
        { float3_t(-0.5f, -0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.25f,  2.f / 3.f) },
        { float3_t(-0.5f, +0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.25f,  1.f / 3.f) },
        { float3_t(-0.5f, +0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f, 1.f / 3.f) },
        { float3_t(-0.5f, -0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f, 2.f / 3.f) },
        // y+
        { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.25f,  0.f / 3.f) },
        { float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.25f,  1.f / 3.f) },
        { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.5f,   1.f / 3.f) },
        { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.5f,   0.f / 3.f) },
        // y-
        { float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.25f,  2.f / 3.f) },
        { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.25f,  3.f / 3.f) },
        { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.5f,   3.f / 3.f) },
        { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.5f,   2.f / 3.f) },
    };

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

    // Blob은 크기가 정해진 바이트 덩어리를 담는 COM객체
    // 컴파일 결과를 담으면 바이트코드상자(pVSBlob, pPSBlob)
    // 에러메세지를 담으면 문자열 상수가 됨
    // Blob 정보를 이용하여 버텍스 셰이더객체, 픽셀 셰이더 객체를 생성함
    ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    // 셰이더를 디버그 모드에서 컴파일한다. | 컴파일시 최적화를 사용하지 않는다(디버깅에 유용함)
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxTex.hlsl",   // 파일 경로 (작업 디렉터리 기준)
        nullptr,                           // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
        "VS_MAIN",                         // 진입점 함수 이름
        "vs_5_0",                          // 타깃: 버텍스 셰이더, 셰이더 모델 5.0
        iFlags,                            // 컴파일 옵션
        0,                                 // 이 책에서는 사용하지 않는 고급 효과 컴파일 옵션(항상 NULL 또는 0)
        &pVSBlob,                          // 결과: 컴파일된 바이트코드
        &pErrBlob)))                       // 실패 시 에러 메시지
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }
    // PS 컴파일
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_VtxTex.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS_MAIN_SKY", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }
    // 버텍스 셰이더 객체 생성
    if (FAILED(m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS)))
        return E_FAIL;

    // 픽셀 셰이더 객체 생성
    if (FAILED(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS)))
        return E_FAIL;

    // Input Layout 생성 (VS 바이트코드와 대조)
    if (FAILED(m_pDevice->CreateInputLayout(VTXNORM::Elements,               // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
        VTXNORM::iNumElements,           // 배열 원소의 개수
        pVSBlob->GetBufferPointer(),    // 정점셰이더를 컴파일해서 얻은 바이트코드를 가리키는 포인터
        pVSBlob->GetBufferSize(),       // 바이트코드의 크기
        &m_pInputLayout)))              // 생성된 입력 배치를 돌려줄 포인터
        return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_NONE;          // D3D11_CULL_BACK , D3D11_CULL_FRONT,D3D11_CULL_NONE
    rsDesc.FrontCounterClockwise = true;        // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // 텍스처 로드
    //if (FAILED(CreateDDSTextureFromFile(m_pDevice.Get(), L"../../../Resource/Ex/SkyCube.dds", nullptr, m_pSRV.GetAddressOf())))
    //    return E_FAIL;

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
    XMStoreFloat4x4(&cbData.mat_World, XMMatrixTranspose(matWorld));
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, XMMatrixTranspose(matWorldInvTranspos));
    cbData.tMaterial = m_tMaterial;

    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    uint32_t iStride = sizeof(VTXNORM);
    uint32_t iOffset = 0;

    m_pContext->IASetVertexBuffers(0,
        1,
        m_pVB.GetAddressOf(),
        &iStride,
        &iOffset);

    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);

    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

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

    m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0);

    // 텍스처 바인드
    m_pTextureCom->Set_TexturePS(0, 0);

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    m_pContext->RSSetState(m_pRS.Get());

    m_pContext->DrawIndexed(m_iIndexCnt, 0, 0);

    return S_OK;
}

HRESULT CSkyBox::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_SkyBox"),
        TEXT("Com_Texture"), m_pTextureCom)))
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
