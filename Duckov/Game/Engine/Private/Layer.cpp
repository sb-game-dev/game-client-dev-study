#include "Layer.h"
#include "GameObject.h"
#include "GameInstance.h"
CLayer::CLayer()
{

}

HRESULT CLayer::Add_GameObject(const wstring_t& strGameObjectTag, shared_ptr<class CGameObject> pGameObject)
{
    if (false == m_GameObjects.emplace(strGameObjectTag, pGameObject).second)
        return E_FAIL;
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
        if (nullptr != Pair.second && !Pair.second->Is_Dead())
            Pair.second->Update(fTimeDelta);
    }
}
void CLayer::Late_Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second && !Pair.second->Is_Dead())
        {
            Pair.second->Late_Update(fTimeDelta);
        }
    }
}
void CLayer::Remove_Dead()
{
    for (auto iter = m_GameObjects.begin(); iter != m_GameObjects.end(); )
    {
        if (nullptr == iter->second || iter->second->Is_Dead())
            iter = m_GameObjects.erase(iter);
        else
            ++iter;
    }
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
