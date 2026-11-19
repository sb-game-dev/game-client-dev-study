#include "Animation.h"
#include "Channel.h"
HRESULT CAnimation::Initialize(const aiAnimation* pAIAnimaiton, shared_ptr<class CModel> pModel)
{
	strcpy_s(m_szName, pAIAnimaiton->mName.C_Str());
	m_fDuration = (f32_t)pAIAnimaiton->mDuration;
	m_fTickPerSecond = (f32_t)pAIAnimaiton->mTicksPerSecond;

	m_iNumChannels = pAIAnimaiton->mNumChannels;
	for (uint32_t i = 0; i < m_iNumChannels; ++i)
	{
		auto pChannel = CChannel::Create(pAIAnimaiton->mChannels[i], pModel);
		if (nullptr == pChannel)
			return E_FAIL;
		m_Channels.push_back(pChannel);
	}
	m_LeftKeyFrameIndices.resize(m_iNumChannels);
	return S_OK;
}

void CAnimation::Update_TransformMatrix(const vector<shared_ptr<class CBone>>& Bones, f32_t fDeltaTime, const vector<bool_t>* pIsUpperBone, f32_t fAnimPlaySpeed)
{
	m_fCurrentTrackPosition += m_fTickPerSecond * fDeltaTime * fAnimPlaySpeed;
	if (m_fCurrentTrackPosition >= m_fDuration)
	{
		if(m_bLoop)
			Reset_Animaition();
		else
			m_isFinished = true;
	}
	for (uint32_t i = 0; i < m_iNumChannels; ++i)
	{
		// IsUpper벡터를 전달받았고 이 뼈가 하체인경우는 채널(뼈)을 갱신하지 않는다.
		if (nullptr != pIsUpperBone && false == (*pIsUpperBone)[m_Channels[i]->Get_BoneIndex()]) 
			continue;
		// isUpper 벡터를 전달 받지 못했다(하체를 그리는 경우다) -> 애니메이션이 들고있는 채널(뼈) 전체 갱신
		// isUpper 벡터를 전달 받았고 값이 true다 -> 상체 뼈이므로 Update
		m_Channels[i]->Update_TransformMatirx(Bones, m_LeftKeyFrameIndices[i], m_fCurrentTrackPosition);
	}
}

void CAnimation::Reset_Animaition()
{
	m_fCurrentTrackPosition = 0;
	m_isFinished = false;
	for (auto& LeftKeyFrameIndex : m_LeftKeyFrameIndices)
		LeftKeyFrameIndex = 0;
}

shared_ptr<CAnimation> CAnimation::Create(const aiAnimation* pAIAnimation, shared_ptr<class CModel> pModel)
{
	auto pInstance = shared_ptr<CAnimation>(new CAnimation());
	if (FAILED(pInstance->Initialize(pAIAnimation, pModel)))
	{
		MSG_BOX("Create to Failed : CAnimaition");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CAnimation> CAnimation::Clone()
{
	return shared_ptr<CAnimation>(new CAnimation(*this));
}
