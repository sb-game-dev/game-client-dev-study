#include "Bone.h"

HRESULT CBone::Initialize(const aiNode* pAINode, int32_t iParentBoneIndex)
{
	strcpy_s(m_szName, pAINode->mName.C_Str());

	m_iParentIndex = iParentBoneIndex;

	memcpy(&m_TransformMatrix, &pAINode->mTransformation, sizeof(float4x4_t));

	XMStoreFloat4x4(&m_TransformMatrix,
		XMMatrixTranspose(XMLoadFloat4x4(&m_TransformMatrix)));

	XMStoreFloat4x4(&m_CombinedTransformMatrix,
		XMMatrixIdentity());

	return S_OK;
}

void CBone::Update_CombinedTranformMatrix(const vector<shared_ptr<CBone>>& Bones, fmatrix_t PreTranformMatrix)
{
	if (-1 == m_iParentIndex)
	{
		XMStoreFloat4x4(&m_CombinedTransformMatrix,
			XMLoadFloat4x4(&m_TransformMatrix) * PreTranformMatrix);
		return;
	}
	XMStoreFloat4x4(&m_CombinedTransformMatrix,
		XMLoadFloat4x4(&m_TransformMatrix)
		* XMLoadFloat4x4(&Bones[m_iParentIndex]->m_CombinedTransformMatrix));
}

shared_ptr<CBone> CBone::Create(const aiNode* pAINode, int32_t iParentBoneIndex)
{
	auto pInstance = shared_ptr<CBone>(new CBone());
	if (FAILED(pInstance->Initialize(pAINode, iParentBoneIndex)))
	{
		MSG_BOX("Failed to Create : CBone");
		pInstance.reset();
	}
	return pInstance;
}
