#include "Channel.h"
#include "Model.h"
#include "Bone.h"
HRESULT CChannel::Initialize(const aiNodeAnim* pAIChannel, shared_ptr<class CModel> pModel)
{
    strcpy_s(m_szName, pAIChannel->mNodeName.C_Str());
    
    m_iNumKeyFrames = max(pAIChannel->mNumScalingKeys,pAIChannel->mNumRotationKeys);
    m_iNumKeyFrames = max(m_iNumKeyFrames,pAIChannel->mNumPositionKeys);

    m_iBoneIndex = pModel->Get_BoneIndex(m_szName);
    if (-1 == m_iBoneIndex)
        return E_FAIL;

    float3_t vScale{};
    float4_t vRotation{};
    float3_t vPosition{};
    for (uint32_t i = 0; i < m_iNumKeyFrames; ++i)
    {
        KEYFRAME tKeyFrame{};

        if (i < pAIChannel->mNumScalingKeys)
        {
            tKeyFrame.fTrackPosition =(float)pAIChannel->mScalingKeys[i].mTime;
            memcpy(&vScale, &pAIChannel->mScalingKeys[i].mValue, sizeof(float3_t));
        }
        if (i < pAIChannel->mNumRotationKeys)
        {
            tKeyFrame.fTrackPosition = (float)pAIChannel->mRotationKeys[i].mTime;
            vRotation.x = pAIChannel->mRotationKeys[i].mValue.x;
            vRotation.y = pAIChannel->mRotationKeys[i].mValue.y;
            vRotation.z = pAIChannel->mRotationKeys[i].mValue.z;
            vRotation.w = pAIChannel->mRotationKeys[i].mValue.w;
        }
        if (i < pAIChannel->mNumPositionKeys)
        {
            tKeyFrame.fTrackPosition = (float)pAIChannel->mPositionKeys[i].mTime;
            memcpy(&vPosition, &pAIChannel->mPositionKeys[i].mValue, sizeof(float3_t));
        }
        tKeyFrame.vScale = vScale;
        tKeyFrame.vRotation = vRotation;
        tKeyFrame.vPosition = vPosition;

        m_KeyFrames.push_back(tKeyFrame);
    }

    return S_OK;
}

void CChannel::Update_TransformMatirx(const vector<shared_ptr<class CBone>>& Bones, uint32_t& pLeftKetFrameIndex, f32_t fCurrentTrackPos, const vector<BONE_SRT>* pPreSRT, f32_t fBlendRatio)
{
    vector_t vScale{}, vRotation{}, vPosition{};
    KEYFRAME    LastKeyFrame = m_KeyFrames.back();
    if (fCurrentTrackPos >= LastKeyFrame.fTrackPosition)
    {
        vScale = XMLoadFloat3(&LastKeyFrame.vScale);
        vRotation = XMLoadFloat4(&LastKeyFrame.vRotation);
        vPosition = XMVectorSetW(XMLoadFloat3(&LastKeyFrame.vPosition),1.f);
    }
    else
    {
        while (fCurrentTrackPos >= m_KeyFrames[pLeftKetFrameIndex + 1].fTrackPosition)
            ++pLeftKetFrameIndex;
        f32_t fRatio = (fCurrentTrackPos - m_KeyFrames[pLeftKetFrameIndex].fTrackPosition) /
            (m_KeyFrames[pLeftKetFrameIndex + 1].fTrackPosition - m_KeyFrames[pLeftKetFrameIndex].fTrackPosition);

        vector_t    vLeftScale, vRightScale;
        vector_t    vLeftRotation, vRightRotation;
        vector_t    vLeftPosition, vRightPosition;

        vLeftScale = XMLoadFloat3(&m_KeyFrames[pLeftKetFrameIndex].vScale);
        vLeftRotation = XMLoadFloat4(&m_KeyFrames[pLeftKetFrameIndex].vRotation);
        vLeftPosition = XMVectorSetW(XMLoadFloat3(&m_KeyFrames[pLeftKetFrameIndex].vPosition), 1.f);

        vRightScale = XMLoadFloat3(&m_KeyFrames[pLeftKetFrameIndex + 1].vScale);
        vRightRotation = XMLoadFloat4(&m_KeyFrames[pLeftKetFrameIndex + 1].vRotation);
        vRightPosition = XMVectorSetW(XMLoadFloat3(&m_KeyFrames[pLeftKetFrameIndex + 1].vPosition), 1.f);

        vScale = XMVectorLerp(vLeftScale, vRightScale, fRatio);
        vRotation = XMQuaternionSlerp(vLeftRotation, vRightRotation, fRatio);
        vPosition = XMVectorLerp(vLeftPosition, vRightPosition, fRatio);
    }

    if (nullptr != pPreSRT)
    {
        const BONE_SRT& tPreSRT = (*pPreSRT)[m_iBoneIndex];
        vScale = XMVectorLerp(XMLoadFloat3(&tPreSRT.vScale), vScale, fBlendRatio);
        vRotation = XMQuaternionSlerp(XMLoadFloat4(&tPreSRT.vRotation), vRotation, fBlendRatio);
        vPosition = XMVectorLerp(XMVectorSetW(XMLoadFloat3(&tPreSRT.vPosition), 1.f), vPosition, fBlendRatio);
    }
    Bones[m_iBoneIndex]->Set_TransfromMatrix(XMMatrixAffineTransformation(vScale, vector_t{ 0.f,0.f,0.f,1.f }, vRotation, vPosition));
}

shared_ptr<CChannel> CChannel::Create(const aiNodeAnim* pAIChannel, shared_ptr<class CModel> pModel)
{
    auto pInstance = shared_ptr<CChannel>(new CChannel());
    if (FAILED(pInstance->Initialize(pAIChannel, pModel)))
    {
        MSG_BOX("Failed to Create : CChannel");
        pInstance.reset();
    }
    return pInstance;
}
