#include "VIBuffer_SkyBox.h"

CVIBuffer_SkyBox::CVIBuffer_SkyBox(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CVIBuffer{ pDevice,pContext }
{
}

HRESULT CVIBuffer_SkyBox::Initialize_Prototype()
{
#pragma region DATA
    m_iNumVertexBuffers = 1;
    m_iNumVertices = 24;
    m_iVertexStride = sizeof(VTXNORM);

    m_iNumIndices = 36;
    m_iIndexStride = 2;
    m_eIndexFormat = DXGI_FORMAT_R16_UINT;

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

    // 반 텍셀 오프셋 : 면 경계에서 십자 이미지의 빈 칸(배경색)이 선형 필터링으로 섞이지 않게 UV를 안쪽으로 당김
    // 텍스처 크기가 바뀌면 분모도 같이 바꿀 것 (proc_preview.png = 512 x 384)
    const float fHU = 0.5f / 512.f;
    const float fHV = 0.5f / 384.f;

    // z-
    pVertices[0] = { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f - fHU, 2.f / 3.f - fHV) };
    pVertices[1] = { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f - fHU, 1.f / 3.f + fHV) };
    pVertices[2] = { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.75f + fHU, 1.f / 3.f + fHV) };
    pVertices[3] = { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.75f + fHU, 2.f / 3.f - fHV) };
    // x+
    pVertices[4] = { float3_t(+0.5f, -0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.75f - fHU, 2.f / 3.f - fHV) };
    pVertices[5] = { float3_t(+0.5f, +0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.75f - fHU, 1.f / 3.f + fHV) };
    pVertices[6] = { float3_t(+0.5f, +0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.5f + fHU, 1.f / 3.f + fHV) };
    pVertices[7] = { float3_t(+0.5f, -0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.5f + fHU, 2.f / 3.f - fHV) };
    // z+
    pVertices[8] = { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.5f - fHU, 2.f / 3.f - fHV) };
    pVertices[9] = { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.5f - fHU, 1.f / 3.f + fHV) };
    pVertices[10] = { float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.25f + fHU, 1.f / 3.f + fHV) };
    pVertices[11] = { float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.25f + fHU, 2.f / 3.f - fHV) };
    // x-
    pVertices[12] = { float3_t(-0.5f, -0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.25f - fHU, 2.f / 3.f - fHV) };
    pVertices[13] = { float3_t(-0.5f, +0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.25f - fHU, 1.f / 3.f + fHV) };
    pVertices[14] = { float3_t(-0.5f, +0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f + fHU, 1.f / 3.f + fHV) };
    pVertices[15] = { float3_t(-0.5f, -0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f + fHU, 2.f / 3.f - fHV) };
    // y+
    pVertices[16] = { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.25f + fHU, 0.f + fHV) };
    pVertices[17] = { float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.25f + fHU, 1.f / 3.f - fHV) };
    pVertices[18] = { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.5f - fHU, 1.f / 3.f - fHV) };
    pVertices[19] = { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.5f - fHU, 0.f + fHV) };
    // y-
    pVertices[20] = { float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.25f + fHU, 2.f / 3.f + fHV) };
    pVertices[21] = { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.25f + fHU, 1.f - fHV) };
    pVertices[22] = { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.5f - fHU, 1.f - fHV) };
    pVertices[23] = { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.5f - fHU, 2.f / 3.f + fHV) };

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

    shared_ptr<uint16_t[]>  pIndices = make_shared<uint16_t[]>(m_iNumIndices);
    uint16_t iVtx = 0;
    for (uint16_t i = 0; i < 36; i += 6)
    {
        pIndices[i] = iVtx;
        pIndices[i + 1] = iVtx + 1;
        pIndices[i + 2] = iVtx + 2;

        pIndices[i + 3] = iVtx;
        pIndices[i + 4] = iVtx + 2;
        pIndices[i + 5] = iVtx + 3;

        iVtx += 4;
    }

    D3D11_SUBRESOURCE_DATA          IndexInitialData{};
    IndexInitialData.pSysMem = pIndices.get();

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;
#pragma endregion
    return S_OK;
}

HRESULT CVIBuffer_SkyBox::Initialize(void* pArg)
{
    return S_OK;
}

shared_ptr<CVIBuffer_SkyBox> CVIBuffer_SkyBox::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CVIBuffer_SkyBox>(new CVIBuffer_SkyBox(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CVIBuffer_SkyBox");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVIBuffer_SkyBox::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CVIBuffer_SkyBox>(new CVIBuffer_SkyBox(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVIBuffer_SkyBox");
        pInstance.reset();
    }

    return pInstance;
}
