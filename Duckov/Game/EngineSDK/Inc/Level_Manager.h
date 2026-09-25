#pragma once
#include "Level.h"
NS_BEGIN(Engine)
class CLevel_Manager
{
private:
	CLevel_Manager();
public:
	~CLevel_Manager() = default;

public:
	HRESULT			Change_Level(int32_t iNewLevelIndex, shared_ptr<CLevel> pNewLevel);
	void			Update(f32_t fTimeDelta);
	void			LateUpdate(f32_t fDeltaTime);
	HRESULT			Render();

private:
	int32_t						m_iCurrentLevelIndex = { -1 };
	shared_ptr<CLevel>			m_pCurrentLevel = { nullptr };

public:
	static unique_ptr<CLevel_Manager>	Create();
};

NS_END