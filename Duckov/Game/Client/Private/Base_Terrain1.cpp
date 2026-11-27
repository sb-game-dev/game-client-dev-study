#include "Base_Terrain1.h"

CBase_Terrain1::CBase_Terrain1(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{ pDevice,pContext }
{
}

HRESULT CBase_Terrain1::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
	return S_OK;
}

HRESULT CBase_Terrain1::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if(FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
	return S_OK;
}

void CBase_Terrain1::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CBase_Terrain1::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

void CBase_Terrain1::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::PRIORITY, static_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CBase_Terrain1::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    //if (FAILED(CGameInstance::Get().Bind_RasterizerState(g_strRS_Cull_Front)))
    //    return E_FAIL;

    if (FAILED(Bind_Shader()))
        return E_FAIL;
    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    uint32_t    iNumMeshes = m_pModelCom->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModelCom->Bind_BoneMatrix(i, 2)))
            return E_FAIL;
        if (FAILED(m_pModelCom->Bind_Material(i, ModelFile::TEXTURE_TYPE::DIFFUSE, 0, 0)))
            return E_FAIL;

        //if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_NORMALS, 0, 1)))
        //    return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }
    //if (FAILED(CGameInstance::Get().Bind_RasterizerState(g_strRS_Default)))
    //    return E_FAIL;
	return S_OK;
}

HRESULT CBase_Terrain1::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(m_iLevelIndex), Proto::Model_BaseTerrain1,
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_MODEL,
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;
	return S_OK;
}

HRESULT CBase_Terrain1::Ready_ConstantBuffer()
{
    XMStoreFloat4x4(&m_tCBData.mat_World, m_pTransformCom->Get_World());
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
	return S_OK;
}

HRESULT CBase_Terrain1::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;
    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CBase_Terrain1::Bind_ShaderResources()
{
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD), &m_tCBData)))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CBase_Terrain1> CBase_Terrain1::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CBase_Terrain1>(new CBase_Terrain1(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CBase_Terrain1");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CBase_Terrain1::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CBase_Terrain1>(new CBase_Terrain1(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CBase_Terrain1");
        pInstance.reset();
    }
    return pInstance;
}
