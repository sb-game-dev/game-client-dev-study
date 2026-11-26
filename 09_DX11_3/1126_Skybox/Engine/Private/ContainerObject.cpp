#include "ContainerObject.h"

#include "GameInstance.h"
#include "PartObject.h"

CContainerObject::CContainerObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject { pDevice, pContext }
{
}   

HRESULT CContainerObject::Initialize_Prototype()
{
    if(FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CContainerObject::Initialize(void* pArg)
{  
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (nullptr == pArg)
        return S_OK;

    auto        pDesc = static_cast<CONTAINEROBJECT_DESC*>(pArg);

    return S_OK;
}

void CContainerObject::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);

    for (auto& Pair : m_PartObjects)
    {
        if(nullptr != Pair.second)
            Pair.second->Priority_Update(fTimeDelta);
    }
}

void CContainerObject::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

    for (auto& Pair : m_PartObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Update(fTimeDelta);
    }
}

void CContainerObject::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);

    for (auto& Pair : m_PartObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Late_Update(fTimeDelta);
    }
}

HRESULT CContainerObject::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CPartObject> CContainerObject::Find_PartObject(const wstring& strPartTag)
{
    auto    iter = m_PartObjects.find(strPartTag);
    if (iter == m_PartObjects.end())
        return nullptr;

    return iter->second;   
}

HRESULT CContainerObject::Add_PartObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, const wstring_t& strPartTag, void* pArg)
{
    if (nullptr != Find_PartObject(strPartTag))
        return E_FAIL;

    auto    pPartObject = dynamic_pointer_cast<CPartObject>(CGameInstance::Get().Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
    if (nullptr == pPartObject)
        return E_FAIL;

    m_PartObjects.emplace(strPartTag, pPartObject);

    return S_OK;
}

