#pragma once

#include "Level.h"

/* 1. 현재 할당된 레벨을 보관한다. */
/* 1_1. 보관하고 있는 레벨의 업데이트 또는 렌더를 호출해주낟. */
/* 2. 전달받은 레벨로 교체해준다. */
/* 2_1. 교체 시에 이전레벨은 삭제 처리한다. */
/* 2_2. 삭제된 레벨 용 자원도 정리해준다. */


NS_BEGIN(Engine)

class CLevel_Manager final
{
private:
	CLevel_Manager();
public:
	~CLevel_Manager() = default;

public:
	HRESULT Change_Level(int32_t iNewLevelIndex, shared_ptr<CLevel> pNewLevel);
	void Update(f32_t fTimeDelta);
	HRESULT Render();

private:
	int32_t					m_iCurrentLevelIndex = { -1 };
	shared_ptr<CLevel>		m_pCurrentLevel = { nullptr };

public:
	static unique_ptr<CLevel_Manager> Create();
};

NS_END