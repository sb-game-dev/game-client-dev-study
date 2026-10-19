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

    // Blob은 크기가 정해진 바이트 덩어리를 담는 COM객체
    // 컴파일 결과를 담으면 바이트코드상자(pVSBlob, pPSBlob)
    // 에러메세지를 담으면 문자열 상수가 됨
    // Blob 정보를 이용하여 버텍스 셰이더객체, 픽셀 셰이더 객체를 생성함
    ComPtr<ID3DBlob> pVSBlob, pPSBlob, pPSShadowBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    // 셰이더를 디버그 모드에서 컴파일한다. | 컴파일시 최적화를 사용하지 않는다(디버깅에 유용함)
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxTex.hlsl",   // 파일 경로 (작업 디렉터리 기준)
        nullptr,                           // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // hlsl에서 헤더를 사용하는 경우 사용
        "VS_MAIN_INST",                    // 진입점 함수 이름
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
        "PS_MAIN", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }
    // 그림자 PS 컴파일
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_VtxTex.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS_SHADOW", "ps_5_0", iFlags, 0, &pPSShadowBlob, &pErrBlob)))
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

    // 그림자 픽셀 셰이더 객체 생성
    if (FAILED(m_pDevice->CreatePixelShader(pPSShadowBlob->GetBufferPointer(), pPSShadowBlob->GetBufferSize(), nullptr, &m_pPS_Shadow)))
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
    return Render_Mesh(m_pInstanceVB.Get(), m_pPS.Get(),m_iNumInstance);
}

HRESULT CCube_Instance::Render_Shadow()
{
    return Render_Mesh(m_pInstanceVB_Shadow.Get(), m_pPS_Shadow.Get(), m_iVisibleShadowCnt);
}

HRESULT CCube_Instance::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Cube"),
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;
    return S_OK;
}

HRESULT CCube_Instance::Ready_InstanceBuffers()
{
    const vector_t  vToLight = vector_t{ -0.5f, 0.5f, -0.5f, 0.f };
    const matrix_t matOffset = XMMatrixTranslation(0.f, 0.01f, 0.f);

    for (uint32_t i = 0; i < m_iNumInstance; ++i)
    {
        vector_t vPos = vector_t{10 * sinf(XM_2PI / 16 * i), 0.f, 10 * cosf(XM_2PI / 16 * i), 1.f};
        vector_t vPlane = vector_t{ 0.f, 1.f, 0.f, 0.f };
        Compute_OnHill(vPos, vPlane);

        matrix_t matWorld = XMMatrixTranslationFromVector(vPos);    // XMMatrixTranslation에서 매개변수가 벡터로 바뀐 버전
        matrix_t matShadow = matWorld * XMMatrixShadow(vPlane, vToLight) * matOffset;

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

    const auto& vecIndex = pHill->GetIndex();
    const auto& vecVtx = pHill->GetVertices();

    for (uint32_t i = 0; i + 2 < vecIndex.size(); i += 3)
    {
        float3_t p0 = vecVtx[vecIndex[i]].vPosition;
        float3_t p1 = vecVtx[vecIndex[i + 1]].vPosition;
        float3_t p2 = vecVtx[vecIndex[i + 2]].vPosition;

        vector_t vPlane = XMPlaneFromPoints(XMLoadFloat3(&p0), XMLoadFloat3(&p1), XMLoadFloat3(&p2));

        vector_t vRayPos = vPos + vector_t{ 0,100.f,0,0.f };
        vector_t vRayDir = XMVectorSet(0.f, -1.f, 0.f, 0.f);   // 아래 방향

        vector_t v0 = XMLoadFloat3(&p0);
        vector_t v1 = XMLoadFloat3(&p1);
        vector_t v2 = XMLoadFloat3(&p2);

        f32_t fDist = 0.f;
        if (TriangleTests::Intersects(vRayPos, vRayDir, v0, v1, v2, fDist))
        {
            float4_t plane;
            XMStoreFloat4(&plane, vPlane); // x = a, y = b, z = c, w = d -> ax + by + cz + d = 0

            f32_t fY = -(plane.x * XMVectorGetX(vPos) + plane.z * XMVectorGetZ(vPos) + plane.w) / plane.y;

            vPos = XMVectorSetY(vPos, fY + 0.5f);

            vector_t vGround = XMPlaneNormalize(vPlane);
            if (XMVectorGetY(vGround) < 0.f)        // 법선이 아래를 보면 뒤집기
                vGround = XMVectorNegate(vGround);
            vGroundPlane = vGround;
            return true;
        }
    }
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
