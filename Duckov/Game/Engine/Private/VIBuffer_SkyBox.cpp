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

    // z-
    pVertices[0] = { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 2.f / 3.f) };
    pVertices[1] = { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 1.f / 3.f) };
    pVertices[2] = { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.75f,  1.f / 3.f) };
    pVertices[3] = { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, 0.f, -1.f), float2_t(0.75f,  2.f / 3.f) };
    // x+
    pVertices[4] = { float3_t(+0.5f, -0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.75f,  2.f / 3.f) };
    pVertices[5] = { float3_t(+0.5f, +0.5f, -0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.75f,  1.f / 3.f) };
    pVertices[6] = { float3_t(+0.5f, +0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.5f, 1.f / 3.f) };
    pVertices[7] = { float3_t(+0.5f, -0.5f, +0.5f), float3_t(+1.f, 0.f, 0.f), float2_t(0.5f, 2.f / 3.f) };
    // z+
    pVertices[8] = { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.5f, 2.f / 3.f) };
    pVertices[9] = { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.5f, 1.f / 3.f) };
    pVertices[10] ={ float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.25f,  1.f / 3.f) };
    pVertices[11] ={ float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, 0.f, +1.f), float2_t(0.25f,  2.f / 3.f) };
    // x-
    pVertices[12] = { float3_t(-0.5f, -0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.25f,  2.f / 3.f) };
    pVertices[13] = { float3_t(-0.5f, +0.5f, +0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.25f,  1.f / 3.f) };
    pVertices[14] = { float3_t(-0.5f, +0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f, 1.f / 3.f) };
    pVertices[15] = { float3_t(-0.5f, -0.5f, -0.5f), float3_t(-1.f, 0.f, 0.f), float2_t(0.f, 2.f / 3.f) };
    // y+
    pVertices[16] = { float3_t(-0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.25f,  0.f / 3.f) };
    pVertices[17] = { float3_t(-0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.25f,  1.f / 3.f) };
    pVertices[18] = { float3_t(+0.5f, +0.5f, +0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.5f,   1.f / 3.f) };
    pVertices[19] = { float3_t(+0.5f, +0.5f, -0.5f), float3_t(0.f, +1.f, 0.f), float2_t(0.5f,   0.f / 3.f) };
    // y-
    pVertices[20] = { float3_t(-0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.25f,  2.f / 3.f) };
    pVertices[21] = { float3_t(-0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.25f,  3.f / 3.f) };
    pVertices[22] = { float3_t(+0.5f, -0.5f, -0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.5f,   3.f / 3.f) };
    pVertices[23] = { float3_t(+0.5f, -0.5f, +0.5f), float3_t(0.f, -1.f, 0.f), float2_t(0.5f,   2.f / 3.f) };

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
