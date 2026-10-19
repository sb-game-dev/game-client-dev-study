#include "VIBuffer_Rect.h"

CVIBuffer_Rect::CVIBuffer_Rect(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CVIBuffer{pDevice,pContext}
{
}

HRESULT CVIBuffer_Rect::Initialize_Prototype()
{
#pragma region DATA
    m_iNumVertexBuffers = 1;
    m_iNumVertices = 4;
    m_iVertexStride = sizeof(VTXNORM);

    m_iNumIndices = 6;
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
    pVertices[0].vPosition = float3_t(-0.5f, 0.5f, 0.f);
    pVertices[0].vNormal = float3_t(0.f, 0.f, -1.f);
    pVertices[0].Tex = float2_t(0.f, 0.f);

    pVertices[1].vPosition = float3_t(0.5f, 0.5f, 0.f);
    pVertices[1].vNormal = float3_t(0.f, 0.f, -1.f);
    pVertices[1].Tex = float2_t(1.f, 0.f);

    pVertices[2].vPosition = float3_t(0.5f, -0.5f, 0.f);
    pVertices[2].vNormal = float3_t(0.f, 0.f, -1.f);
    pVertices[2].Tex = float2_t(1.f, 1.f);

    pVertices[3].vPosition = float3_t(-0.5f, -0.5f, 0.f);
    pVertices[3].vNormal = float3_t(0.f, 0.f, -1.f);
    pVertices[3].Tex = float2_t(0.f, 1.f);

    D3D11_SUBRESOURCE_DATA VertexInitialData{};
    VertexInitialData.pSysMem = pVertices.get();

    if(FAILED(m_pDevice->CreateBuffer(&VertexBufferDesc,&VertexInitialData,&m_pVB)))
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
    pIndices[0] = 0;
    pIndices[1] = 1;
    pIndices[2] = 2;

    pIndices[3] = 0;
    pIndices[4] = 2;
    pIndices[5] = 3;

    D3D11_SUBRESOURCE_DATA          IndexInitialData{};
    IndexInitialData.pSysMem = pIndices.get();

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;
#pragma endregion


	return S_OK;
}

HRESULT CVIBuffer_Rect::Initialize(void* pArg)
{
	return S_OK;
}

shared_ptr<CVIBuffer_Rect> CVIBuffer_Rect::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CVIBuffer_Rect>(new CVIBuffer_Rect(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CVIBuffer_Rect");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVIBuffer_Rect::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CVIBuffer_Rect>(new CVIBuffer_Rect(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVIBuffer_Rect");
        pInstance.reset();
    }

    return pInstance;
}
