#include "BackGround.h"
#include "DDSTextureLoader.h"

CBackGround::CBackGround(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{pDevice,pContext}
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
    VTXNORM vertices[] =
    {
        { float3_t(-0.5f, -0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 1.f) },
        { float3_t(-0.5f, +0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 0.f) },
        { float3_t(+0.5f, +0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 0.f) },
        { float3_t(+0.5f, -0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 1.f) },
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
    // 인덱스 정보
    UINT indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

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
        "PS_MAIN_NOLIGHT", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
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
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // 텍스처 로드
    if (FAILED(CreateDDSTextureFromFile(m_pDevice.Get(), L"../../../Resource/Logo/Logo_Background_1280x720.dds", nullptr, m_pSRV.GetAddressOf())))
        return E_FAIL;

    // 샘플러 생성
    D3D11_SAMPLER_DESC samplerDesc{};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
        return E_FAIL;

    // Material
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    SetPos(float3_t(0.f, 0.f, 1.f));
    m_vScale = { g_iWinSizeX,g_iWinSizeY,1.f };
	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
    return S_OK;
}

void CBackGround::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CBackGround::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);
}

void CBackGround::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta);
}
HRESULT CBackGround::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
    XMMATRIX matWorld = GetWorld();

    // 역전치 행렬은 이동 성분을 뺀 복사본으로 계산 (matWorld 자체는 이동 성분 유지)
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    CB_PER_OBJECT_LIT cbData;
    XMStoreFloat4x4(&cbData.mat_World, XMMatrixTranspose(matWorld));
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, XMMatrixTranspose(matWorldInvTranspos));
    cbData.tMaterial = m_tMaterial;

    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    // 파이프라인에 꽂기
        //IA(입력 조립기 단계)
        // 정점 하나의 크기와 버퍼의 시작 위치 설정
    uint32_t iStride = sizeof(VTXNORM);
    uint32_t iOffset = 0;
    // 버텍스 버퍼 꽂기
    m_pContext->IASetVertexBuffers(0,                       // 정점 버퍼들을 붙이기 시작할 인덱스
        1,                       // 입력 슬롯에 붙이고자 하는 버퍼의 개수
        m_pVB.GetAddressOf(),    // 버퍼를 담은 배열의 첫 원소를 가리키는 포인터
        &iStride,                // 버퍼의 한 원소의 바이트크기 단위(주소를 넘겨줘야함)
        &iOffset);               // 정점 버퍼의 시작위치에서부터 건너뛸 인덱스

    // 인덱스 버퍼 꽂기
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 삼각형 그리기 설정
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // InputLayoyt 꽂기(FVF의 역할)
    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    // VS(버텍스 셰이더 단계) -> 월드변환, 뷰스페이스 변환, 투영 변환 행렬을 전달받아서 버텍스 버퍼에 계산함
    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

    // VS의 상수버퍼슬롯(b0)에 상수버퍼(변환 행렬 버퍼) 꽂기
    m_pContext->VSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // PS(픽셀 셰이더) -> 지금은 색 밖에 없음
    m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0);

    m_pContext->PSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // 텍스처 바인드
    m_pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());


    // 그리기
    m_pContext->DrawIndexed(m_iIndexCnt, // IndexCnt: 인덱스 버퍼의 크기
        0,  // StartIndexLocation : 사용할 인덱스의 위치
        0); // BaseVERTEXLocation : 정점들을 가져오기 전에 이 호출에서 사용할 인덱스에 더해지는 정수값

    return S_OK;
}
shared_ptr<CBackGround> CBackGround::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CBackGround>(new CBackGround(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Create Failed : CBackGround");
		pInstance.reset();
	}

	return pInstance;
}

shared_ptr<CPrototype> CBackGround::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CBackGround>(new CBackGround(*this));
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : CBackGround");
		pInstance.reset();
	}
	return pInstance;
}