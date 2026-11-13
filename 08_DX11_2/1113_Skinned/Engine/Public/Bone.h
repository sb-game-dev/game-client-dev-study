#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CBone final
{
private:
	CBone();
public:
	virtual ~CBone() = default;

public:
	const float4x4_t* Get_CombinedTransformationMatrix() const {
		return &m_CombinedTransformationMatrix;
	}

public:
	HRESULT Initialize(const aiNode* pAINode, int32_t iParentBoneIndex);
	void Update_CombinedTransformationMatrix(const vector<shared_ptr<CBone>>& Bones, fmatrix_t PreTransformMatrix);
	bool_t Compare_Name(const char_t* pBoneName) const {
		return !strcmp(pBoneName, m_szName);
	}

private:
	char_t				m_szName[MAX_PATH] = {""};
	float4x4_t			m_TransformationMatrix = {};
	float4x4_t			m_CombinedTransformationMatrix = {};
	int32_t				m_iParentIndex = { -1 };


public:
	static shared_ptr<CBone> Create(const aiNode* pAINode, int32_t iParentBoneIndex);
};

NS_END