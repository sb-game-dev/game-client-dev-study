#include "Hill.h"
#include <fstream>

CHill::CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CHill::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    LoadHeightMap(L"../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw");

    uint32_t    ivtxCnt = m_ivtxCntX * m_ivtxCntZ;
    uint32_t    iFaceCnt = (m_ivtxCntX - 1) * (m_ivtxCntZ - 1) * 2;
    m_fHalfWidth = 0.5f * (m_ivtxCntX - 1) * m_fDx;
    m_fHalfDepth = 0.5f * (m_ivtxCntZ - 1) * m_fDz;

    f32_t   du = 1.f / (m_ivtxCntX - 1);
    f32_t   dv = 1.f / (m_ivtxCntZ - 1);

    
    m_tMeshData.Vertices.resize(ivtxCnt);
    m_tMeshData.Indices.resize(iFaceCnt * 3);

    for (uint32_t i = 0; i < m_ivtxCntZ; ++i)
    {
        float z = m_fHalfDepth - i * m_fDz;
        for (uint32_t j = 0; j < m_ivtxCntX; ++j)
        {
            float x = -m_fHalfWidth + j * m_fDx;
            m_tMeshData.Vertices[i * m_ivtxCntX + j].vPosition = float3_t(x, 0.f, z);
            
            m_tMeshData.Vertices[i * m_ivtxCntX + j].vNormal = GetNormal(i, j);
            m_tMeshData.Vertices[i * m_ivtxCntX + j].vTangentU = float3_t(1.f, 0.f, 0.f);

            m_tMeshData.Vertices[i * m_ivtxCntX + j].TexC.x = j*du;
            m_tMeshData.Vertices[i * m_ivtxCntX + j].TexC.y = i*dv;
        }
    }

    uint32_t k = 0;
    for (uint32_t i = 0; i < m_ivtxCntZ - 1; ++i)
    {
        for (uint32_t j = 0; j < m_ivtxCntX - 1; ++j)
        {
            m_tMeshData.Indices[k] = i * m_ivtxCntX + j;
            m_tMeshData.Indices[k + 1] = i * m_ivtxCntX + j + 1;
            m_tMeshData.Indices[k + 2] = (i + 1) * m_ivtxCntX + j;
            m_tMeshData.Indices[k + 3] = (i + 1) * m_ivtxCntX + j;
            m_tMeshData.Indices[k + 4] = i * m_ivtxCntX + j + 1;
            m_tMeshData.Indices[k + 5] = (i + 1) * m_ivtxCntX + j + 1;

            k += 6;
        }
    }
    m_iIndexCnt = uint32_t(m_tMeshData.Indices.size());
    vector<VTXNORM> vertices(m_tMeshData.Vertices.size());
    for (size_t i = 0; i < m_tMeshData.Vertices.size(); ++i)
    {
        float3_t& p = m_tMeshData.Vertices[i].vPosition;
        p.y = m_vHeightmap[i]; //GetHeight(p.x, p.z);
        vertices[i].vPosition = p;
        vertices[i].vNormal = m_tMeshData.Vertices[i].vNormal;
        vertices[i].Tex = m_tMeshData.Vertices[i].TexC;
        
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
    m_tMaterial.Ambient = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨

    D3D11_BUFFER_DESC   VBDesc{}; 
    VBDesc.ByteWidth = uint32_t(sizeof(VTXNORM) * m_tMeshData.Vertices.size());
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

    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         
    rsDesc.CullMode = D3D11_CULL_BACK;          
    rsDesc.FrontCounterClockwise = false;       
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

    return S_OK;
}

HRESULT CHill::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
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
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CHill::Render()
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

    m_pContext->IASetInputLayout(m_pVS->Get_InputLayout().Get());

    m_pContext->VSSetShader(m_pVS->Get_Shader().Get(), nullptr, 0);

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

    m_pContext->PSSetShader(m_pPS->Get_Shader().Get(), nullptr, 0);

    // 텍스처 바인드
    m_pLayerCom->Set_TexturePS(0, 2);    // Layer0 잔디     → t2
    m_pLayerCom->Set_TexturePS(1, 3);    // Layer1 흙       → t3
    m_pLayerCom->Set_TexturePS(2, 4);    // Layer2 아스팔트 → t4
    m_pBlendCom->Set_TexturePS(0, 5);    // 혼합맵          → t5
    
    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    m_pContext->RSSetState(m_pRS.Get());

    m_pContext->DrawIndexed(m_iIndexCnt, 
        0,                      
        0);                     

    return S_OK;
}

f32_t CHill::GetHeight(f32_t x, f32_t z)
{
    // 지형 생성시 사용한 x,z 값을 이용하여 row, col 값을 계산
    // float x = -m_fHalfWidth + j * m_fDx;
    // float z = m_fHalfDepth - i * m_fDz;

    f32_t col = (x + m_fHalfWidth) / m_fDx;
    f32_t row = (m_fHalfDepth - z) / m_fDz;

    // 내림 적용
    int32_t j = (int32_t)floorf(col);
    int32_t i = (int32_t)floorf(row);

    // 지형 내부에 있는지 확인
    if (i < 0 || j < 0 || i >= (int32_t)m_ivtxCntZ - 1 || j >= (int32_t)m_ivtxCntX - 1)
        return 0.f;

    // 사각형 네 꼭짓점 높이 구하기
    // 두르기 순서 ABC / CBD
    f32_t A = m_vHeightmap[i * m_ivtxCntX + j];
    f32_t B = m_vHeightmap[i * m_ivtxCntX + j + 1];
    f32_t C = m_vHeightmap[(i + 1) * m_ivtxCntX + j];
    f32_t D = m_vHeightmap[(i + 1) * m_ivtxCntX + j + 1];

    f32_t s = col - (f32_t)j;
    f32_t t = row - (f32_t)i;

    if (s + t <= 1.f) // 위쪽 삼각형
        return A + s * (B - A) + t * (C - A);
    else
        return D + (1.f - s) * (C - D) + (1.f - t) * (B - D);
}

float4_t CHill::GetPlane(f32_t x, f32_t z)
{
    f32_t col = (x + m_fHalfWidth) / m_fDx;
    f32_t row = (m_fHalfDepth - z) / m_fDz;

    // 내림 적용
    int32_t j = (int32_t)floorf(col);
    int32_t i = (int32_t)floorf(row);

    // 지형 내부에 있는지 확인
    if (i < 0 || j < 0 || i >= (int32_t)m_ivtxCntZ - 1 || j >= (int32_t)m_ivtxCntX - 1)
        return float4_t{0.f,1.f,0.f,0.f};

    // 사각형 네 꼭짓점 높이 구하기
    // 두르기 순서 ABC / CBD
    f32_t A = m_vHeightmap[i * m_ivtxCntX + j];
    f32_t B = m_vHeightmap[i * m_ivtxCntX + j + 1];
    f32_t C = m_vHeightmap[(i + 1) * m_ivtxCntX + j];
    f32_t D = m_vHeightmap[(i + 1) * m_ivtxCntX + j + 1];

    f32_t s = col - (f32_t)j;
    f32_t t = row - (f32_t)i;

    if (s + t <= 1.f) // 위쪽 삼각형
    {
        vector_t p0 = vector_t{ j * m_fDx - m_fHalfWidth,A,-i * m_fDz + m_fHalfWidth,1.f };
        vector_t p1 = vector_t{ (j + 1) * m_fDx - m_fHalfWidth,B,-i * m_fDz + m_fHalfWidth,1.f };
        vector_t p2 = vector_t{ j * m_fDx - m_fHalfWidth,C,-(i + 1) * m_fDz + m_fHalfWidth,1.f };

        vector_t vPlane = XMPlaneFromPoints(p0, p1, p2);
        float4_t vReturnPlane;
        XMStoreFloat4(&vReturnPlane, vPlane);
        return vReturnPlane;
    }
    else
    {
        vector_t p0 = vector_t{ j * m_fDx - m_fHalfWidth,C,-(i + 1) * m_fDz + m_fHalfWidth,1.f };
        vector_t p1 = vector_t{ (j + 1) * m_fDx - m_fHalfWidth,B,-i * m_fDz + m_fHalfWidth,1.f };
        vector_t p2 = vector_t{ (j + 1) * m_fDx - m_fHalfWidth,D,-(i + 1) * m_fDz + m_fHalfWidth,1.f };

        vector_t vPlane = XMPlaneFromPoints(p0, p1, p2);
        float4_t vReturnPlane;
        XMStoreFloat4(&vReturnPlane, vPlane);
        return vReturnPlane;
    }
}

float3_t CHill::GetNormal(uint32_t i, uint32_t j)
{
    // 중심 차분
    // i -> 행 , j -> 열
    uint32_t iUp = (i > 0) ? i - 1 : i; // i<=0 이면 up은 자기 자신이 되는 것
    uint32_t iDown = (i < m_ivtxCntZ - 1) ? i + 1 : i;
    uint32_t jLeft = (j > 0) ? j - 1 : j;
    uint32_t jRight = (j < m_ivtxCntX - 1) ? j + 1 : j;

    f32_t L = m_vHeightmap[i * m_ivtxCntX + jLeft];
    f32_t R = m_vHeightmap[i * m_ivtxCntX + jRight];
    f32_t U = m_vHeightmap[iUp * m_ivtxCntX + j];      // +z 쪽
    f32_t D = m_vHeightmap[iDown * m_ivtxCntX + j];    // -z 쪽

    // 실제 이웃 간 거리 (경계에서는 한 칸, 내부에서는 두 칸)
    f32_t fDistX = (jRight - jLeft) * m_fDx;
    f32_t fDistZ = (iDown - iUp) * m_fDz;

    vector_t vN = vector_t{ (L - R) / fDistX, 
                            1.f, 
                            (D - U) / fDistZ, 
                            0.f };

    float3_t vNormal;
    XMStoreFloat3(&vNormal, XMVector3Normalize(vN));
    return vNormal;
}

void CHill::LoadHeightMap(const tchar_t* pHightMapPath)
{
    vector<uint16_t> in(m_ivtxCntX * m_ivtxCntZ);
    ifstream inFile;
    inFile.open(pHightMapPath, ios_base::binary); // binary로 읽어야 함

    if (inFile)
    {
        // read(char* s, streamsize count);
        // s: 읽은 데이터를 채울 메모리 시작 주소
        // count: 읽을 바이트 수 -> 백터 길이 * 벡터 자료형의 크기

        inFile.read(
            (char*)&in[0], 
            streamsize(in.size() * sizeof(in[0]))
        );
        inFile.close();
    }

    m_vHeightmap.resize(m_ivtxCntX * m_ivtxCntZ);
    for (uint32_t i = 0; i < m_ivtxCntZ; ++i)
    {
        for (uint32_t j = 0; j < m_ivtxCntX; ++j)
        {
            uint32_t iSrcRow = (m_ivtxCntZ - 1) - i;        // 파일 자체가 z가 뒤집혀있기때문에 반전시켜줘야 한다.
                                                            // 뒤집기 -> 마지막 인덱스에서 빼기
            m_vHeightmap[i * m_ivtxCntX + j] = in[iSrcRow * m_ivtxCntX + j] / 65535.f * 600.f - 30.f; // 16비트로 나눠야함 2^16 = 65536
        }
    }
}

HRESULT CHill::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Terrain_Blend,
        TEXT("Com_Texture"), m_pBlendCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Terrain_Layer,
        TEXT("Com_Blend"), m_pLayerCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_TERRAIN,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_TERRAIN,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    return S_OK;
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
