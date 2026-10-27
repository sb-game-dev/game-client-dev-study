#include "VIBuffer_Terrain.h"
#include <fstream>

CVIBuffer_Terrain::CVIBuffer_Terrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CVIBuffer{ pDevice,pContext }
{
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(const tchar_t* pHeightMapPath)
{
#pragma region DATA
    m_iNumVertexBuffers = 1;
    m_iNumVertices = m_ivtxCntX * m_ivtxCntZ;
    m_iVertexStride = sizeof(VTXNORM);

    m_iNumIndices = (m_ivtxCntX - 1) * (m_ivtxCntZ - 1) * 6;
    m_iIndexStride = 4;
    m_eIndexFormat = DXGI_FORMAT_R32_UINT;

    m_ePrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
#pragma endregion

#pragma region VERTEX_BUFFER

    if (FAILED(LoadHeightMap(pHeightMapPath)))
        return E_FAIL;

    D3D11_BUFFER_DESC   VertexBufferDesc{};
    VertexBufferDesc.ByteWidth = m_iVertexStride * m_iNumVertices;
    VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.StructureByteStride = m_iVertexStride;

    shared_ptr<VTXNORM[]> pVertices = make_shared<VTXNORM[]>(m_iNumVertices);

    f32_t   du = 1.f / (m_ivtxCntX - 1);
    f32_t   dv = 1.f / (m_ivtxCntZ - 1);

    m_fHalfWidth = 0.5f * (m_ivtxCntX - 1) * m_fDx;
    m_fHalfDepth = 0.5f * (m_ivtxCntZ - 1) * m_fDz;

    for (uint32_t i = 0; i < m_ivtxCntZ; ++i)
    {
        float z = m_fHalfDepth - i * m_fDz;
        for (uint32_t j = 0; j < m_ivtxCntX; ++j)
        {
            float x = -m_fHalfWidth + j * m_fDx;

            pVertices[i * m_ivtxCntX + j].vPosition = float3_t( x, GetHeight(x, z), z );
            pVertices[i * m_ivtxCntX + j].vNormal = GetNormal(i, j);
            pVertices[i * m_ivtxCntX + j].Tex = { j * du, i * dv };
        }
    }

    D3D11_SUBRESOURCE_DATA VertexInitialData{};
    VertexInitialData.pSysMem = pVertices.get();

    if (FAILED(m_pDevice->CreateBuffer(&VertexBufferDesc, &VertexInitialData, &m_pVB)))
        return E_FAIL;
#pragma endregion

#pragma region INDEX_BUFFER
    D3D11_BUFFER_DESC           IndexBufferDesc{};
    IndexBufferDesc.ByteWidth = m_iIndexStride * m_iNumIndices;
    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = m_iIndexStride;

    shared_ptr<uint32_t[]>  pIndices = make_shared<uint32_t[]>(m_iNumIndices);

    uint32_t k = 0;
    for (uint32_t i = 0; i < m_ivtxCntZ - 1; ++i)
    {
        for (uint32_t j = 0; j < m_ivtxCntX - 1; ++j)
        {
            pIndices[k] = i * m_ivtxCntX + j;
            pIndices[k + 1] = i * m_ivtxCntX + j + 1;
            pIndices[k + 2] = (i + 1) * m_ivtxCntX + j;
            pIndices[k + 3] = (i + 1) * m_ivtxCntX + j;
            pIndices[k + 4] = i * m_ivtxCntX + j + 1;
            pIndices[k + 5] = (i + 1) * m_ivtxCntX + j + 1;

            k += 6;
        }
    }

    D3D11_SUBRESOURCE_DATA          IndexInitialData{};
    IndexInitialData.pSysMem = pIndices.get();

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;
#pragma endregion

#pragma region CullingAABB
    m_bUseCulling = false;
    //BoundingBox::CreateFromPoints(m_tLocalBox, m_iVertexStride, &pVertices[0].vPosition, sizeof(VTXNORM));
#pragma endregion
    return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void* pArg)
{
    return S_OK;
}

f32_t CVIBuffer_Terrain::GetHeight(f32_t x, f32_t z)
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

float4_t CVIBuffer_Terrain::GetPlane(f32_t x, f32_t z)
{
    f32_t col = (x + m_fHalfWidth) / m_fDx;
    f32_t row = (m_fHalfDepth - z) / m_fDz;

    // 내림 적용
    int32_t j = (int32_t)floorf(col);
    int32_t i = (int32_t)floorf(row);

    // 지형 내부에 있는지 확인
    if (i < 0 || j < 0 || i >= (int32_t)m_ivtxCntZ - 1 || j >= (int32_t)m_ivtxCntX - 1)
        return float4_t{ 0.f,1.f,0.f,0.f };

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
        vector_t p0 = vector_t{ j * m_fDx - m_fHalfWidth,A,-i * m_fDz + m_fHalfDepth,1.f };
        vector_t p1 = vector_t{ (j + 1) * m_fDx - m_fHalfWidth,B,-i * m_fDz + m_fHalfDepth,1.f };
        vector_t p2 = vector_t{ j * m_fDx - m_fHalfWidth,C,-(i + 1) * m_fDz + m_fHalfDepth,1.f };

        vector_t vPlane = XMPlaneFromPoints(p0, p1, p2);
        float4_t vReturnPlane;
        XMStoreFloat4(&vReturnPlane, vPlane);
        return vReturnPlane;
    }
    else
    {
        vector_t p0 = vector_t{ j * m_fDx - m_fHalfWidth,C,-(i + 1) * m_fDz + m_fHalfDepth,1.f };
        vector_t p1 = vector_t{ (j + 1) * m_fDx - m_fHalfWidth,B,-i * m_fDz + m_fHalfDepth,1.f };
        vector_t p2 = vector_t{ (j + 1) * m_fDx - m_fHalfWidth,D,-(i + 1) * m_fDz + m_fHalfDepth,1.f };

        vector_t vPlane = XMPlaneFromPoints(p0, p1, p2);
        float4_t vReturnPlane;
        XMStoreFloat4(&vReturnPlane, vPlane);
        return vReturnPlane;
    }
}

HRESULT CVIBuffer_Terrain::LoadHeightMap(const tchar_t* pHightMapPath)
{
    vector<uint16_t> in(m_ivtxCntX * m_ivtxCntZ);
    ifstream inFile;
    inFile.open(pHightMapPath, ios_base::binary); // binary로 읽어야 함

    if (!inFile)
        return E_FAIL;

    // read(char* s, streamsize count);
    // s: 읽은 데이터를 채울 메모리 시작 주소
    // count: 읽을 바이트 수 -> 백터 길이 * 벡터 자료형의 크기
    
    inFile.read(
        (char*)&in[0],
        streamsize(in.size() * sizeof(in[0]))
    );
    inFile.close();

    
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
    return S_OK;
}

float3_t CVIBuffer_Terrain::GetNormal(uint32_t i, uint32_t j)
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

shared_ptr<CVIBuffer_Terrain> CVIBuffer_Terrain::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pHeightMapPath)
{
    auto pInstance = shared_ptr<CVIBuffer_Terrain>(new CVIBuffer_Terrain(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pHeightMapPath)))
    {
        MSG_BOX("Failed to Created : CVIBuffer_Terrain");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVIBuffer_Terrain::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CVIBuffer_Terrain>(new CVIBuffer_Terrain(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVIBuffer_Terrain");
        pInstance.reset();
    }

    return pInstance;
}
