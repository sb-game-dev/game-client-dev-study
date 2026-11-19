#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CBone final
{
private:
	CBone() = default;
public:
	~CBone() = default;

public:
	HRESULT Initialize(const aiNode* pAINode, int32_t iParentBoneIndex);
	void   Update_CombinedTranformMatrix(const vector<shared_ptr<CBone>>& Bones, fmatrix_t PreTranformMatrix);
	bool_t Compare_Name(const char_t* pBoneName) const { 
		return !strcmp(pBoneName, m_szName); 
	}
	const float4x4_t* Get_CombinedTransformMatrix() const {
		return &m_CombinedTransformMatrix;
	}
	void Set_TransfromMatrix(fmatrix_t TransformMatrix) {
		XMStoreFloat4x4(&m_TransformMatrix, TransformMatrix);
	}
	void Reset_TransformMatrix() { m_TransformMatrix = m_InitialTransformMatrix; }
	void Get_SRT(BONE_SRT& tBone_SRT);

private:
	char_t		m_szName[MAX_PATH] = { "" };
	float4x4_t	m_TransformMatrix = {};
	float4x4_t	m_CombinedTransformMatrix = {};
	float4x4_t	m_InitialTransformMatrix = {};

	int32_t		m_iParentIndex = { -1 };

public:
	static shared_ptr<CBone> Create(const aiNode* pAINode, int32_t iParentBoneIndex);
	shared_ptr<CBone> Clone();
};

NS_END