#include "VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CVIBuffer{ pDevice,pContext }
{
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(const tchar_t* pHeightMapPath)
{
    if (FAILED(LoadHeightMap(pHeightMapPath)))
        return E_FAIL;
#pragma region DATA
    m_iNumVertexBuffers = 1;
    m_iNumVertices = m_ivtxCntX * m_ivtxCntZ;
    m_iVertexStride = sizeof(VTXNORM);
    m_vVertices.reserve(m_iNumVertices);

    m_iNumIndices = (m_ivtxCntX - 1) * (m_ivtxCntZ - 1) * 6;
    m_iIndexStride = 4;
    m_eIndexFormat = DXGI_FORMAT_R32_UINT;
    m_vIndices.resize(m_iNumIndices);

    m_ePrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
#pragma endregion

#pragma region VERTEX_BUFFER


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

    for (uint32_t i = 0; i < m_ivtxCntZ; ++i)
    {
        float z = m_fHalfDepth - i * m_fDz;
        for (uint32_t j = 0; j < m_ivtxCntX; ++j)
        {
            float x = -m_fHalfWidth + j * m_fDx;

            pVertices[i * m_ivtxCntX + j].vPosition = float3_t( x, GetHeight(x, z), z );
            pVertices[i * m_ivtxCntX + j].vNormal = float3_t(0.f, 0.f, 0.f);
            pVertices[i * m_ivtxCntX + j].Tex = { j * du, i * dv };

            m_vVertices.push_back(pVertices[i * m_ivtxCntX + j].vPosition);
        }
    }

#pragma endregion

#pragma region INDEX_BUFFER
    D3D11_BUFFER_DESC           IndexBufferDesc{};
    IndexBufferDesc.ByteWidth = m_iIndexStride * m_iNumIndices;
    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = m_iIndexStride;


    uint32_t        iNumIndices = {};
    for (uint32_t i = 0; i < m_ivtxCntZ - 1; ++i)
    {
        for (uint32_t j = 0; j < m_ivtxCntX - 1; ++j)
        {
            uint32_t        iIndex = i * m_ivtxCntX + j;

            uint32_t        iIndices[4] = {
                iIndex,                     
                iIndex + 1,                 
                iIndex + m_ivtxCntX + 1,    
                iIndex + m_ivtxCntX         
            };

            vector_t        vSour, vDest, vNormal;

            m_vIndices[iNumIndices++] = iIndices[0];
            m_vIndices[iNumIndices++] = iIndices[1];
            m_vIndices[iNumIndices++] = iIndices[3];

            vSour = XMLoadFloat3(&pVertices[iIndices[1]].vPosition) -
                XMLoadFloat3(&pVertices[iIndices[0]].vPosition);
            vDest = XMLoadFloat3(&pVertices[iIndices[3]].vPosition) -
                XMLoadFloat3(&pVertices[iIndices[1]].vPosition);

            vNormal = XMVector3Normalize(XMVector3Cross(vSour, vDest));

            XMStoreFloat3(&pVertices[iIndices[0]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[0]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[1]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[1]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[3]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[3]].vNormal) + vNormal);

            m_vIndices[iNumIndices++] = iIndices[3];
            m_vIndices[iNumIndices++] = iIndices[1];
            m_vIndices[iNumIndices++] = iIndices[2];


            vSour = XMLoadFloat3(&pVertices[iIndices[1]].vPosition) -
                XMLoadFloat3(&pVertices[iIndices[3]].vPosition);
            vDest = XMLoadFloat3(&pVertices[iIndices[2]].vPosition) -
                XMLoadFloat3(&pVertices[iIndices[1]].vPosition);

            vNormal = XMVector3Normalize(XMVector3Cross(vSour, vDest));

            XMStoreFloat3(&pVertices[iIndices[3]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[3]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[1]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[1]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[2]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[2]].vNormal) + vNormal);
        }
    }

    for (uint32_t i = 0; i < m_iNumVertices; i++)
    {
        XMStoreFloat3(&pVertices[i].vNormal,
            XMVector3Normalize(XMLoadFloat3(&pVertices[i].vNormal)));
    }
    D3D11_SUBRESOURCE_DATA VertexInitialData{};
    VertexInitialData.pSysMem = pVertices.get();

    if (FAILED(m_pDevice->CreateBuffer(&VertexBufferDesc, &VertexInitialData, &m_pVB)))
        return E_FAIL;

    D3D11_SUBRESOURCE_DATA          IndexInitialData{};
    IndexInitialData.pSysMem = m_vIndices.data();

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;
#pragma endregion

#pragma region CullingAABB
    m_bUseCulling = true;
    BoundingBox::CreateFromPoints(m_tLocalBox, m_iNumVertices, &pVertices[0].vPosition, sizeof(VTXNORM));
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
    // 1. 파일 열기
    FILE* pFile = nullptr;
    if (0 != _wfopen_s(&pFile, pHightMapPath, L"rb") || nullptr == pFile)
        return E_FAIL;

    // 2. 파일 크기 구하기
    fseek(pFile, 0, SEEK_END);      // 파일 끝으로 이동
    long lFileSize = ftell(pFile);  // 현재 위치 읽기
    fseek(pFile, 0, SEEK_SET);      // 파일 처음으로 이동

    // 3. 한 변의 길이 계산
    uint32_t iCount = (uint32_t)(lFileSize / sizeof(uint16_t)); // 총 정점의 개수
    uint32_t iSide = (uint32_t)lroundf(sqrtf((f32_t)iCount));   // 가로 x 세로 한 줄에 몇 개인지 확인
    m_ivtxCntX = m_ivtxCntZ = iSide;

    m_fHalfWidth = (m_ivtxCntX - 1) * 0.5f * m_fDx;
    m_fHalfDepth = (m_ivtxCntZ - 1) * 0.5f * m_fDz;

    // 4. 높이값 읽기
    vector<uint16_t> in(iCount);
    fread(in.data(), sizeof(uint16_t), iCount, pFile);
    fclose(pFile);
    // 5. 높이 변환
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
