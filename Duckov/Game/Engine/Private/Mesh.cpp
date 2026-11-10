#include "Mesh.h"

CMesh::CMesh(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CVIBuffer{pDevice, pContext}
{
}

HRESULT CMesh::Initialize_Prototype(const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix)
{
#pragma region DATA
    m_iMaterialIndex = pAiMesh->mMaterialIndex;
    m_iNumVertexBuffers = 1;
    m_iNumVertices = pAiMesh->mNumVertices;
    m_iVertexStride = sizeof(VTXMESH);

    m_iNumIndices = pAiMesh->mNumFaces * 3;
    m_iIndexStride = 4;
    m_eIndexFormat = DXGI_FORMAT_R32_UINT;

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

    shared_ptr<VTXMESH[]> pVertices = make_shared<VTXMESH[]>(m_iNumVertices);
    for (uint32_t i = 0; i < m_iNumVertices; ++i)
    {
        memcpy(&pVertices[i].vPosition, &pAiMesh->mVertices[i],sizeof(float3_t));
        XMStoreFloat3(&pVertices[i].vPosition,
            XMVector3TransformCoord(XMLoadFloat3(&pVertices[i].vPosition),PreTransformMatrix));

        memcpy(&pVertices[i].vNormal, &pAiMesh->mNormals[i],sizeof(float3_t));
        XMStoreFloat3(&pVertices[i].vNormal,
            XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vNormal), PreTransformMatrix));

        memcpy(&pVertices[i].vTangent, &pAiMesh->mTangents[i],sizeof(float3_t));
        XMStoreFloat3(&pVertices[i].vTangent,
            XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vTangent), PreTransformMatrix));

        memcpy(&pVertices[i].vBinormal, &pAiMesh->mBitangents[i],sizeof(float3_t));
        XMStoreFloat3(&pVertices[i].vBinormal,
            XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vBinormal), PreTransformMatrix));

        memcpy(&pVertices[i].vTexcoord, &pAiMesh->mTextureCoords[0][i], sizeof(float2_t));
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
    uint32_t iIndex = {};
    for (uint32_t i = 0; i < pAiMesh->mNumFaces; ++i)
    {
        pIndices[iIndex++] = pAiMesh->mFaces[i].mIndices[0];
        pIndices[iIndex++] = pAiMesh->mFaces[i].mIndices[1];
        pIndices[iIndex++] = pAiMesh->mFaces[i].mIndices[2];
    }

    D3D11_SUBRESOURCE_DATA          IndexInitialData{};
    IndexInitialData.pSysMem = pIndices.get();

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;
#pragma endregion

#pragma region CullingAABB
    m_bUseCulling = true;
    BoundingBox::CreateFromPoints(m_tLocalBox, m_iNumVertices, &pVertices[0].vPosition, sizeof(VTXMESH));
#pragma endregion

	return S_OK;
}

HRESULT CMesh::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CMesh::Render_Instanced(ID3D11Buffer* pInstanceVB, uint32_t iInstanceStride, uint32_t iNumInstances)
{
    ID3D11Buffer*   pVBs[] = { m_pVB.Get(), pInstanceVB };
    uint32_t        iStrides[] = { m_iVertexStride,iInstanceStride };
    uint32_t        iOffsets[] = { 0,0 };

    m_pContext->IASetVertexBuffers(0, 2, pVBs, iStrides, iOffsets);
    m_pContext->IASetIndexBuffer(m_pIB.Get(), m_eIndexFormat, 0);
    m_pContext->IASetPrimitiveTopology(m_ePrimitiveTopology);
    m_pContext->DrawIndexedInstanced(m_iNumIndices, iNumInstances, 0, 0, 0);

    return S_OK;
}

shared_ptr<CMesh> CMesh::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const aiMesh* pAiMesh, fmatrix_t PreTransformMatrix)
{
	auto pInstance = shared_ptr<CMesh>(new CMesh(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype(pAiMesh, PreTransformMatrix)))
	{
		MSG_BOX("Failed to Created : CMesh");
		return nullptr;
	}
	return pInstance;
}
shared_ptr<CPrototype> CMesh::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CMesh>(new CMesh(*this));

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Clone : CMesh");
		return nullptr;
	}
	return pInstance;
}