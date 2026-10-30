#include "ConstantBuffer.h"

CConstantBuffer::CConstantBuffer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
}

HRESULT CConstantBuffer::Initialize(const void* pBuffer, uint32_t iBufferLength)
{
    D3D11_BUFFER_DESC           BufferDesc{};
    BufferDesc.ByteWidth = iBufferLength;
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BufferDesc.MiscFlags = 0;
    BufferDesc.StructureByteStride = 0;

    m_iByteLength = iBufferLength;

    D3D11_SUBRESOURCE_DATA      InitialData{};
    InitialData.pSysMem = pBuffer;

    if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &InitialData, &m_pCB)))
        return E_FAIL;

	return S_OK;
}

HRESULT CConstantBuffer::Bind_Vertex_ShaderResource(uint32_t iSlot, const void* pBuffer)
{
    D3D11_MAPPED_SUBRESOURCE        SubResourceData{};

    m_pContext->Map(m_pCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResourceData);

    memcpy(SubResourceData.pData, pBuffer, m_iByteLength);

    m_pContext->Unmap(m_pCB.Get(), 0);

    ID3D11Buffer* pCB[] = {
        m_pCB.Get(), 
    };

    m_pContext->VSSetConstantBuffers(iSlot, 1, pCB);

    return S_OK;
}

HRESULT CConstantBuffer::Bind_Pixel_ShaderResource(uint32_t iSlot, const void* pBuffer)
{
    D3D11_MAPPED_SUBRESOURCE        SubResourceData{};

    m_pContext->Map(m_pCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResourceData);

    memcpy(SubResourceData.pData, pBuffer, m_iByteLength);

    m_pContext->Unmap(m_pCB.Get(), 0);

    ID3D11Buffer* pCB[] = {
        m_pCB.Get(),
    };

    m_pContext->PSSetConstantBuffers(iSlot, 1, pCB);

    return S_OK;
}

shared_ptr<CConstantBuffer> CConstantBuffer::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const void* pBuffer, uint32_t iBufferLength)
{
    auto pInstance = shared_ptr<CConstantBuffer>(new CConstantBuffer(pDevice, pContext));

    if (FAILED(pInstance->Initialize(pBuffer, iBufferLength)))
    {
        MSG_BOX("Failed to Created : CConstantBuffer");
        pInstance.reset();
    }

    return pInstance;
}
