#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CCamera;
class CCamera_Manager
{
private:
	CCamera_Manager();
public:
	~CCamera_Manager() = default;

public:
	void				Add_Camera(const wstring_t& strCameraTag, shared_ptr<CCamera> pCamera);
	void				Set_MainCamera(const wstring_t& strCameraTag);
	shared_ptr<CCamera> Get_MainCamera(const wstring_t& strCameraTag) { return m_pMainCamera; }

	void			Priority_Update(f32_t fDeltaTime);
	void			Update(f32_t fDeltaTime);
	void			Late_Update(f32_t fDeltaTime);
	HRESULT			Bind();
private:
	map<const wstring_t, shared_ptr<CCamera>> m_pCameras;
	shared_ptr<CCamera>	m_pMainCamera = { nullptr };

private:
	shared_ptr<CCamera> Find_Camera(const wstring_t& strCameraTag);

public:
	static unique_ptr<CCamera_Manager> Create();
};

NS_END