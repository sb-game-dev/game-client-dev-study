#pragma once
#include "Engine_Defines.h"
#include "Timer_Manager.h"
#include "Graphic_Device.h"
#include "Level_Manager.h"
/*
1. 엔진의 기능을 클라이언트에 보여주는 객체.
2. 엔진에 정의되어있는 다양한 기능을 하는 객체를 모아서 보관한다.
3. 엔진의 업데이트와 렌더를 담당한다.
*/
NS_BEGIN(Engine)
class ENGINE_DLL CGameInstance final
{
	DECLARE_SINGLETON(CGameInstance)

private:
	CGameInstance();

public:
	~CGameInstance();

public:/* 엔진의 초기화과정 : 여러 메니져를 미리 할당하여 사용 할 준비를 한다*/
	HRESULT			Initialize_Engine(const ENGINE_DESC& EngineDesc, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext);

public:
	HRESULT			Clear_BackBuffer_View(const float4_t* pClearColor);
	HRESULT			Clear_DepthStencil_View();
	HRESULT			Present();

	HRESULT			Clear_Resources(int32_t iCurrentLevel);

public:
	f32_t			Get_TimeDelta(const wstring_t& strTimerTag);
	HRESULT			Add_Timer(const wstring_t& strTimerTag);
	void			Update_TimeDelta(const wstring_t& strTimerTag);

private:
	unique_ptr<CGraphic_Device>	m_pGraphic_Device = { nullptr };
	unique_ptr<CTimer_Manager>	m_pTimer_Manager = { nullptr };
	unique_ptr<CLevel_Manager>	m_pLevel_Manager = { nullptr };

public:
	void			Release_Engine();

};
NS_END
