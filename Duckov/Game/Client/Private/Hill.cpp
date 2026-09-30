#include "Hill.h"

CHill::CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CHill::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    uint32_t    ivtxCntX = 129;
    uint32_t    ivtxCntZ = 129;

    uint32_t    ivtxCnt = ivtxCntX * ivtxCntZ;
    uint32_t    iFaceCnt = (ivtxCntX - 1) * (ivtxCntZ - 1) * 2;
    f32_t       fHalfWidth = 0.5f * (ivtxCntX -1);
    f32_t       fHalfDepth = 0.5f * (ivtxCntZ -1);

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
            
            m_tMeshData.Vertices[i * ivtxCntX + j].vNormal = GetNormal(x, z);
            m_tMeshData.Vertices[i * ivtxCntX + j].vTangentU = float3_t(1.f, 0.f, 0.f);

            m_tMeshData.Vertices[i * ivtxCntX + j].TexC.x = j*du;
            m_tMeshData.Vertices[i * ivtxCntX + j].TexC.y = i*dv;
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
    m_iIndexCnt = m_tMeshData.Indices.size();
    vector<VTXNORM> vertices(m_tMeshData.Vertices.size());
    for (size_t i = 0; i < m_tMeshData.Vertices.size(); ++i)
    {
        float3_t& p = m_tMeshData.Vertices[i].vPosition;
        p.y = GetHeight(p.x, p.z);
        vertices[i].vPosition = p;
        vertices[i].vNormal = m_tMeshData.Vertices[i].vNormal;
        //if (p.y < -10.0f)
        //    vertices[i].vColor = XMFLOAT4(1.0f, 0.96f, 0.62f, 1.0f);
        //else if (p.y < 5.0f)
        //    vertices[i].vColor = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
        //else if (p.y < 12.0f)
        //    vertices[i].vColor = XMFLOAT4(0.1f, 0.48f, 0.19f, 1.0f);
        //else if (p.y < 20.0f)
        //    vertices[i].vColor = XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
        //else
        //    vertices[i].vColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    // Material
    m_tMaterial.Ambient = float4_t(0.48f, 0.77f, 0.46f, 1.f);
    m_tMaterial.Diffuse = float4_t(0.48f, 0.77f, 0.46f, 1.f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    D3D11_BUFFER_DESC   VBDesc{}; 
    VBDesc.ByteWidth = sizeof(VTXNORM) * m_tMeshData.Vertices.size();
    VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  VBData{};
    VBData.pSysMem = &vertices[0];  
    if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
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
        L"../Shader/Shader_VtxNorm.hlsl",  
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
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_VtxNorm.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
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


    return S_OK;
}

HRESULT CHill::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    return S_OK;
}

void CHill::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CHill::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CHill::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

HRESULT CHill::Render()
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

    m_pContext->RSSetState(m_pRS.Get());

    m_pContext->DrawIndexed(m_iIndexCnt, 
        0,                      
        0);                     

    return S_OK;
}

float3_t CHill::GetNormal(f32_t x, f32_t z)
{
    //0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z));
    f32_t fDfDx = 0.03f * z * cosf(0.1f * x) + 0.3f * cosf(0.1f * z);
    f32_t fDfDz = 0.3f * sinf(0.1f * x) - 0.03f * x * sinf(0.1f * z);
    float3_t vNormal = { -fDfDx,1.f,-fDfDz };
    XMStoreFloat3(&vNormal, XMVector3Normalize(XMLoadFloat3(&vNormal)));
    return vNormal;
}

shared_ptr<CHill> CHill::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CHill>(new CHill(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CHill::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CHill>(new CHill(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
