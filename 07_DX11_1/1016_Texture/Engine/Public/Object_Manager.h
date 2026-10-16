#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CObject_Manager final
{
private:
	CObject_Manager();
public:
	~CObject_Manager() = default;

public:
	HRESULT Initialize(uint32_t iNumLevels);
	/*iPrototypeLevelIndex에 추가되어있는 strPrototypeTag웒영르 찾아서 pARg를 넣어서 복제하여 사본을 만들고  */
	/*iLayerLevelIndex에 추가되어있는 strLayrTAg레이얼르 찾아서 추가해.  */
	HRESULT Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, void* pArg);
	void Priority_Update(f32_t fTimeDelta);
	void Update(f32_t fTimeDelta);
	void Late_Update(f32_t fTimeDelta);
	void Clear(uint32_t iClearLevelIndex);

private:
	uint32_t				m_iNumLevels = {};
	shared_ptr<map<const wstring_t, shared_ptr<class CLayer>>[]>		m_pLayers = {};
	typedef map<const wstring_t, shared_ptr<class CLayer>>				LAYERS;

private:
	shared_ptr<class CLayer> Find_Layer(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag);

public:
	static unique_ptr<CObject_Manager> Create(uint32_t iNumLevels);
};

NS_END