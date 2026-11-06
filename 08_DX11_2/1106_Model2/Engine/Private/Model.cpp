#include "Model.h"
#include "Mesh.h"

CModel::CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CComponent { pDevice, pContext }
{
}

CModel::CModel(const CModel& Prototype)
    : CComponent { Prototype }
    , m_iNumMeshes { Prototype.m_iNumMeshes }
    , m_Meshes { Prototype.m_Meshes }
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

    return S_OK;
}

HRESULT CModel::Initialize(void* pArg)
{
    return S_OK;
}

HRESULT CModel::Render()
{
    for (auto& pMesh : m_Meshes)
    {
        if(nullptr != pMesh)
        {
            if (FAILED(pMesh->Bind_Resources()))
                return E_FAIL;

            if (FAILED(pMesh->Render()))
                return E_FAIL;
        }
    }

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