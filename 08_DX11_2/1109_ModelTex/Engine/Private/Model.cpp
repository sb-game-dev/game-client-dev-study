#include "Model.h"
#include "Mesh.h"
#include "Material.h"

CModel::CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CComponent { pDevice, pContext }
{
}

CModel::CModel(const CModel& Prototype)
    : CComponent { Prototype }
    , m_iNumMeshes { Prototype.m_iNumMeshes }
    , m_Meshes { Prototype.m_Meshes }
    , m_iNumMaterials { Prototype.m_iNumMaterials }
    , m_Materials { Prototype.m_Materials }   
{

}

HRESULT CModel::Initialize_Prototype(const char_t* pModelFilePath, fmatrix_t PreTransformMatrix)
{
    uint32_t        iFlag = { aiProcess_PreTransformVertices | aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast };

    m_pAIScene = m_Importer.ReadFile(pModelFilePath, iFlag);
    if (0 == m_pAIScene)
        return E_FAIL;

    if (FAILED(Ready_Meshes(PreTransformMatrix)))
        return E_FAIL;

    if (FAILED(Ready_Materials(pModelFilePath)))
        return E_FAIL;



    return S_OK;
}

HRESULT CModel::Initialize(void* pArg)
{
    return S_OK;
}

HRESULT CModel::Bind_Material(uint32_t iMeshIndex, aiTextureType eType, uint32_t iIndex, uint32_t iSlot)
{
    uint32_t        iMaterialIndex = m_Meshes[iMeshIndex]->Get_MaterialIndex();

    if (iMaterialIndex >= m_iNumMaterials)
        return E_FAIL;

    return m_Materials[iMaterialIndex]->Bind_Pixel_ShaderResource(eType, iIndex, iSlot);

}

HRESULT CModel::Render(uint32_t iMeshIndex)
{
    if (iMeshIndex >= m_iNumMeshes)
        return E_FAIL;

    m_Meshes[iMeshIndex]->Bind_Resources();
    m_Meshes[iMeshIndex]->Render();        

    return S_OK;
}

HRESULT CModel::Ready_Meshes(fmatrix_t PreTransformMatrix)
{
    m_iNumMeshes = m_pAIScene->mNumMeshes;

    for (uint32_t i = 0; i < m_iNumMeshes; i++)
    {
        auto    pMesh = CMesh::Create(m_pDevice, m_pContext, m_pAIScene->mMeshes[i], PreTransformMatrix);
        if (nullptr == pMesh)
            return E_FAIL;

        m_Meshes.push_back(pMesh);
    }   

    return S_OK;
}

HRESULT CModel::Ready_Materials(const char_t* pModelFilePath)
{
    m_iNumMaterials = m_pAIScene->mNumMaterials;

    for (uint32_t i = 0; i < m_iNumMaterials; i++)
    {
        auto    pMaterial = CMaterial::Create(m_pDevice, m_pContext, pModelFilePath, m_pAIScene->mMaterials[i]);
        if (nullptr == pMaterial)
            return E_FAIL;

        m_Materials.push_back(pMaterial);
    }

    return S_OK;
}

shared_ptr<CModel> CModel::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix)
{
    auto pInstance = shared_ptr<CModel>(new CModel(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pModelFilePath, PreTransformMatrix)))
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