#include "Wave.h"
#include "DDSTextureLoader.h"

CWave::CWave(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CWave::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    m_eRenderID = RENDERID::ALPHA;

    uint32_t    ivtxCntX = 129;
    uint32_t    ivtxCntZ = 129;

    uint32_t    ivtxCnt = ivtxCntX * ivtxCntZ;
    uint32_t    iFaceCnt = (ivtxCntX - 1) * (ivtxCntZ - 1) * 2;
    f32_t       fHalfWidth = 0.5f * (ivtxCntX - 1);
    f32_t       fHalfDepth = 0.5f * (ivtxCntZ - 1);

    f32_t   dx = 1.f;//128.f / (ivtxCntX);
    f32_t   dz = 1.f;//128.f / (ivtxCntZ);

    f32_t   du = 1.f / (ivtxCntX - 1);
    f32_t   dv = 1.f / (ivtxCntZ - 1);


    m_tMeshData.Vertices.resize(ivtxCnt);
    m_tMeshData.Indices.resize(iFaceCnt * 3);

    for (uint32_t i = 0; i < ivtxCntZ; ++i)
    {
        float z = fHalfDepth - i * dz;
        for (uint32_t j = 0; j < ivtxCntX; ++j)
        {
            float x = -fHalfWidth + j * dx;
            m_tMeshData.Vertices[i * ivtxCntX + j].vPosition = float3_t(x, 0.f, z);

            m_tMeshData.Vertices[i * ivtxCntX + j].vTangentU = float3_t(1.f, 0.f, 0.f);

            m_tMeshData.Vertices[i * ivtxCntX + j].TexC.x = j * du * 20.f;
            m_tMeshData.Vertices[i * ivtxCntX + j].TexC.y = i * dv * 20.f;
        }
    }

    uint32_t k = 0;
    for (uint32_t i = 0; i < ivtxCntZ - 1; ++i)
    {
        for (uint32_t j = 0; j < ivtxCntX - 1; ++j)
        {
            m_tMeshData.Indices[k] = i * ivtxCntX + j;
            m_tMeshData.Indices[k + 1] = i * ivtxCntX + j + 1;
            m_tMeshData.Indices[k + 2] = (i + 1) * ivtxCntX + j;
            m_tMeshData.Indices[k + 3] = (i + 1) * ivtxCntX + j;
            m_tMeshData.Indices[k + 4] = i * ivtxCntX + j + 1;
            m_tMeshData.Indices[k + 5] = (i + 1) * ivtxCntX + j + 1;

            k += 6;
        }
    }
    m_iIndexCnt = uint32_t(m_tMeshData.Indices.size());

    // Material
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f); 
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 0.5f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    // 버텍스 버퍼를 동적으로 설정하기 위해 Usage, BindFlag, CPUAccessFlag 설정 변경
    D3D11_BUFFER_DESC   VBDesc{};
    VBDesc.ByteWidth = uint32_t(sizeof(VTXNORM) * m_tMeshData.Vertices.size());
    VBDesc.Usage = D3D11_USAGE_DYNAMIC;
    VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
    VBDesc.MiscFlags = 0;    

    if (FAILED(m_pDevice->CreateBuffer(&VBDesc, nullptr, &m_pVB)))
        return E_FAIL;


    D3D11_BUFFER_DESC IBDesc{};
    IBDesc.ByteWidth = sizeof(UINT) * m_iIndexCnt;
    IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;


    D3D11_SUBRESOURCE_DATA IBData{};
    IBData.pSysMem = &m_tMeshData.Indices[0];
    if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
        return E_FAIL;

    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_PER_OBJECT_LIT);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, &m_pCB)))
        return E_FAIL;

    ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

#endif

    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxTex.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS_MAIN",
        "vs_5_0",
        iFlags,
        0,
        &pVSBlob,
        &pErrBlob)))
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }

    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_VtxTex.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS_MAIN", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }

    if (FAILED(m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS)))
        return E_FAIL;

    if (FAILED(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS)))
        return E_FAIL;

    if (FAILED(m_pDevice->CreateInputLayout(VTXNORM::Elements,
                                            VTXNORM::iNumElements,
                                            pVSBlob->GetBufferPointer(),
                                            pVSBlob->GetBufferSize(),
                                            &m_pInputLayout)))
        return E_FAIL;

    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_BACK;
    rsDesc.FrontCounterClockwise = false;
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // 텍스처 로딩 + SRV 설정
    if (FAILED(CreateDDSTextureFromFile(m_pDevice.Get(), L"../../../Resource/Ex/water2.dds", nullptr, m_pSRV.GetAddressOf())))
        return E_FAIL;
    D3D11_SAMPLER_DESC samplerDesc = {};

    // sampler 생성
    samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    samplerDesc.MaxAnisotropy = 16;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
        return E_FAIL;

    // 블렌더 스테이트 생성
    D3D11_BLEND_DESC blendDesc{};
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;

    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    if (FAILED(m_pDevice->CreateBlendState(&blendDesc, m_pBS.GetAddressOf())))
        return E_FAIL;

    return S_OK;
}

HRESULT CWave::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    return S_OK;
}

void CWave::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CWave::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    m_fTime += fDeltaTime;

    D3D11_MAPPED_SUBRESOURCE    mappedData;
    if (FAILED(m_pContext->Map(m_pVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData)))
        return ;

    VTXNORM* v = reinterpret_cast<VTXNORM*>(mappedData.pData);
    for (uint32_t i = 0; i < m_tMeshData.Vertices.size(); ++i)
    {
        float3_t vPos = m_tMeshData.Vertices[i].vPosition;
        vPos.y = GetWaveHeight(vPos.x, vPos.z, m_fTime);

        v[i].vPosition = vPos;
        v[i].vNormal = GetWaveNormal(vPos.x, vPos.z, m_fTime);
        v[i].Tex = float2_t(m_tMeshData.Vertices[i].TexC.x + 0.1f * m_fTime
                          , m_tMeshData.Vertices[i].TexC.y + 0.1f * m_fTime);
    }
    m_pContext->Unmap(m_pVB.Get(), 0);
}
void CWave::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

HRESULT CWave::Render()
{
    XMMATRIX matWorld = GetWorld();

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
    m_pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    m_pContext->RSSetState(m_pRS.Get());

    float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
    m_pContext->OMSetBlendState(m_pBS.Get(), blendFactor, 0xffffffff);     // 블렌딩 ON

    m_pContext->DrawIndexed(m_iIndexCnt, 0, 0);

    m_pContext->OMSetBlendState(nullptr, blendFactor, 0xffffffff);         // 복구

    return S_OK;
}

shared_ptr<CWave> CWave::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CWave>(new CWave(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CWave::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CWave>(new CWave(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
