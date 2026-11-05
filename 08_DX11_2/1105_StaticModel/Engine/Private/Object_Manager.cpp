#include "Object_Manager.h"
#include "Layer.h"

#include "GameObject.h"

#include "GameInstance.h"

CObject_Manager::CObject_Manager()
{
}

HRESULT CObject_Manager::Initialize(uint32_t iNumLevels)
{
    m_iNumLevels = iNumLevels;

    m_pLayers = make_shared<LAYERS[]>(iNumLevels);

    return S_OK;
}

HRESULT CObject_Manager::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, void* pArg)
{
    /*원형을 복제해서 사본객체를 만든ㄷ닫 .*/
    auto    pGameObject = dynamic_pointer_cast<CGameObject>(CGameInstance::Get().Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
    if (nullptr == pGameObject)
        return E_FAIL;   

    /* 사본객체를 집어넣기위한 레이어를 검색해준다. */
    auto    pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);

    /* 집어넣기위한 레이어가 없네>? */
    if (nullptr == pLayer)
    {
        /* 없으면 만든다.*/
        pLayer = CLayer::Create();

        pLayer->Add_GameObject(pGameObject);

        /* 새롭게 만든 레이어를 맵에 등록한다.*/
        m_pLayers[iLayerLevelIndex].emplace(strLayerTag, pLayer);
    }
    else
        pLayer->Add_GameObject(pGameObject);

    return S_OK;
}

void CObject_Manager::Priority_Update(f32_t fTimeDelta)
{
    for (uint32_t i = 0; i < m_iNumLevels; i++)
    {
        for (auto& Pair : m_pLayers[i])
        {
            if (nullptr != Pair.second)
                Pair.second->Priority_Update(fTimeDelta);
        }
    }
}

void CObject_Manager::Update(f32_t fTimeDelta)
{
    for (uint32_t i = 0; i < m_iNumLevels; i++)
    {
        for (auto& Pair : m_pLayers[i])
        {
            if (nullptr != Pair.second)
                Pair.second->Update(fTimeDelta);
        }
    }
}

void CObject_Manager::Late_Update(f32_t fTimeDelta)
{
    for (uint32_t i = 0; i < m_iNumLevels; i++)
    {
        for (auto& Pair : m_pLayers[i])
        {
            if (nullptr != Pair.second)
                Pair.second->Late_Update(fTimeDelta);
        }
    }
}

void CObject_Manager::Clear(uint32_t iClearLevelIndex)
{
    if (iClearLevelIndex >= m_iNumLevels)
        return;


    m_pLayers[iClearLevelIndex].clear();

}

shared_ptr<class CLayer> CObject_Manager::Find_Layer(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag)
{
    auto    iter = m_pLayers[iLayerLevelIndex].find(strLayerTag);
    if (iter == m_pLayers[iLayerLevelIndex].end())
        return nullptr;

    return iter->second;
}

unique_ptr<CObject_Manager> CObject_Manager::Create(uint32_t iNumLevels)
{
    auto pInstance = unique_ptr<CObject_Manager>(new CObject_Manager());

    if (FAILED(pInstance->Initialize(iNumLevels)))
    {
        MSG_BOX("Failed to Created : CObject_Manager");
        pInstance.reset();
    }

    return pInstance;
}

