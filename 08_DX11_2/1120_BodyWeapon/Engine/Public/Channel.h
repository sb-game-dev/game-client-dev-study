#pragma once

#include "Engine_Defines.h"

/* 특정애니메이션을 위해 사용되는 뼈의 정보.  */
/* 재생 위치에 따른 상태들을 보관한다. */

NS_BEGIN(Engine)

class CChannel final 
{
private:
	CChannel();
public:
	virtual ~CChannel() = default;

public:
	HRESULT Initialize(const aiNodeAnim* pAIChannel, class CModel* pModel);
	void Update_TransformationMatrix(const vector<shared_ptr<class CBone>>& Bones, uint32_t* pLeftKeyFrameIndex, f32_t fCurrentTrackPosition);


private:
	char_t				m_szName[MAX_PATH] = {};
	uint32_t			m_iNumKeyFrames = {};
	vector<KEYFRAME>	m_KeyFrames;
	int32_t				m_iBoneIndex = {};
	//uint32_t			m_iLeftKeyFrameIndex = { };

public:
	static shared_ptr<CChannel> Create(const aiNodeAnim* pAIChannel, class CModel* pModel);
};

NS_END