#pragma once

#include "Engine_Defines.h"

/* 이 애니메이션에서 사용해야할 뼈들의 정보를 보관한다. */
/* 이 애니메이션의 전체 길이, 속도등의 정보도 관리한다. */

NS_BEGIN(Engine)

class CAnimation final
{
private:
	CAnimation();
public:
	~CAnimation() = default;

public:
	HRESULT Initialize(const aiAnimation* pAIAnimation, class CModel* pModel);
	bool_t Update_TransformationMatrix(const vector<shared_ptr<class CBone>>& Bones, bool_t isLoop, f32_t fTimeDelta);
	void Reset();
private:
	char_t				m_szName[MAX_PATH] = { "" };
	f32_t				m_fDuration = {}; /* 전체길이 */
	f32_t				m_fTickPerSecond = {};
	f32_t				m_fCurrentTrackPosition = {};

	/* 이 애니메이션을 재생위해 필요한 뼈의 갯수 */
	uint32_t								m_iNumChannels = {};
	vector<shared_ptr<class CChannel>>		m_Channels;
	vector<uint32_t>						m_LeftKeyFrameIndices;

public:
	static shared_ptr<CAnimation> Create(const aiAnimation* pAIAnimation, class CModel* pModel);
	shared_ptr<CAnimation> Clone();
};

NS_END