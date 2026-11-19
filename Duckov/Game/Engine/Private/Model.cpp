#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "Bone.h"
#include "Animation.h"

CModel::CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CComponent{pDevice,pContext}
{
}

CModel::CModel(const CModel& rhs)
    : CComponent{rhs}
    , m_eType{rhs.m_eType}
    , m_Meshes{rhs.m_Meshes}
    , m_iNumMeshes{rhs.m_iNumMeshes}
    , m_PreTransformMatrix{ rhs.m_PreTransformMatrix}

    , m_Materials{rhs.m_Materials}
    , m_iNumMaterials{rhs.m_iNumMaterials}
    
    , m_iNumAnimaition{rhs.m_iNumAnimaition}
    , m_fAnimPlaySpeed{rhs.m_fAnimPlaySpeed}
    , m_IsUpperBone{rhs.m_IsUpperBone}
    , m_tLowerLayer{rhs.m_tLowerLayer}
    , m_tUpperLayer{rhs.m_tUpperLayer}

    , m_tLocalBox{rhs.m_tLocalBox}
    , m_bUseCulling{rhs.m_bUseCulling}
{
    for (auto& pBone : rhs.m_Bones)
        m_Bones.push_back(pBone->Clone());

    for (auto& pAnimation : rhs.m_Animations)
        m_Animations.push_back(pAnimation->Clone());

}

HRESULT CModel::Initialize_Prototype(MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix)
{
    m_eType = eType;

    XMStoreFloat4x4(&m_PreTransformMatrix, PreTransformMatrix);
    // bin파일 읽기
    char_t szExt[MAX_PATH] = {};
    _splitpath_s(pModelFilePath, nullptr, 0, nullptr, 0, nullptr, 0, szExt, MAX_PATH);
    if (0 == strcmp(szExt, ".bin"))
        return Load_Binary(pModelFilePath, PreTransformMatrix);

    //Assimp 사용
    uint32_t        iFlag = { aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast };

    if (MODEL::NONANIM == m_eType)
        iFlag |= aiProcess_PreTransformVertices;
    m_pAiScene = m_pImporter.ReadFile(pModelFilePath, iFlag);
	
    if (0 == m_pAiScene)
    {
        MSG_BOX("Faile to ReadFile");
        return E_FAIL;
    }
    
    if (FAILED(Ready_Bones(m_pAiScene->mRootNode, -1, false)))
        return E_FAIL;
    if (FAILED(Ready_Meshes(eType, PreTransformMatrix)))
        return E_FAIL;
    if (FAILED(Ready_Materials(pModelFilePath)))
        return E_FAIL;
    if (FAILED(Ready_Animation()))
        return E_FAIL;

    return S_OK;
}

HRESULT CModel::Initialize(void* pArg)
{

	return S_OK;
}

HRESULT CModel::Render(uint32_t iMeshIndex)
{
    if (FAILED(m_Meshes[iMeshIndex]->Bind_Resources()))
        return E_FAIL;
    
    if (FAILED(m_Meshes[iMeshIndex]->Render()))
        return E_FAIL;
    return S_OK;
}

HRESULT CModel::Render_Instanced(uint32_t iMeshIndex, ID3D11Buffer* pInstanceVB, uint32_t iInstanceStride, uint32_t iNumInstances)
{
    if (FAILED(m_Meshes[iMeshIndex]->Render_Instanced(pInstanceVB,iInstanceStride,iNumInstances)))
        return E_FAIL;
    return S_OK;
}

HRESULT CModel::Bind_Material(uint32_t iMeshIndex, aiTextureType eType, uint32_t iIndex, uint32_t iSlot)
{
    uint32_t    iMeterialIndex = m_Meshes[iMeshIndex]->Get_MaterialIndex();
    if (iMeterialIndex >= m_Materials.size())
        return S_OK;

    m_Materials[iMeterialIndex]->Bind_Pixel_ShaderResource(eType, iIndex, iSlot);
    return S_OK;
}

HRESULT CModel::Bind_BoneMatrix(uint32_t iMeshIndex, uint32_t iSlot)
{
    return m_Meshes[iMeshIndex]->Bind_BoneMatrix(m_Bones, iSlot);
}

int32_t CModel::Get_BoneIndex(const char_t* pBoneName)
{
    //int32_t iBoneIndex = {};
    //auto iter = find_if(m_Bones.begin(), m_Bones.end(), [&](const auto& pBone)->bool_t {
    //    if (true == pBone->Compare_Name(pBoneName))
    //        return true;      // 찾았으면 멈춤 (iBoneIndex는 증가하지 않음)
    //    ++iBoneIndex;         // 못 찾았으면 다음 칸으로
    //    return false;
    //    });
    //if (iter == m_Bones.end())
    //    return -1;
    //return iBoneIndex;
    for (size_t i = 0; i < m_Bones.size(); ++i)
    {
        if (true == m_Bones[i]->Compare_Name(pBoneName))
            return static_cast<int32_t>(i);
    }
    return -1;
}

void CModel::PlayAnimation(f32_t fDeltaTime)
{
    // ------ 뼈들을 현재 애니메이션에 맞게 셋팅한다. ------

    /* 1. 뼈들의 TransformMatrix 행렬을 현재 애니메이션에 맞게 세팅한다. */
    
    // 하체는 뼈 전체를 갱신한다.(상체뼈 하체뼈 구분하지 않는다.)
    m_Animations[m_tLowerLayer.iAnimIndex]->Update_TransformMatrix(m_Bones, fDeltaTime);

    // 상체를 바꿔야 한다면 상체는 따로 갱신 + 하체와 상체의 애니메이션이 같다면 상체의 뼈는 갱신하지 않는다.(애니메이션이 두 번 재생됨)
    if (m_tUpperLayer.isActive && m_tUpperLayer.iAnimIndex != m_tLowerLayer.iAnimIndex)
        m_Animations[m_tUpperLayer.iAnimIndex]->Update_TransformMatrix(m_Bones, fDeltaTime, &m_IsUpperBone);
     
    /* 2. TransformMatrix 행렬과 부모 CombinedMatrix를 곱해서 나의 CombinedMatrix를 만든다.*/
    for (auto& pBone : m_Bones)
        pBone->Update_CombinedTranformMatrix(m_Bones, XMLoadFloat4x4(&m_PreTransformMatrix));
}

void CModel::Set_LowerAnimationIndex(uint32_t iAnimIndex)
{
    if (iAnimIndex >= m_iNumAnimaition)
        return;

    if (m_tLowerLayer.iAnimIndex != iAnimIndex)
    {
        m_Animations[iAnimIndex]->Reset_Animaition();
        m_tLowerLayer.iAnimIndex = iAnimIndex;
    }
}
void CModel::Set_UpperAnimationIndex(uint32_t iAnimIndex, bool_t bActive)
{
    if (iAnimIndex >= m_iNumAnimaition)
        return;

    if (m_tUpperLayer.iAnimIndex != iAnimIndex)
    {
        m_Animations[iAnimIndex]->Reset_Animaition();
        m_tUpperLayer.iAnimIndex = iAnimIndex;
        m_tUpperLayer.isActive = bActive;
    }
}
void CModel::Reset_BoneTransformMatrix()
{
    for (auto& pBone : m_Bones)
        pBone->Reset_TransformMatrix();
}
void CModel::Set_Animation_Loop(uint32_t iAnimationIndex)
{
    if (iAnimationIndex >= m_iNumAnimaition)
        return;
    m_Animations[iAnimationIndex]->Set_Loop();
}


bool_t CModel::Is_Animation_Finished(bool_t bUpper)
{
    if (bUpper) 
        return m_Animations[m_tUpperLayer.iAnimIndex]->Is_Animation_End();
    return m_Animations[m_tLowerLayer.iAnimIndex]->Is_Animation_End();
}

HRESULT CModel::Ready_Meshes(MODEL eType, fmatrix_t PreTransformMatrix)
{
    m_iNumMeshes = m_pAiScene->mNumMeshes;
    bool_t bFirst = true;

    for (uint32_t i = 0; i < m_iNumMeshes; ++i)
    {
        auto pMesh = CMesh::Create(m_pDevice, m_pContext, eType, dynamic_pointer_cast<CModel>(shared_from_this()), m_pAiScene->mMeshes[i], PreTransformMatrix);
        if (nullptr == pMesh)
            return E_FAIL;
        if (bFirst) 
        {   
            m_tLocalBox = pMesh->GetBoundinBox(); 
            bFirst = false; 
        }
        else          
            BoundingBox::CreateMerged(m_tLocalBox, m_tLocalBox, pMesh->GetBoundinBox());
        m_Meshes.push_back(pMesh);
    }
    m_bUseCulling = true;
    return S_OK;
}

HRESULT CModel::Ready_Materials(const char_t* pModelFilePath)
{
    m_iNumMaterials = m_pAiScene->mNumMaterials;
    for (uint32_t i = 0; i < m_iNumMaterials; ++i)
    {
        auto pMaterial = CMaterial::Create(m_pDevice, m_pContext, pModelFilePath, m_pAiScene->mMaterials[i]);
        if (nullptr == pMaterial)
            return E_FAIL;
        m_Materials.push_back(pMaterial);
    }
    return S_OK;
}

HRESULT CModel::Ready_Bones(const aiNode* pAINode, int32_t iPIndex)
{
    auto pBone = CBone::Create(pAINode, iPIndex);
    if (nullptr == pBone)
        return E_FAIL;
    m_Bones.push_back(pBone);

    int32_t iParentIndex = { int32_t(m_Bones.size()) - 1 };
    for (uint32_t i = 0; i < pAINode->mNumChildren; ++i)
    {
        Ready_Bones(pAINode->mChildren[i], iParentIndex);
    }
    return S_OK;
}

HRESULT CModel::Ready_Bones(const aiNode* pAINode, int32_t iParentIndex, bool_t isUpper)
{
    auto pBone = CBone::Create(pAINode, iParentIndex);
    if (nullptr == pBone)
        return E_FAIL;
    if (!isUpper && nullptr != strstr(pAINode->mName.C_Str(), "Spine")) // 전체 문자열, 찾을 문자열
        isUpper = true;
    
    m_Bones.push_back(pBone);
    m_IsUpperBone.push_back(isUpper);

    int32_t iPIndex = { int32_t(m_Bones.size()) - 1 };
    for (uint32_t i = 0; i < pAINode->mNumChildren; ++i)
    {
        Ready_Bones(pAINode->mChildren[i], iPIndex, isUpper);
    }

    return S_OK;
}

HRESULT CModel::Ready_Animation()
{
    m_iNumAnimaition = m_pAiScene->mNumAnimations;
    for (uint32_t i = 0; i < m_iNumAnimaition; ++i)
    {
        auto pAnimaition = CAnimation::Create(m_pAiScene->mAnimations[i], dynamic_pointer_cast<CModel>(shared_from_this()));
        if (nullptr == pAnimaition)
            return E_FAIL;
        m_Animations.push_back(pAnimaition);
    }
    return S_OK;
}

HRESULT CModel::Load_Binary(const char_t* pModelFilePath, fmatrix_t PreTransformMatrix)
{
    wchar_t szWidePath[MAX_PATH] = {};
    MultiByteToWideChar(CP_ACP, 0, pModelFilePath, -1, szWidePath, MAX_PATH);

    FILE* pFile = { nullptr };
    if (0 != _wfopen_s(&pFile, szWidePath, L"rb") || nullptr == pFile)
    {
        MSG_BOX("Failed to Open : Binary Model");
        return E_FAIL;
    }

    if (FAILED(Read_Header(pFile)))
        return E_FAIL;
    if (FAILED(Read_Meshes(pFile, PreTransformMatrix)))
        return E_FAIL;
    if (FAILED(Read_Materials(pFile, pModelFilePath)))
        return E_FAIL;
    fclose(pFile);
    return S_OK;
}

HRESULT CModel::Read_Header(FILE* pFile)
{
    char_t szMagic[4] = {};
    uint32_t iVersion = {};
    uint32_t iType = {};

    if (1 != fread(szMagic, sizeof(szMagic), 1, pFile) ||
        1 != fread(&iVersion, sizeof(uint32_t), 1, pFile) ||
        1 != fread(&iType, sizeof(uint32_t), 1, pFile))
        return E_FAIL;
    return S_OK;
}

HRESULT CModel::Read_Meshes(FILE* pFile, fmatrix_t PreTransformMatrix)
{
    if (1 != fread(&m_iNumMeshes, sizeof(uint32_t), 1, pFile))
    {
        MSG_BOX("Failed to Read : NumMeshes");
        return E_FAIL;
    }
    bool_t bFirst = true;
    for (uint32_t i = 0; i < m_iNumMeshes; ++i)
    {
        auto pMesh = CMesh::Create(m_pDevice, m_pContext, pFile, PreTransformMatrix);
        if (nullptr == pMesh)
            return E_FAIL;

        if (bFirst)
        {
            m_tLocalBox = pMesh->GetBoundinBox();
            bFirst = false;
        }
        else
            BoundingBox::CreateMerged(m_tLocalBox, m_tLocalBox, pMesh->GetBoundinBox());

        m_Meshes.push_back(pMesh);
    }
    m_bUseCulling = true;
    return S_OK;
}

HRESULT CModel::Read_Materials(FILE* pFile, const char_t* pModelFilePath)
{
    fread(&m_iNumMaterials, sizeof(uint32_t), 1, pFile); 

    for (uint32_t i = 0; i < m_iNumMaterials; ++i)
    {
        auto pMaterial = CMaterial::Create(m_pDevice, m_pContext, pModelFilePath, pFile);
        if (nullptr == pMaterial)
            return E_FAIL;
        m_Materials.push_back(pMaterial);
    }
    return S_OK;
}

shared_ptr<CModel> CModel::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix)
{
    auto pInstance = shared_ptr<CModel>(new CModel(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(eType, pModelFilePath, PreTransformMatrix)))
    {
        MSG_BOX("Failed to Created : CModel");
        pInstance.reset();
    }
    return pInstance;
}
shared_ptr<CPrototype> CModel::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CModel>(new CModel(*this));
    
    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CModel");
        pInstance.reset();
    }
    return pInstance;
}