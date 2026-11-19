#pragma once

#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CChannel final
{
private:
	CChannel() = default;
public:
	~CChannel() = default;

public:
	HRESULT	Initialize(const aiNodeAnim* pAIChannel, shared_ptr<class CModel> pModel);
	void	Update_TransformMatirx(const vector<shared_ptr<class CBone>>& Bones, uint32_t& pLeftKetFrameIndex, f32_t fCurrentTrackPos, const vector<BONE_SRT>* pPreSRT, f32_t fBlendRatio);
	int32_t	Get_BoneIndex() { return m_iBoneIndex; }
private:
	char_t				m_szName[MAX_PATH] = {};
	int32_t				m_iBoneIndex = {};

	vector<KEYFRAME>	m_KeyFrames;
	uint32_t			m_iNumKeyFrames = {};
	
	uint32_t			m_iLeftKeyFrameIndex = {};


public:
	static shared_ptr<CChannel> Create(const aiNodeAnim* pAIChannel, shared_ptr<class CModel> pModel);
};

NS_END