#include "Layer.h"

#include "GameObject.h"

CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(shared_ptr<CGameObject> pGameObject)
{
    m_GameObjects.push_back(pGameObject);

    return S_OK;
}

void CLayer::Priority_Update(f32_t fTimeDelta)
{
    for (auto& pGameObject : m_GameObjects)
    {
        if(nullptr != pGameObject)
            pGameObject->Priority_Update(fTimeDelta);
    }
}

void CLayer::Update(f32_t fTimeDelta)
{
    for (auto& pGameObject : m_GameObjects)
    {
        if (nullptr != pGameObject)
            pGameObject->Update(fTimeDelta);
    }
}

void CLayer::Late_Update(f32_t fTimeDelta)
{
    for (auto& pGameObject : m_GameObjects)
    {
        if (nullptr != pGameObject)
            pGameObject->Late_Update(fTimeDelta);
    }
}

shared_ptr<CLayer> CLayer::Create()
{
    return shared_ptr<CLayer>(new CLayer());
}
