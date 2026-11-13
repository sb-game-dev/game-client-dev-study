#include "Mesh.h"
#include "Model.h"

#include "Bone.h"

CMesh::CMesh(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CVIBuffer { pDevice, pContext }
{
}

HRESULT CMesh::Initialize_Prototype(MODEL eType, shared_ptr<CModel> pModel, const aiMesh* pAIMesh, fmatrix_t PreTransformMatrix)
{
#pragma region DATA
    strcpy_s(m_szName, pAIMesh->mName.C_Str());

    m_iMaterialIndex = pAIMesh->mMaterialIndex;
    m_iNumVertexBuffers = 1;
    m_iNumVertices = pAIMesh->mNumVertices;

    m_iNumIndices = pAIMesh->mNumFaces * 3;
    m_iIndexStride = 4;
    m_eIndexFormat = DXGI_FORMAT_R32_UINT;
    m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
#pragma endregion 

#pragma region VERTEX_BUFFER 

    HRESULT hr = MODEL::NONANIM == eType ? Ready_Meshes_For_NonAnim(pAIMesh, PreTransformMatrix) : Ready_Meshes_For_Anim(pModel, pAIMesh);
    if (FAILED(hr))
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

    uint32_t        iNumIndices = {};

    for (uint32_t i = 0; i < pAIMesh->mNumFaces; i++)
    {
        pIndices[iNumIndices++] = pAIMesh->mFaces[i].mIndices[0];
        pIndices[iNumIndices++] = pAIMesh->mFaces[i].mIndices[1];
        pIndices[iNumIndices++] = pAIMesh->mFaces[i].mIndices[2];
    }

    D3D11_SUBRESOURCE_DATA          IndexInitialData{};
    IndexInitialData.pSysMem = pIndices.get();

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;
#pragma endregion 

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, m_BoneMatrices, sizeof(float4x4_t) * 512);
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

HRESULT CMesh::Initialize(void* pArg)
{
    return S_OK;
}

HRESULT CMesh::Bind_BoneMatrices(vector<shared_ptr<class CBone>>& Bones, uint32_t iSlot)
{
    for (uint32_t i = 0; i < m_iNumBones; i++)
    {
        XMStoreFloat4x4(&m_BoneMatrices[i], 
            XMLoadFloat4x4(&m_OffsetMatrices[i]) * 
            XMLoadFloat4x4(Bones[m_BoneIndices[i]]->Get_CombinedTransformationMatrix()));
    }
    return m_pCB->Bind_Vertex_ShaderResource(iSlot, m_BoneMatrices);
}


HRESULT CMesh::Ready_Meshes_For_NonAnim(const aiMesh* pAIMesh, fmatrix_t PreTransformMatrix)
{
    m_iVertexStride = sizeof VTXMESH;

    D3D11_BUFFER_DESC           VertexBufferDesc{};
    VertexBufferDesc.ByteWidth = m_iVertexStride * m_iNumVertices;
    VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.StructureByteStride = m_iVertexStride;

    shared_ptr<VTXMESH[]> pVertices = make_shared<VTXMESH[]>(m_iNumVertices);

    for (uint32_t i = 0; i < m_iNumVertices; i++)
    {
        memcpy(&pVertices[i].vPosition, &pAIMesh->mVertices[i], sizeof float3_t);
        XMStoreFloat3(&pVertices[i].vPosition,
            XMVector3TransformCoord(XMLoadFloat3(&pVertices[i].vPosition), PreTransformMatrix));

        memcpy(&pVertices[i].vNormal, &pAIMesh->mNormals[i], sizeof float3_t);
        XMStoreFloat3(&pVertices[i].vNormal,
            XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vNormal), PreTransformMatrix));

        memcpy(&pVertices[i].vTangent, &pAIMesh->mTangents[i], sizeof float3_t);
        XMStoreFloat3(&pVertices[i].vTangent,
            XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vTangent), PreTransformMatrix));

        memcpy(&pVertices[i].vBinormal, &pAIMesh->mBitangents[i], sizeof float3_t);
        XMStoreFloat3(&pVertices[i].vBinormal,
            XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vBinormal), PreTransformMatrix));

        memcpy(&pVertices[i].vTexcoord, &pAIMesh->mTextureCoords[0][i], sizeof float2_t);
    }

    D3D11_SUBRESOURCE_DATA          VertexInitialData{};
    VertexInitialData.pSysMem = pVertices.get();

    if (FAILED(m_pDevice->CreateBuffer(&VertexBufferDesc, &VertexInitialData, &m_pVB)))
        return E_FAIL;

    return S_OK;
}

HRESULT CMesh::Ready_Meshes_For_Anim(shared_ptr<CModel> pModel, const aiMesh* pAIMesh)
{
    m_iVertexStride = sizeof VTXANIMMESH;

    D3D11_BUFFER_DESC           VertexBufferDesc{};
    VertexBufferDesc.ByteWidth = m_iVertexStride * m_iNumVertices;
    VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.StructureByteStride = m_iVertexStride;

    shared_ptr<VTXANIMMESH[]> pVertices = make_shared<VTXANIMMESH[]>(m_iNumVertices);

    for (uint32_t i = 0; i < m_iNumVertices; i++)
    {
        memcpy(&pVertices[i].vPosition, &pAIMesh->mVertices[i], sizeof float3_t);       
        memcpy(&pVertices[i].vNormal, &pAIMesh->mNormals[i], sizeof float3_t);     
        memcpy(&pVertices[i].vTangent, &pAIMesh->mTangents[i], sizeof float3_t);        
        memcpy(&pVertices[i].vBinormal, &pAIMesh->mBitangents[i], sizeof float3_t);       
        memcpy(&pVertices[i].vTexcoord, &pAIMesh->mTextureCoords[0][i], sizeof float2_t);
    }

    /* 이 메시에게 영향을 주는 뼈의 갯수 */
    m_iNumBones = pAIMesh->mNumBones;

    for (uint32_t i = 0; i < m_iNumBones; i++)
    {
        int32_t     iBoneIndex = pModel->Get_BoneIndex(pAIMesh->mBones[i]->mName.C_Str());
        if (-1 == iBoneIndex)
            return E_FAIL;

        float4x4_t      OffsetMatrix = {};

        memcpy(&OffsetMatrix, &pAIMesh->mBones[i]->mOffsetMatrix, sizeof(float4x4_t));

        XMStoreFloat4x4(&OffsetMatrix,
            XMMatrixTranspose(XMLoadFloat4x4(&OffsetMatrix)));
        
        m_OffsetMatrices.push_back(OffsetMatrix);

        m_BoneIndices.push_back(iBoneIndex);

        /* 이 뼈가 영향을 주는 정점의 갯수 */
        for (uint32_t j = 0; j < pAIMesh->mBones[i]->mNumWeights; ++j)
        {
            if(0.f == pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendWeight.x)
            {
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendIndex.x = i;
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendWeight.x = pAIMesh->mBones[i]->mWeights[j].mWeight;
            }

            else if (0.f == pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendWeight.y)
            {
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendIndex.y = i;
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendWeight.y = pAIMesh->mBones[i]->mWeights[j].mWeight;
            }
            else if (0.f == pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendWeight.z)
            {
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendIndex.z = i;
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendWeight.z = pAIMesh->mBones[i]->mWeights[j].mWeight;
            }
            else 
            {
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendIndex.w = i;
                pVertices[pAIMesh->mBones[i]->mWeights[j].mVertexId].vBlendWeight.w = pAIMesh->mBones[i]->mWeights[j].mWeight;
            }
        }
    }

    if (0 == m_iNumBones)
    {
        m_iNumBones = 1;

        m_BoneIndices.push_back(pModel->Get_BoneIndex(m_szName));

        float4x4_t      OffsetMatrix = {};
        XMStoreFloat4x4(&OffsetMatrix, XMMatrixIdentity());

        m_OffsetMatrices.push_back(OffsetMatrix);
    }

    D3D11_SUBRESOURCE_DATA          VertexInitialData{};
    VertexInitialData.pSysMem = pVertices.get();

    if (FAILED(m_pDevice->CreateBuffer(&VertexBufferDesc, &VertexInitialData, &m_pVB)))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CMesh> CMesh::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, shared_ptr<CModel> pModel, const aiMesh* pAIMesh, fmatrix_t PreTransformMatrix)
{
    auto pInstance = shared_ptr<CMesh>(new CMesh(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(eType, pModel, pAIMesh, PreTransformMatrix)))
    {
        MSG_BOX("Failed to Created : CMesh");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CMesh::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CMesh>(new CMesh(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CMesh");
        pInstance.reset();
    }

    return pInstance;
}