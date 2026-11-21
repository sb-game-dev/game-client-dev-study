#include "Channel.h"
#include "Model.h"
#include "Bone.h"

HRESULT CChannel::Initialize(FILE* pFile)
{
    fread(&m_iBoneIndex, sizeof(int32_t), 1, pFile);
    fread(&m_iNumKeyFrames, sizeof(uint32_t), 1, pFile);
    m_KeyFrames.resize(m_iNumKeyFrames);
    fread(m_KeyFrames.data(), sizeof(KEYFRAME), m_iNumKeyFrames, pFile);
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

shared_ptr<CChannel> CChannel::Create(FILE* pFile)
{
    auto pInstance = shared_ptr<CChannel>(new CChannel());
    if (FAILED(pInstance->Initialize(pFile)))
    {
        MSG_BOX("Failed to Create : CChannel");
        pInstance.reset();
    }
    return pInstance;
}