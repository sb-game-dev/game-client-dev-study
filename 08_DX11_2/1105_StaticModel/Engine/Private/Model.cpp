#include "Model.h"

CModel::CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CComponent { pDevice, pContext }
{
}

HRESULT CModel::Initialize_Prototype(const char_t* pModelFilePath)
{
    uint32_t        iFlag = { aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast };

    m_pAIScene = m_Importer.ReadFile(pModelFilePath, iFlag);
    if (0 == m_pAIScene)
        return E_FAIL;

    if (FAILED(Ready_Meshes()))
        return E_FAIL;

    return S_OK;
}

HRESULT CModel::Initialize(void* pArg)
{
    return S_OK;
}

HRESULT CModel::Ready_Meshes()
{
    return E_NOTIMPL;
}

shared_ptr<CModel> CModel::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const char_t* pModelFilePath)
{
    auto pInstance = shared_ptr<CModel>(new CModel(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pModelFilePath)))
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