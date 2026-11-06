#include "Mesh.h"

CMesh::CMesh(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CVIBuffer{pDevice, pContext}
{
}

HRESULT CMesh::Initialize_Prototype(const aiMesh* pAiMesh)
{
#pragma region DATA
    m_iNumVertexBuffers = 1;
    m_iNumVertices = pAiMesh->mNumVertices;
    m_iVertexStride = sizeof(VTXNORM);

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
        memcpy(&pVertices[0].vPosition, &pAiMesh->mVertices[i],sizeof(float3_t));
        memcpy(&pVertices[0].vNormal, &pAiMesh->mNormals[i],sizeof(float3_t));
        memcpy(&pVertices[0].vTangent, &pAiMesh->mTangents[i],sizeof(float3_t));
        memcpy(&pVertices[0].vBinormal, &pAiMesh->mBitangents[i],sizeof(float3_t));
        memcpy(&pVertices[0].vTexcoord, &pAiMesh->mTextureCoords[0][i], sizeof(float2_t));
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
    for (uint32_t i = 0; i < m_iNumIndices; ++i)
    {
        pIndices[iIndex++] = pAiMesh->mFaces->mIndices[0];
        pIndices[iIndex++] = pAiMesh->mFaces->mIndices[1];
        pIndices[iIndex++] = pAiMesh->mFaces->mIndices[2];
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

shared_ptr<CMesh> CMesh::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const aiMesh* pAiMesh)
{
	auto pInstance = shared_ptr<CMesh>(new CMesh(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype(pAiMesh)))
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