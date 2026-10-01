#include "Prototype_Manager.h"

CPrototype_Manager::CPrototype_Manager()
{
}

HRESULT CPrototype_Manager::Initialize(uint32_t iNumLevels)
{
	m_iNumLevels = iNumLevels;
	m_pPrototypes = make_shared<PROTOTYPES[]>(iNumLevels);
	return S_OK;
}

HRESULT CPrototype_Manager::Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype)
{
	if (iLevelIndex >= m_iNumLevels ||
		nullptr != Find_Prototype(iLevelIndex, strPrototypeTag))
		return E_FAIL;

	m_pPrototypes[iLevelIndex].emplace(strPrototypeTag, pPrototype);
	return S_OK;
}

shared_ptr<CPrototype> CPrototype_Manager::Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg)
{
	return shared_ptr<CPrototype>();
}

void CPrototype_Manager::Clear(uint32_t iClearLevelIndex)
{
	if (iClearLevelIndex >= m_iNumLevels)
		return;
	m_pPrototypes[iClearLevelIndex].clear();
}

shared_ptr<CPrototype> CPrototype_Manager::Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag)
{
	auto Pair = m_pPrototypes[iLevelIndex].find(strPrototypeTag);

	if (Pair == m_pPrototypes[iLevelIndex].end())
		return nullptr;

	return Pair->second;
}



unique_ptr<CPrototype_Manager> CPrototype_Manager::Create(uint32_t iNumLevels)
{
	auto pInstance = unique_ptr<CPrototype_Manager> (new CPrototype_Manager());
	if (FAILED(pInstance->Initialize(iNumLevels)))
		pInstance.reset();
	return pInstance;
}
