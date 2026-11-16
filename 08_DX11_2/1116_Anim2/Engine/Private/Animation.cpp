#include "Animation.h"
#include "Channel.h"

CAnimation::CAnimation()
{
}

HRESULT CAnimation::Initialize(const aiAnimation* pAIAnimation, class CModel* pModel)
{
    strcpy_s(m_szName, pAIAnimation->mName.C_Str());
    m_fDuration = pAIAnimation->mDuration;
    m_fTickPerSecond = pAIAnimation->mTicksPerSecond;

    m_iNumChannels = pAIAnimation->mNumChannels;

    for (uint32_t i = 0; i < m_iNumChannels; i++)
    {
        auto        pChannel = CChannel::Create(pAIAnimation->mChannels[i], pModel);
        if (nullptr == pChannel)
            return E_FAIL;

        m_Channels.push_back(pChannel);
    }

    return S_OK;
}

void CAnimation::Update_TransformationMatrix(const vector<shared_ptr<class CBone>>& Bones, f32_t fTimeDelta)
{
    /*현재 트랙내에서의 재생위치를 구한다. */
    m_fCurrentTrackPosition += m_fTickPerSecond * fTimeDelta;

    if (m_fCurrentTrackPosition >= m_fDuration)
    {

    }

    for (auto& pChannel : m_Channels)
    {
        pChannel->Update_TransformationMatrix(Bones, m_fCurrentTrackPosition);
    }


}

shared_ptr<CAnimation> CAnimation::Create(const aiAnimation* pAIAnimation, class CModel* pModel)
{
    auto pInstance = shared_ptr<CAnimation>(new CAnimation());

    if (FAILED(pInstance->Initialize(pAIAnimation, pModel)))
    {
        MSG_BOX("Failed to Created : CAnimation");
        pInstance.reset();
    }

    return pInstance;
}

