#pragma once
#include "Engine_Defines.h"
#include "Timer_Manager.h"
#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Prototype_Manager.h"
#include "Object_Manager.h"
#include "Camera_Manager.h"
#include "Light_Manager.h"
#include "Renderer.h"
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
	~CGameInstance() = default;

public:/* 엔진의 초기화과정 : 여러 메니져를 미리 할당하여 사용 할 준비를 한다*/
	HRESULT			Initialize_Engine(const ENGINE_DESC& EngineDesc, 
									  _Out_ ComPtr<ID3D11Device>& pDevice, 
									  _Out_ ComPtr<ID3D11DeviceContext>& pContext);

public:
	HRESULT			Clear_BackBuffer_View(const float4_t* pClearColor);
	HRESULT			Clear_DepthStencil_View();
	HRESULT			Clear_Resources(int32_t iClearLevelIndex);
	void			Update_Engine(f32_t fDeltaTime);
	HRESULT			Draw();
	HRESULT			Present();

#pragma region PROTOTYPE_MANAGER
public:
	HRESULT Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype);
	shared_ptr<CPrototype> Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg = nullptr);
#pragma endregion

#pragma region LEVEL_MANAGER
public:
	HRESULT			Change_Level(int32_t iNewLevelIndex, shared_ptr<CLevel> pNewLevel);
#pragma endregion

#pragma region TIMER_MANAGER
public:
	f32_t			Get_TimeDelta(const wstring_t& strTimerTag);
	HRESULT			Add_Timer(const wstring_t& strTimerTag);
	void			Update_TimeDelta(const wstring_t& strTimerTag);
#pragma endregion

#pragma region OBJECT_MANAGER
public:
	HRESULT	Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag,
		uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag, void* pArg = nullptr);

	shared_ptr<CGameObject>			Find_GameObject(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag);
#pragma endregion

#pragma region CAMERA_MANAGER
public:
	void				Add_Camera(const wstring_t& strCameraTag, shared_ptr<CCamera> pCamera);
	void				Set_MainCamera(const wstring_t& strCameraTag);
	float4x4_t			GetView();
	shared_ptr<CCamera> Get_MainCamera();
#pragma endregion

#pragma region LIGHT_MANAGER
	void	AddLight(const wstring_t& strLightTag, shared_ptr<CLight> pLight);
	shared_ptr<CLight> Find_Light(const wstring_t& strLightTag);
#pragma endregion

#pragma region RENDERER
	void	Add_RenderGroup(RENDERID eRenderID, shared_ptr<CGameObject> pGameObject);
	void	Set_Mirror(shared_ptr<CGameObject> pMirror);
	void	Add_ReflectObject(shared_ptr<CGameObject>pObject);
	void	Clear_Mirror();
#pragma endregion

private:
	unique_ptr<CGraphic_Device>		m_pGraphic_Device = { nullptr };
	unique_ptr<CObject_Manager>		m_pObject_Manager = { nullptr };
	unique_ptr<CTimer_Manager>		m_pTimer_Manager = { nullptr };
	unique_ptr<CLevel_Manager>		m_pLevel_Manager = { nullptr };
	unique_ptr<CPrototype_Manager>	m_pPrototype_Manager = { nullptr };
	unique_ptr<CCamera_Manager>		m_pCamera_Manager = { nullptr };
	unique_ptr<CLight_Manager>		m_pLight_Manager = { nullptr };
	unique_ptr<CRenderer>			m_pRenderer = { nullptr };

public:
	void			Release_Engine();

};
NS_END
