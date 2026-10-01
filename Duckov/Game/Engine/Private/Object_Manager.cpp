#include "Object_Manager.h"
#include "Layer.h"
HRESULT CObject_Manager::Initialize(uint32_t iNumLevels)
{
	m_iNumLevels = iNumLevels;
	m_pLayers = make_shared<LAYERS[]>(iNumLevels);
	return S_OK;
}

HRESULT CObject_Manager::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, void* pArg, uint32_t iLayerLevelIndex, const wstring_t& strLayerTag)
{
	return E_NOTIMPL;
}
shared_ptr<CLayer> CObject_Manager::Find_Layer(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag)
{
	auto iter = m_pLayers[iLayerLevelIndex].find(strLayerTag);
	if (iter == m_pLayers[iLayerLevelIndex].end())
		return nullptr;
	return iter->second;
}