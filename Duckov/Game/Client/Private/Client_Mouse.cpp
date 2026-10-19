#include "Client_Mouse.h"
const f32_t g_SizeX = 24.f;
const f32_t g_SizeY = 15.f;
const f32_t g_RotZ[4] = { 0.f,90.f,180.f,270.f };

CClient_Mouse::CClient_Mouse(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMouse{ pDevice,pContext }
{
}

HRESULT CClient_Mouse::Initialize_Prototype()
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
    VBData.pSysMem = vertices;  
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
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxTex.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, 
        "VS_MAIN_INST", "vs_5_0", iFlags, 0, &pVSBlob, &pErrBlob)))                       
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
    if (FAILED(m_pDevice->CreateInputLayout(VTXNORM_INSTANCE::Elements,               // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
        VTXNORM_INSTANCE::iNumElements,           // 배열 원소의 개수
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

    // 샘플러 생성
    D3D11_SAMPLER_DESC samplerDesc{};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
        return E_FAIL;
    return S_OK;
}

HRESULT CClient_Mouse::Initialize(void* pArg)
{
    CClient_Mouse::CLIENT_MOUSE_DESC MouseDesc{};
    if (FAILED(__super::Initialize(&MouseDesc)))
        return E_FAIL;


    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_InstanceBuffers()))
        return E_FAIL;

    return S_OK;
}

void CClient_Mouse::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CClient_Mouse::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
    POINT		pt{};

    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);

    m_vPosVP = { (f32_t)pt.x,(f32_t)pt.y,1.f };

    vector_t vRayOrigin = {};
    vector_t vRayDir = {};

    CGameInstance::Get().Get_MainCamera()->Compute_PickingRay(pt, vRayOrigin, vRayDir);

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Player");
    if (nullptr == pPlayer)
        return;

    float3_t    vPlayerPos = {};
    float3_t    vecOrigin = {};
    float3_t    vecRayDir = {};
    XMStoreFloat3(&vPlayerPos, pPlayer->Get_Transform()->Get_State(STATE::POSITION));
    XMStoreFloat3(&vecOrigin, vRayOrigin);
    XMStoreFloat3(&vecRayDir, vRayDir);

    // 직선의 방정식 => (x - x`)/a = (y - y`)/b = (z - z`)/c

    f32_t x = (vPlayerPos.y - vecOrigin.y) / vecRayDir.y * vecRayDir.x + vecOrigin.x;
    f32_t z = (vPlayerPos.y - vecOrigin.y) / vecRayDir.y * vecRayDir.z + vecOrigin.z;
    m_pTransformCom->Set_State(STATE::POSITION,{ x, vPlayerPos.y, z, 1.f });

    // 
    if (GetAsyncKeyState(VK_LBUTTON) && m_fRange <= 50.f)
        m_fRange += 10.f;

    if (m_fRange > 26.f)
        m_fRange -= 100 * fTimeDelta;
}

void CClient_Mouse::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CClient_Mouse::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    //const f32_t fSizeX = 20.f;
    //const f32_t fSizeY = 12.f;
    //matrix_t matScale = XMMatrixScaling(fSizeX, fSizeY, 1.f);
    //matrix_t matTrans = XMMatrixTranslation(m_vPosVP.x - g_iWinSizeX * 0.5f, 
    //                                        -m_vPosVP.y + g_iWinSizeY * 0.5f, 
    //                                        m_vPosVP.z);
    //matrix_t matWorldVP = matScale * matTrans;

    D3D11_MAPPED_SUBRESOURCE tMapped{};

    if (FAILED(m_pContext->Map(m_pInstanceVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
        return E_FAIL;
    float3_t vOffsetPos[4] = { {0.f,m_fRange,0.f},{-m_fRange,0.f,0.f} ,{0.f,-m_fRange,0.f} ,{m_fRange,0.f,0.f} };

    auto pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
    for (uint32_t i = 0; i < m_iNumInstance; ++i)
    {
        matrix_t matScale = XMMatrixScaling(g_SizeX, g_SizeY, 1.f);
        matrix_t matRotZ  = XMMatrixRotationZ(XMConvertToRadians(g_RotZ[i]));
        matrix_t matTrans = XMMatrixTranslation(+ m_vPosVP.x - g_iWinSizeX * 0.5f + vOffsetPos[i].x,
                                                - m_vPosVP.y + g_iWinSizeY * 0.5f + vOffsetPos[i].y, 
                                                m_vPosVP.z);
        pDst[i] = m_WorldMats[i];
        XMStoreFloat4x4(&pDst[i], matScale * matRotZ * matTrans);
    }
    m_pContext->Unmap(m_pInstanceVB.Get(), 0);

    return Render_Mesh(m_pInstanceVB.Get(), m_pPS.Get(), m_iNumInstance);
}

HRESULT CClient_Mouse::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS)
{
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
    //m_pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());
    m_pTextureCom->Set_TexturePS(0, 0);

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
HRESULT CClient_Mouse::Ready_Components()
{
    //StaticLevel로 변경해야 할 듯
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Mouse"),
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;
    return S_OK;
}
HRESULT CClient_Mouse::Ready_InstanceBuffers()
{
    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(float4x4_t) * m_iNumInstance;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB)))
        return E_FAIL;
}
HRESULT CClient_Mouse::Render_Mesh(ID3D11Buffer* pInstanceVB, ID3D11PixelShader* pPS, uint32_t iInstanceCnt)
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
    m_pContext->IASetVertexBuffers(0, 2, pVBs, iStride, iOffset);

    // 인덱스 버퍼 꽂기
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 삼각형 그리기 설정
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // InputLayout 꽂기(FVF의 역할)
    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    // VS(버텍스 셰이더 단계) -> 월드변환, 뷰스페이스 변환, 투영 변환 행렬을 전달받아서 버텍스 버퍼에 계산함
    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

    // VS의 상수버퍼슬롯(b0)에 상수버퍼(변환 행렬 버퍼) 꽂기

    m_pContext->VSSetConstantBuffers(0, 1, m_pCB.GetAddressOf());

    // PS(픽셀 셰이더) -> 지금은 색 밖에 없음
    m_pContext->PSSetShader(pPS, nullptr, 0);

    m_pContext->PSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // 텍스처 바인드
    m_pTextureCom->Set_TexturePS(3, 0);

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
shared_ptr<CClient_Mouse> CClient_Mouse::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CClient_Mouse>(new CClient_Mouse(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CClient_Mouse");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CClient_Mouse::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CClient_Mouse>(new CClient_Mouse(*this));
    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CClient_Mouse");
        pInstance.reset();
    }
    return pInstance;
}