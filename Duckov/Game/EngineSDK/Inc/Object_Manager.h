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
	/* iPrototypeLevelIndex에 추가되어있는 strPrototypeTag원형을 찾아서 pArg를 넣어서 복제하여 사본을 만들고*/
	/* iLayerLevelIndex에 추가되어있는 strLayerTag레이어를 찾아서 사본을 추가*/
	HRESULT	Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, 
						   uint32_t iLayerLevelIndex,	  const wstring_t& strLayerTag, const wstring_t& strGameObjectTag, void* pArg = nullptr);
	
	void		Priority_Update(f32_t fDeltaTime);
	void		Update(f32_t fDeltaTime);
	void		Late_Update(f32_t fDeltaTime);
	HRESULT		Render();
	void		Clear(uint32_t iClearLevelIndex);

	shared_ptr<CGameObject>			Find_GameObject(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag);
	//vector<shared_ptr<CGameObject>> Find_GameObjects(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag);
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