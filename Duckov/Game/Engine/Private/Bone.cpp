#include "Bone.h"

HRESULT CBone::Initialize(const aiNode* pAINode, int32_t iParentBoneIndex)
{
	strcpy_s(m_szName, pAINode->mName.C_Str());

	m_iParentIndex = iParentBoneIndex;

	memcpy(&m_TransformMatrix, &pAINode->mTransformation, sizeof(float4x4_t));

	XMStoreFloat4x4(&m_TransformMatrix,
		XMMatrixTranspose(XMLoadFloat4x4(&m_TransformMatrix)));
	
	// 처음의 TransformMatrix를 저장
	m_InitialTransformMatrix = m_TransformMatrix;

	XMStoreFloat4x4(&m_CombinedTransformMatrix,
		XMMatrixIdentity());

	return S_OK;
}

HRESULT CBone::Initialize(FILE* pFile)
{
	uint32_t iLength = {};
	fread(&iLength, sizeof(uint32_t), 1, pFile);
	fread(m_szName, sizeof(char_t), iLength, pFile);
	
	fread(&m_iParentIndex, sizeof(int32_t), 1, pFile);

	fread(&m_TransformMatrix, sizeof(float4x4_t), 1, pFile);

	XMStoreFloat4x4(&m_TransformMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_TransformMatrix)));

	// 처음의 TransformMatrix를 저장
	m_InitialTransformMatrix = m_TransformMatrix;

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

void CBone::Get_SRT(BONE_SRT& tBone_SRT)
{
	vector_t vScale, vRotation, vTranspos;
	XMMatrixDecompose(&vScale, &vRotation, &vTranspos, XMLoadFloat4x4(&m_TransformMatrix));
	XMStoreFloat3(&tBone_SRT.vScale, vScale);
	XMStoreFloat4(&tBone_SRT.vRotation, vRotation);
	XMStoreFloat3(&tBone_SRT.vPosition, vTranspos);
}

void CBone::Set_Name(const char_t* pBoneName)
{
	strcpy_s(m_szName, pBoneName);
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

shared_ptr<CBone> CBone::Create(FILE* pFile)
{
	auto pInstance = shared_ptr<CBone>(new CBone());
	if (FAILED(pInstance->Initialize(pFile)))
	{
		MSG_BOX("Failed to Create : CBone (binary)");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CBone> CBone::Clone()
{
	return shared_ptr<CBone>(new CBone(*this));
}
