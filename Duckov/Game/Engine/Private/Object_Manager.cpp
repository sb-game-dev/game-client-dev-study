#include "Object_Manager.h"
#include "Layer.h"
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

HRESULT CObject_Manager::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, 
										uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag, 
										void* pArg)
{
	// Prototype_Manager에 접근하여 Loader에서 생성한 원본을 가져다 복제본을 생성함
	auto pCopyGameObject = dynamic_pointer_cast<CGameObject>(CGameInstance::Get().Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
	if (nullptr == pCopyGameObject)
		return E_FAIL;

	// 생성한 복제본을 넣을 레이어를 검색
	auto pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);

	// 만약 레이어가 없다면 
	if (nullptr == pLayer)
	{
		// 레이어를 생성한다
		pLayer = CLayer::Create();
		// 생성한 레이어에 복제본을 추가
		pLayer->Add_GameObject(strGameObjectTag, pCopyGameObject);
		// 생성한 레이어를 Layers에 등록
		m_pLayers[iLayerLevelIndex].emplace(strLayerTag, pLayer);
	}
	// 레이어가 있다면 생성한 복제본을 레이어에 추가
	else
		pLayer->Add_GameObject(strGameObjectTag, pCopyGameObject);

	return S_OK;
}
void CObject_Manager::Priority_Update(f32_t fDeltaTime)
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Priority_Update(fDeltaTime);
		}
	}
}
void CObject_Manager::Update(f32_t fDeltaTime)
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Update(fDeltaTime);
		}
	}
}
void CObject_Manager::Late_Update(f32_t fDeltaTime)
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Late_Update(fDeltaTime);
		}
	}
}
HRESULT	CObject_Manager::Render()
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				if (FAILED(Pair.second->Render())) return E_FAIL;
		}
	}
	return S_OK;
}

void CObject_Manager::Clear(uint32_t iClearLevelIndex)
{
	if (iClearLevelIndex >= m_iNumLevels)
		return;
	m_pLayers[iClearLevelIndex].clear();
}

shared_ptr<CGameObject> CObject_Manager::Find_GameObject(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag)
{
	auto pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);
	if (nullptr == pLayer)
		return nullptr;

	auto pGameObject = pLayer->Find_GameObject(strGameObjectTag);
	if (nullptr == pGameObject)
		return nullptr;

	return pGameObject;
}

shared_ptr<CLayer> CObject_Manager::Find_Layer(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag)
{
	auto iter = m_pLayers[iLayerLevelIndex].find(strLayerTag);
	if (iter == m_pLayers[iLayerLevelIndex].end())
		return nullptr;
	return iter->second;
}

unique_ptr<CObject_Manager> CObject_Manager::Create(uint32_t iNumLevels)
{
	auto pInstance = unique_ptr<CObject_Manager>(new CObject_Manager());
	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX("Create Failed : CObject_Manager");
		pInstance.reset();
	}
	return pInstance;
}