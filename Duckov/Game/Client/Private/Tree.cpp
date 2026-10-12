#include "Tree.h"
#include "DDSTextureLoader.h"
#include "Hill.h"

CTree::CTree(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CTree::Initialize_Prototype()
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

    // Blob은 크기가 정해진 바이트 덩어리를 담는 COM객체
    // 컴파일 결과를 담으면 바이트코드상자(pVSBlob, pPSBlob)
    // 에러메세지를 담으면 문자열 상수가 됨
    // Blob 정보를 이용하여 버텍스 셰이더객체, 픽셀 셰이더 객체를 생성함
    ComPtr<ID3DBlob> pVSBlob, pPSBlob, pGSBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    // 셰이더를 디버그 모드에서 컴파일한다. | 컴파일시 최적화를 사용하지 않는다(디버깅에 유용함)
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_TreeSprite.hlsl",   // 파일 경로 (작업 디렉터리 기준)
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
    // GS 컴파일
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_TreeSprite.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "GS_MAIN", "gs_5_0", iFlags, 0, &pGSBlob, &pErrBlob)))
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }
    // PS 컴파일
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_TreeSprite.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS_MAIN", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
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

    // 기하 셰이더 객체 생성
    if (FAILED(m_pDevice->CreateGeometryShader(pGSBlob->GetBufferPointer(), pGSBlob->GetBufferSize(), nullptr, &m_pGS)))
        return E_FAIL;

    // Input Layout 생성 (VS 바이트코드와 대조)
    if (FAILED(m_pDevice->CreateInputLayout(TREEPOINTSPRITE::Elements,      // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
                                            TREEPOINTSPRITE::iNumElements,  // 배열 원소의 개수
                                            pVSBlob->GetBufferPointer(),    // 정점셰이더를 컴파일해서 얻은 바이트코드를 가리키는 포인터
                                            pVSBlob->GetBufferSize(),       // 바이트코드의 크기
                                            &m_pInputLayout)))              // 생성된 입력 배치를 돌려줄 포인터
                                            return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_NONE;          // D3D11_CULL_BACK , D3D11_CULL_FRONT,D3D11_CULL_NONE
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // 텍스처 로드
    if (FAILED(CreateDDSTextureFromFile(m_pDevice.Get(), L"../../../Resource/Ex/tree0.dds", nullptr, m_pSRV.GetAddressOf())))
        return E_FAIL;

    // 샘플러 생성
    D3D11_SAMPLER_DESC samplerDesc{};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
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

HRESULT CTree::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    TREEPOINTSPRITE v[m_iTreeCnt] = {};
    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));
    for (UINT i = 0; i < m_iTreeCnt; ++i)
    {
        float x = f32_t(rand() % 41 - 20.f);
        float z = f32_t(rand() % 41 - 20.f);

        float y = pHill->GetHeight(x, z);

        y += 5.0f;

        v[i].vPos = XMFLOAT3(x, y, z);
        v[i].Size = XMFLOAT2(16.0f, 16.0f);
    }

    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(TREEPOINTSPRITE) * m_iTreeCnt;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = v;
    if (FAILED(m_pDevice->CreateBuffer(&vbd, &vinitData, &m_pVB)))
        return E_FAIL;
    return S_OK;
}

void CTree::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CTree::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CTree::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CTree::Render()
{
    return Render_Mesh(GetWorld(), m_pRS.Get(), m_pPS.Get());
}

HRESULT CTree::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, ID3D11PixelShader* pPS)
{
    CB_PER_OBJECT_LIT cbData;
    cbData.tMaterial = m_tMaterial;

    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    uint32_t iStride = sizeof(TREEPOINTSPRITE);
    uint32_t iOffset = 0;
    // 버텍스 버퍼 꽂기
    m_pContext->IASetVertexBuffers(0,                       // 정점 버퍼들을 붙이기 시작할 인덱스
                                   1,                       // 입력 슬롯에 붙이고자 하는 버퍼의 개수
                                   m_pVB.GetAddressOf(),    // 버퍼를 담은 배열의 첫 원소를 가리키는 포인터
                                   &iStride,                // 버퍼의 한 원소의 바이트크기 단위(주소를 넘겨줘야함)
                                   &iOffset);               // 정점 버퍼의 시작위치에서부터 건너뛸 인덱스
    // 삼각형 그리기 설정
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

    // InputLayoyt 꽂기(FVF의 역할)
    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    // VS(버텍스 셰이더 단계) -> 월드변환, 뷰스페이스 변환, 투영 변환 행렬을 전달받아서 버텍스 버퍼에 계산함
    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

    // VS의 상수버퍼슬롯(b0)에 상수버퍼(변환 행렬 버퍼) 꽂기
    m_pContext->VSSetConstantBuffers(0, //register(b0)과 연결됨
                                     1,
                                     m_pCB.GetAddressOf());

    // GS 할당
    m_pContext->GSSetShader(m_pGS.Get(), nullptr, 0);


    // PS(픽셀 셰이더) -> 지금은 색 밖에 없음
    m_pContext->PSSetShader(pPS, nullptr, 0);

    m_pContext->PSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // 텍스처 바인드
    m_pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(pRS);

    // 그리기
    m_pContext->Draw(m_iTreeCnt, 0); 

    // GS 해제
    m_pContext->GSSetShader(nullptr, nullptr, 0);
    return S_OK;
}

shared_ptr<CTree> CTree::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CTree>(new CTree(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CTree::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CTree>(new CTree(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
