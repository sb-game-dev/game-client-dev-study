#include "PipeLine.h"
#include "ConstantBuffer.h"

CPipeLine::CPipeLine(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
}

HRESULT CPipeLine::Initialize()
{
    uint32_t        iNumViewports = { 1 };
    D3D11_VIEWPORT  ViewportDesc{};

    m_pContext->RSGetViewports(&iNumViewports, &ViewportDesc);

    /* 유아이를 그려내기위한 직교투영 행렬들 */
    XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformMatrices[ETOUI(D3DTS::VIEW)],
        XMMatrixIdentity());
    XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformMatrices[ETOUI(D3DTS::PROJ)],
        XMMatrixOrthographicLH(ViewportDesc.Width, ViewportDesc.Height, 0.f, 1.f));

    /* 원근투영용 뷰, 투영행렬. */
    for (auto& Matrix : m_PipeLineDesc.PerspectiveTransformMatrices)    
        XMStoreFloat4x4(&Matrix, XMMatrixIdentity());

    XMStoreFloat4(&m_PipeLineDesc.vCamPosition, XMVectorSet(0.f, 0.f, 0.f, 1.f));

    /* 쉐이더에 전달해주기위한 상수버퍼를 생성해준다. */
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_PipeLineDesc, sizeof m_PipeLineDesc);
    if (nullptr == m_pCB)
        return E_FAIL;

	return S_OK;
}

void CPipeLine::Update()
{
    for (uint32_t i = 0; i < ETOUI(D3DTS::END); i++)
    {
        XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformInverseMatrices[i],
            XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_PipeLineDesc.OrthoTransformMatrices[i])));
        XMStoreFloat4x4(&m_PipeLineDesc.PerspectiveTransformInverseMatrices[i],
            XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_PipeLineDesc.PerspectiveTransformMatrices[i])));
    }
    memcpy(&m_PipeLineDesc.vCamPosition, &m_PipeLineDesc.PerspectiveTransformInverseMatrices[ETOUI(D3DTS::VIEW)].m[3], sizeof float4_t);
}

HRESULT CPipeLine::Bind_Vertex_ShaderResource(uint32_t iSlot)
{
    return m_pCB->Bind_Vertex_ShaderResource(iSlot, &m_PipeLineDesc);
}

HRESULT CPipeLine::Bind_Pixel_ShaderResource(uint32_t iSlot)
{
    return m_pCB->Bind_Pixel_ShaderResource(iSlot, &m_PipeLineDesc);
}


unique_ptr<CPipeLine> CPipeLine::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = unique_ptr<CPipeLine>(new CPipeLine(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CPipeLine");
        pInstance.reset();
    }

    return pInstance;
}

