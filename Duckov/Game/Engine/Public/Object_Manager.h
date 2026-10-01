#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CGameObject;
class CObject_Manager
{
private:
	CObject_Manager();
public:
	~CObject_Manager() = default;

public:
	HRESULT	Initialize(uint32_t iNumLevels);
	HRESULT	Add_GameObject(uint32_t iPrototypeLevelIndex,const wstring_t& strPrototypeTag, void* pArg, 
						   uint32_t iLayerLevelIndex, const wstring_t& strLayerTag);

private:
	uint32_t	m_iNumLevels = {};
	typedef map<const wstring_t, shared_ptr<class CLayer>> LAYERS;
	shared_ptr<LAYERS[]> m_pLayers = {};
private:
	shared_ptr<class CLayer> Find_Layer(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag);
public:
	static unique_ptr<CObject_Manager> Create(uint32_t iNumLevels);
};
NS_END