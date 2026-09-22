#include "MainApp.h"
#include "Engine_Defines.h"
#include "Client_Defines.h"
#include "Inven.h"

CMainApp::CMainApp()
{

}

CMainApp::~CMainApp()
{
    CGameInstance::Get().Release_Engine();
}

HRESULT CMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비 */
//#ifdef _DEBUG
//
//    if (::AllocConsole() == TRUE)
//    {
//        FILE* nfp[3];
//        freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//        freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//        freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//        std::ios::sync_with_stdio();
//    }
//
//#endif // _DEBUG

    shared_ptr<ITEM> pGun_test = shared_ptr<ITEM>(new GUN);
    pGun_test->strItemName = L"Gun";
    CInven::Get().AddEquipSlot(EQUIP_SLOT::GUN_1, pGun_test);
    pGun_test = nullptr;

    shared_ptr<ITEM> pGun_test2 = shared_ptr<ITEM>(new GUN);
    pGun_test2->strItemName = L"Gun2";
    CInven::Get().AddEquipSlot(EQUIP_SLOT::GUN_2, pGun_test2);
    pGun_test2 = nullptr;

    shared_ptr<ITEM> pBag_test = shared_ptr<ITEM>(new BACKPACK);
    pBag_test->strItemName = L"LV5 BackPack";
    CInven::Get().AddEquipSlot(EQUIP_SLOT::BACKPACK, pBag_test);
    pBag_test = nullptr;

    swap(
        CInven::Get().GetSlot(EQUIP_SLOT::GUN_1),
        CInven::Get().GetSlot(EQUIP_SLOT::GUN_2)
    );

    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iWinSizeX;
    EngineDesc.iWinSizeY = g_iWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;


    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc,m_pDevice,m_pContext)))
        return E_FAIL;

    // 버텍스 버퍼, 인덱스 버퍼, 상수 버퍼(변환 행렬 담는 상자), 버텍스 셰이더, 픽셀 셰이더, InputLayout 생성
    if (FAILED(Ready_Cube()))
        return E_FAIL;


    return S_OK;
}

void CMainApp::Update(f32_t fDeltaTime)
{
    KeyInput(fDeltaTime);
}

HRESULT CMainApp::Render()
{
// Clear
    float4_t    vClearColor = float4_t(1.f, 1.f, 1.f, 1.f);
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

// 변환 행렬 계산 -> 상수 버퍼(m_pCB) 갱신
    XMMATRIX matWorld = XMMatrixRotationX(m_fRotX) * XMMatrixRotationY(m_fRotY * 0.5f) * XMMatrixRotationZ(m_fRotZ * 0.5f);
    XMMATRIX matView = XMMatrixLookAtLH(
        XMVectorSet(0.f, 0.f, -3.f, 1.f),
        XMVectorSet(0.f, 0.f, 0.f, 1.f),
        XMVectorSet(0.f, 1.f, 0.f, 0.f));
    XMMATRIX matProj = XMMatrixPerspectiveFovLH(
        XMConvertToRadians(60.f), (f32_t)g_iWinSizeX / g_iWinSizeY, 0.1f, 100.f);

    // VS로 전달할 구조체 채우기
    // HLSL은 기본적으로 열 단위로 데이터를 읽기 때문에 전치를 해야 함
    CB_TRANSFORM cbData;
    XMStoreFloat4x4(&cbData.WorldMatrix, XMMatrixTranspose(matWorld));
    XMStoreFloat4x4(&cbData.ViewMatrix, XMMatrixTranspose(matView));
    XMStoreFloat4x4(&cbData.ProjMatrix, XMMatrixTranspose(matProj));

    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 CPU가 읽고 쓰기가 가능함)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

// 파이프라인에 꽂기
    // 정점 하나의 크기와 버퍼의 시작 위치 설정
    uint32_t iStride = sizeof(VTXCOL);
    uint32_t iOffset = 0;

    //IA(입력 조립기 단계)
    // 정점의 28바이트중 앞 12바이트는 POSITION, 나머지 16바이트는 COLOR로 읽어라(FVF의 역할)
    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    // 버텍스 버퍼 꽂기
    m_pContext->IASetVertexBuffers(0, 1, m_pVB.GetAddressOf(), &iStride, &iOffset);

    // 인덱스 버퍼 꽂기
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);
    
    // 삼각형 그리기 설정
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // VS(버텍스 셰이더) -> 월드변환, 뷰스페이스 변환, 투영 변환 행렬을 전달받아서 버텍스 버퍼에 계산함
    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

    // VS의 상수버퍼슬롯(b0)에 행렬 버퍼를 꽂기
    m_pContext->VSSetConstantBuffers(0, //register(b0)과 연결됨
                                     1,
                                     m_pCB.GetAddressOf());

    // PS(픽셀 셰이더) -> 지금은 색 밖에 없음
    m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0);

    m_pContext->DrawIndexed(36, 0, 0);

    //CInven::Get().RenderEquipSlot();

    CGameInstance::Get().Present();
    return S_OK;
}

HRESULT CMainApp::Ready_Cube()
{
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
    VBData.pSysMem = vertices;
    if(FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
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

    // 버퍼를 초기화 할 때 사용할 자료는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
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
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxCol.hlsl",  // 파일 경로 (작업 디렉터리 기준)
        nullptr,                           // #define 매크로 목록
        nullptr,                           // #include 처리기
        "VS_MAIN",                         // 진입점 함수 이름
        "vs_5_0",                          // 타깃: 버텍스 셰이더, 셰이더 모델 5.0
        iFlags,                            // 컴파일 옵션
        0,                                 // 이펙트용 옵션 (안 씀)
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
    if (FAILED(m_pDevice->CreateInputLayout(VTXCOL::Elements, VTXCOL::iNumElements,
        pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pInputLayout)))
        return E_FAIL;


    return S_OK;
}

void CMainApp::KeyInput(f32_t fDeltaTime)
{
    if (GetAsyncKeyState('W'))
    {
        m_fRotX += fDeltaTime;
    }

    if (GetAsyncKeyState('S'))
    {
        m_fRotX -= fDeltaTime;
    }
    if (GetAsyncKeyState('A'))
    {
        m_fRotY += fDeltaTime;
    }

    if (GetAsyncKeyState('D'))
    {
        m_fRotY -= fDeltaTime;
    }
    if (GetAsyncKeyState('Q'))
    {
        m_fRotZ += fDeltaTime;
    }

    if (GetAsyncKeyState('E'))
    {
        m_fRotZ -= fDeltaTime;
    }
    
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto    pInstance = unique_ptr<CMainApp>(new CMainApp());
    
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();  // 유저가 임의로 삭제 + nullptr로 채워줌. 나중에 삭제하지 않고 즉시 삭제
    
    return pInstance;
}
