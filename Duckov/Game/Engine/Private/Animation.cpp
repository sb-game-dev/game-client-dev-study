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

void CAnimation::Update_TransformMatrix(const vector<shared_ptr<class CBone>>& Bones, f32_t fDeltaTime)
{
	m_fCurrentTrackPosition += m_fTickPerSecond * fDeltaTime;
	if (m_fCurrentTrackPosition >= m_fDuration)
	{
		if(m_bLoop)
			Reset_Animaition();
		else
			m_isFinished = true;
	}
	uint32_t iChannelIndex = {};
	for (auto& pChannel : m_Channels)
		pChannel->Update_TransformMatirx(Bones, m_LeftKeyFrameIndices[iChannelIndex++], m_fCurrentTrackPosition);
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
