#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "Bone.h"

CModel::CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CComponent{pDevice,pContext}
{
}

CModel::CModel(const CModel& rhs)
    : CComponent{rhs}
    , m_Meshes{rhs.m_Meshes}
    , m_iNumMeshes{rhs.m_iNumMeshes}
    , m_Materials{rhs.m_Materials}
    , m_iNumMaterials{rhs.m_iNumMaterials}
    , m_tLocalBox{rhs.m_tLocalBox}
    , m_bUseCulling{rhs.m_bUseCulling}
{
}

HRESULT CModel::Initialize_Prototype(MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix)
{
    m_eType = eType;

    uint32_t        iFlag = { aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast };

    if (MODEL::NONANIM == m_eType)
        iFlag |= aiProcess_PreTransformVertices;
    m_pAiScene = m_pImporter.ReadFile(pModelFilePath, iFlag);
	
    if (0 == m_pAiScene)
    {
        MSG_BOX("Faile to ReadFile");
        return E_FAIL;
    }
    if (FAILED(Ready_Meshes(eType, PreTransformMatrix)))
        return E_FAIL;
    if (FAILED(Ready_Materials(pModelFilePath)))
        return E_FAIL;
    if (FAILED(Ready_Bones(m_pAiScene->mRootNode, -1)))
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
    m_Materials[iMeterialIndex]->Bind_Pixel_ShaderResource(eType, iIndex, iSlot);
    return S_OK;
}

int32_t CModel::Get_BoneIndex(const char_t* pBoneName)
{
    int32_t iBoneIndex = {};
    auto iter = find_if(m_Bones.begin(), m_Bones.end(), [&](const auto& pBone)->bool_t {
        if (true == pBone->Compare_Name(pBoneName))
            return true;      // 찾았으면 멈춤 (iBoneIndex는 증가하지 않음)
        ++iBoneIndex;         // 못 찾았으면 다음 칸으로
        return false;
        });
    if (iter == m_Bones.end())
        return -1;
    return iBoneIndex;
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