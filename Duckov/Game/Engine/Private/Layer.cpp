#include "Layer.h"
#include "GameObject.h"
CLayer::CLayer()
{

}

HRESULT CLayer::Add_GameObject(const wstring_t& strGameObjectTag, shared_ptr<class CGameObject> pGameObject)
{
    m_GameObjects.emplace(strGameObjectTag, pGameObject);

    return S_OK;
}

void CLayer::Priority_Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Priority_Update(fTimeDelta);
    }
}
void CLayer::Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Update(fTimeDelta);
    }
}
void CLayer::Late_Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Late_Update(fTimeDelta);
    }
}
HRESULT	CLayer::Render()
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            if (FAILED(Pair.second->Render()))return E_FAIL;
    }
    return S_OK;
}
shared_ptr<CGameObject> CLayer::Find_GameObject(const wstring_t& strGameObjectTag)
{
    auto iter = m_GameObjects.find(strGameObjectTag);
    if (iter == m_GameObjects.end())
        return nullptr;
    return iter->second;
}
shared_ptr<CLayer>	CLayer::Create()
{
    return shared_ptr<CLayer>(new CLayer());
}
