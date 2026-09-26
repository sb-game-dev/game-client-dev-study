#include "Cube.h"

CCube::CCube(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject(pDevice,pContext)
{
}

HRESULT CCube::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    // 정육면체 그리기
    // 정점 정보
    VTXCOL vertices[] =
    {
        { float3_t(-0.5f, -0.5f, -0.5f), float4_t(Colors::White)},
        { float3_t(-0.5f, +0.5f, -0.5f), float4_t(Colors::Black)},
        { float3_t(+0.5f, +0.5f, -0.5f), float4_t(Colors::Red)},
        { float3_t(+0.5f, -0.5f, -0.5f), float4_t(Colors::Green)},
        { float3_t(-0.5f, -0.5f, +0.5f), float4_t(Colors::Blue)},
        { float3_t(-0.5f, +0.5f, +0.5f), float4_t(Colors::Yellow)},
        { float3_t(+0.5f, +0.5f, +0.5f), float4_t(Colors::Cyan)},
        { float3_t(+0.5f, -0.5f, +0.5f), float4_t(Colors::Magenta)}
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

         4, 6, 5,
         4, 7, 6,

         4, 5, 1,
         4, 1, 0,

         3, 2, 6,
         3, 6, 7,

         1, 5, 6,
         1, 6, 2,

         4, 0, 3,
         4, 3, 7
    };

    // 인덱스 버퍼 생성
    D3D11_BUFFER_DESC IBDesc{};
    IBDesc.ByteWidth = sizeof(indices);
    IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;


    D3D11_SUBRESOURCE_DATA IBData{};
    IBData.pSysMem = indices;
    if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
        return E_FAIL;

    // 상수 버퍼 생성
    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_TRANSFORM);
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
        L"../Shader/Shader_VtxCol.hlsl",  // 파일 경로 (작업 디렉터리 기준)
        nullptr,                           // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
        nullptr,                           // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
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
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_VtxCol.hlsl", nullptr, nullptr,
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

    // Input Layout 생성 (VS 바이트코드와 대조)
    if (FAILED(m_pDevice->CreateInputLayout(VTXCOL::Elements,               // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
                                            VTXCOL::iNumElements,           // 배열 원소의 개수
                                            pVSBlob->GetBufferPointer(),    // 정점셰이더를 컴파일해서 얻은 바이트코드를 가리키는 포인터
                                            pVSBlob->GetBufferSize(),       // 바이트코드의 크기
                                            &m_pInputLayout)))              // 생성된 입력 배치를 돌려줄 포인터
        return E_FAIL;

    // 레스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());
	return S_OK;
}

void CCube::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    if(m_bPlayer)
        KeyInput(fDeltaTime);
}
void CCube::LateUpdate(f32_t fDeltaTime)
{
    __super::LateUpdate(fDeltaTime);
}

HRESULT CCube::Render()
{    
    // 변환 행렬 계산 -> 상수 버퍼(변환 행렬) 갱신
    //XMMATRIX matWorld = XMMatrixRotationX(m_fRotX) 
    //                    * XMMatrixRotationY(m_fRotY) 
    //                    * XMMatrixRotationZ(m_fRotZ)
    //                    * XMMatrixTranslation(m_vPosition.x, m_vPosition.y, m_vPosition.z);

    XMMATRIX matWorld = GetWorld();

   

    // VS로 전달할 구조체 채우기
    // HLSL은 기본적으로 열 단위로 데이터를 읽기 때문에 전치를 해야 함
    CB_TRANSFORM cbData;
    XMStoreFloat4x4(&cbData.WorldMatrix, XMMatrixTranspose(matWorld));

    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

// 파이프라인에 꽂기
    //IA(입력 조립기 단계)
    // 정점 하나의 크기와 버퍼의 시작 위치 설정
    uint32_t iStride = sizeof(VTXCOL);
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

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());

    // 그리기
    m_pContext->DrawIndexed(36, // IndexCnt: 인덱스 버퍼의 크기
        0,  // StartIndexLocation : 사용할 인덱스의 위치
        0); // BaseVertexLocation : 정점들을 가져오기 전에 이 호출에서 사용할 인덱스에 더해지는 정수값

	return S_OK;
}

void CCube::KeyInput(f32_t fDeltaTime)
{
    if (GetAsyncKeyState('W'))
    {
        MovePos({ 0.f,0.f,1.f }, 1.f, fDeltaTime);
    }
    if (GetAsyncKeyState('S'))
    {
        MovePos({ 0.f,0.f,-1.f }, 1.f, fDeltaTime);
    }
    if (GetAsyncKeyState('A'))
    {
        MovePos({ -1.f,0.f,0.f }, 1.f, fDeltaTime);
    }
    if (GetAsyncKeyState('D'))
    {
        MovePos({ 1.f,0.f,0.f }, 1.f, fDeltaTime);
    }
}
shared_ptr<CCube> CCube::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CCube>(new CCube(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}