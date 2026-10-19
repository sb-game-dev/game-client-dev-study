#include "Mirror.h"

CMirror::CMirror(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CMirror::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 상수 버퍼 생성
    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_PER_OBJECT);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, m_pCB.GetAddressOf())))
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
    if (FAILED(D3DCompileFromFile( L"../Shader/Shader_VtxTex.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, 
        "VS_MAIN", "vs_5_0", iFlags, 0, &pVSBlob, &pErrBlob)))                      
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

    // 레스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // sampler 생성
    D3D11_SAMPLER_DESC samplerDesc = {};

    samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    samplerDesc.MaxAnisotropy = 16;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
        return E_FAIL;

    // Material
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 0.5f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    return S_OK;
}

HRESULT CMirror::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    m_pTransformCom->Set_State(STATE::POSITION, vector_t{ 0.f,2.f,5.f,1.f });
    m_pTransformCom->Set_Scale(6.f, 4.f, 1.f);

    if (FAILED(Ready_Components()))
        return E_FAIL;

    return S_OK;
}

void CMirror::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CMirror::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CMirror::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CMirror::Render()
{
    XMMATRIX matWorld = m_pTransformCom->Get_World();

    // VS로 전달할 구조체 채우기
    // HLSL은 기본적으로 열 단위로 데이터를 읽기 때문에 전치를 해야 함
    CB_PER_OBJECT cbData;
    XMStoreFloat4x4(&cbData.WorldMatrix, XMMatrixTranspose(matWorld));

    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    m_pBufferCom->Bind_Resources();
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

    m_pTextureCom->Set_TexturePS(0, 0);

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());

    // 그리기
    m_pBufferCom->Render();

    return S_OK;
}

XMVECTOR CMirror::Get_MirrorPlane()
{
    vector_t vPos = m_pTransformCom->Get_State(STATE::POSITION);

    return XMPlaneFromPointNormal(vPos,XMVectorSet(0.f,0.f,-1.f,0.f));
}

HRESULT CMirror::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Mirror"),
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Rect"),
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CMirror> CMirror::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CMirror>(new CMirror(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CMirror");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CMirror::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CMirror>(new CMirror(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CMirror");
        pInstance.reset();
    }
    return pInstance;
}
