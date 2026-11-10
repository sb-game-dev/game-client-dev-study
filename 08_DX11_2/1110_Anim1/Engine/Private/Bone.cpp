#include "Bone.h"

CBone::CBone()
{
}

HRESULT CBone::Initialize(const aiNode* pAINode, int32_t iParentBoneIndex)
{
    strcpy_s(m_szName, pAINode->mName.C_Str());

    m_iParentIndex = iParentBoneIndex;

    memcpy(&m_TransformationMatrix, &pAINode->mTransformation, sizeof(float4x4_t));

    XMStoreFloat4x4(&m_TransformationMatrix,
        XMMatrixTranspose(XMLoadFloat4x4(&m_TransformationMatrix)));

    XMStoreFloat4x4(&m_CombinedTransformationMatrix,
        XMMatrixIdentity());

    return S_OK;
}

shared_ptr<CBone> CBone::Create(const aiNode* pAINode, int32_t iParentBoneIndex)
{
    auto pInstance = shared_ptr<CBone>(new CBone());

    if (FAILED(pInstance->Initialize(pAINode, iParentBoneIndex)))
    {
        MSG_BOX("Failed to Created : CBone");
        pInstance.reset();
    }

    return pInstance;
}

