#include "Channel.h"
#include "Model.h"
#include "Bone.h"

CChannel::CChannel()
{
}

HRESULT CChannel::Initialize(const aiNodeAnim* pAIChannel, class CModel* pModel)
{
    strcpy_s(m_szName, pAIChannel->mNodeName.C_Str());

    m_iBoneIndex = pModel->Get_BoneIndex(m_szName);
    if (-1 == m_iBoneIndex)
        return E_FAIL;

    m_iNumKeyFrames = max(pAIChannel->mNumScalingKeys, pAIChannel->mNumRotationKeys);
    m_iNumKeyFrames = max(m_iNumKeyFrames, pAIChannel->mNumPositionKeys);

    float3_t        vScale{};
    float4_t        vRotation{};
    float3_t        vPosition{};

    for (uint32_t i = 0; i < m_iNumKeyFrames; i++)
    {
        KEYFRAME            KeyFrame{};

        if(i < pAIChannel->mNumScalingKeys)
        {
            KeyFrame.fTrackPosition = pAIChannel->mScalingKeys[i].mTime;
           memcpy(&vScale, &pAIChannel->mScalingKeys[i].mValue, sizeof(float3_t));
        }

        if (i < pAIChannel->mNumRotationKeys)
        {
            KeyFrame.fTrackPosition = pAIChannel->mRotationKeys[i].mTime;
            vRotation.x = pAIChannel->mRotationKeys[i].mValue.x;
            vRotation.y = pAIChannel->mRotationKeys[i].mValue.y;
            vRotation.z = pAIChannel->mRotationKeys[i].mValue.z;
            vRotation.w = pAIChannel->mRotationKeys[i].mValue.w;            
        }

        if (i < pAIChannel->mNumPositionKeys)
        {
            KeyFrame.fTrackPosition = pAIChannel->mPositionKeys[i].mTime;
            memcpy(&vPosition, &pAIChannel->mPositionKeys[i].mValue, sizeof(float3_t));
        }

        KeyFrame.vScale = vScale;
        KeyFrame.vRotation = vRotation;
        KeyFrame.vPosition = vPosition;

        m_KeyFrames.push_back(KeyFrame);
    }

	return S_OK;
}

void CChannel::Update_TransformationMatrix(const vector<shared_ptr<class CBone>>& Bones, uint32_t* pLeftKeyFrameIndex, f32_t fCurrentTrackPosition)
{
    if (0.f == fCurrentTrackPosition)
        *pLeftKeyFrameIndex = 0;

    vector_t        vScale{}, vRotation{}, vTranslation{};

    KEYFRAME        LastKeyFrame = m_KeyFrames.back();

    if (fCurrentTrackPosition >= LastKeyFrame.fTrackPosition)
    {
        vScale = XMLoadFloat3(&LastKeyFrame.vScale);
        vRotation = XMLoadFloat4(&LastKeyFrame.vRotation);
        vTranslation = XMVectorSetW(XMLoadFloat3(&LastKeyFrame.vPosition), 1.f);
    }
    else /* 선형보간이 필요한 경우 */
    {
        while (fCurrentTrackPosition >= m_KeyFrames[*pLeftKeyFrameIndex + 1].fTrackPosition)
            ++*pLeftKeyFrameIndex;  

        f32_t       fRatio = (fCurrentTrackPosition - m_KeyFrames[*pLeftKeyFrameIndex].fTrackPosition) / 
            (m_KeyFrames[*pLeftKeyFrameIndex + 1].fTrackPosition - m_KeyFrames[*pLeftKeyFrameIndex].fTrackPosition);

        vector_t    vLeftScale, vRightScale;
        vector_t    vLeftRot, vRightRot;
        vector_t    vLeftPos, vRightPos;

        vLeftScale = XMLoadFloat3(&m_KeyFrames[*pLeftKeyFrameIndex].vScale);
        vLeftRot = XMLoadFloat4(&m_KeyFrames[*pLeftKeyFrameIndex].vRotation);
        vLeftPos = XMVectorSetW(XMLoadFloat3(&m_KeyFrames[*pLeftKeyFrameIndex].vPosition), 1.f);

        vRightScale = XMLoadFloat3(&m_KeyFrames[*pLeftKeyFrameIndex + 1].vScale);
        vRightRot = XMLoadFloat4(&m_KeyFrames[*pLeftKeyFrameIndex + 1].vRotation);
        vRightPos = XMVectorSetW(XMLoadFloat3(&m_KeyFrames[*pLeftKeyFrameIndex + 1].vPosition), 1.f);

        vScale = XMVectorLerp(vLeftScale, vRightScale, fRatio);
        vRotation = XMQuaternionSlerp(vLeftRot, vRightRot, fRatio);
        vTranslation = XMVectorLerp(vLeftPos, vRightPos, fRatio);
    }

    Bones[m_iBoneIndex]->Set_TransformationMatrix(
        XMMatrixAffineTransformation(
            vScale, 
            XMVectorSet(0.f, 0.f, 0.f, 1.f), 
            vRotation, 
            vTranslation
        ));
    
}

shared_ptr<CChannel> CChannel::Create(const aiNodeAnim* pAIChannel, class CModel* pModel)
{
    auto pInstance = shared_ptr<CChannel>(new CChannel());

    if (FAILED(pInstance->Initialize(pAIChannel, pModel)))
    {
        MSG_BOX("Failed to Created : CChannel");
        pInstance.reset();
    }

    return pInstance;
}

