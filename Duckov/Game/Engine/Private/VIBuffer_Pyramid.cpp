#include "VIBuffer_Pyramid.h"

CVIBuffer_Pyramid::CVIBuffer_Pyramid(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CVIBuffer{ pDevice,pContext }
{
}

HRESULT CVIBuffer_Pyramid::Initialize_Prototype()
{
#pragma region DATA
    m_iNumVertexBuffers = 1;
    m_iNumVertices = 5;
    m_iVertexStride = sizeof(VTXCOL);

    m_iNumIndices = 18;
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

    shared_ptr<VTXCOL[]> pVertices = make_shared<VTXCOL[]>(m_iNumVertices);
    pVertices[0] = { float3_t(-0.5f, -0.5f, -0.5f), float4_t(Colors::White)};
    pVertices[1] = { float3_t(-0.5f, +0.5f, -0.5f), float4_t(Colors::Black)};
    pVertices[2] = { float3_t(+0.5f, +0.5f, -0.5f), float4_t(Colors::Red)};
    pVertices[3] = { float3_t(+0.5f, -0.5f, -0.5f), float4_t(Colors::Brown)};
    pVertices[4] = { float3_t(0.f, 0.f, +0.5f),     float4_t(Colors::Orange) };

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

    //shared_ptr<uint16_t[]>  pIndices = make_shared<uint16_t[]>(m_iNumIndices);
    uint16_t pIndices[] = {
         0, 1, 2,
         0, 2, 3,

         1, 4, 2,
         2, 4, 3,
         3, 4, 0,
         0, 4, 1
    };

    D3D11_SUBRESOURCE_DATA          IndexInitialData{};
    IndexInitialData.pSysMem = pIndices;

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;
#pragma endregion

    return S_OK;
}

HRESULT CVIBuffer_Pyramid::Initialize(void* pArg)
{
    return S_OK;
}

shared_ptr<CVIBuffer_Pyramid> CVIBuffer_Pyramid::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CVIBuffer_Pyramid>(new CVIBuffer_Pyramid(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CVIBuffer_Pyramid");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVIBuffer_Pyramid::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CVIBuffer_Pyramid>(new CVIBuffer_Pyramid(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVIBuffer_Pyramid");
        pInstance.reset();
    }

    return pInstance;
}
