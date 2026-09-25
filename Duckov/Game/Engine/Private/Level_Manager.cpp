#include "Level_Manager.h"
#include "GameInstance.h"

CLevel_Manager::CLevel_Manager()
{
}
HRESULT CLevel_Manager::Change_Level(int32_t iNewLevelIndex, shared_ptr<CLevel> pNewLevel)
{
	if (nullptr != m_pCurrentLevel)
	{
		m_pCurrentLevel.reset();
		/* 지금 삭제한 레벨의 자원을 정리한다. */
		CGameInstance::Get().Clear_Resources(m_iCurrentLevelIndex);
	}
	m_iCurrentLevelIndex = iNewLevelIndex;
	m_pCurrentLevel = pNewLevel;

	return S_OK;
}

void CLevel_Manager::Update(f32_t fTimeDelta)
{
	if (nullptr != m_pCurrentLevel)
		m_pCurrentLevel->Update(fTimeDelta);
}

void CLevel_Manager::LateUpdate(f32_t fTimeDelta)
{
	if (nullptr != m_pCurrentLevel)
		m_pCurrentLevel->LateUpdate(fTimeDelta);
}

HRESULT CLevel_Manager::Render()
{
	if (nullptr != m_pCurrentLevel)
		m_pCurrentLevel->Render();
	return S_OK;
}
unique_ptr<CLevel_Manager>	CLevel_Manager::Create()
{
	return unique_ptr<CLevel_Manager>(new CLevel_Manager());
}