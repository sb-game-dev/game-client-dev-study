#pragma once
#include "Engine_Defines.h"

/* 이 애니메이션의 전체 길이, 속도등의 정보를 관리한다. */
/* 이 애니메이션에서 사용해야할 뼈들의 정보를 보관한다. */

NS_BEGIN(Engine)
class CAnimation final
{
private:
	CAnimation() = default;
public:
	~CAnimation() = default;
public:
	HRESULT		Initialize(const aiAnimation* pAIAnimaiton, shared_ptr<class CModel> pModel);
	void		Update_TransformMatrix(const vector<shared_ptr<class CBone>>& Bones, 
									   f32_t fDeltaTime, 
									   const vector<bool_t>* pIsUpperBone = nullptr, 
									   f32_t fAnimPlaySpeed = 1.f, 
									   const vector<BONE_SRT>* pPreSRT = nullptr, 
									   f32_t fBlendRatio = 1.f);

	void		Reset_Animaition();
	bool_t		Is_Animation_End() const { return m_isFinished; }
	void		Set_Loop() { m_bLoop = true; }
private:
	/* 이 애니메이션의 전체 길이, 속도등의 정보를 관리한다. */
	char_t		m_szName[MAX_PATH] = { "" };
	f32_t		m_fDuration = {};
	f32_t		m_fTickPerSecond = {};
	f32_t		m_fCurrentTrackPosition = {};

	/* 이 애니메이션에서 사용해야할 뼈들의 정보를 보관한다. */
	uint32_t							m_iNumChannels = {};
	vector<shared_ptr<class CChannel>>	m_Channels;
	vector<uint32_t>					m_LeftKeyFrameIndices;

	bool_t		m_bLoop = { false };
	bool_t		m_isFinished = { true };

public:
	static shared_ptr<CAnimation> Create(const aiAnimation* pAIAnimation, shared_ptr<class CModel> pModel);
	shared_ptr<CAnimation> Clone();
};

NS_END