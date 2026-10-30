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
	void				Add_Camera(CAMERA eCameraID, shared_ptr<CCamera> pCamera);
	void				Set_MainCamera(CAMERA eCameraID);
	shared_ptr<CCamera> Get_MainCamera() { return m_pMainCamera; }
	CAMERA				Get_MainCameraID() { return m_eMainCamera; }


private:
	shared_ptr<CCamera>		m_Cameras[ETOUI(CAMERA::END)];
	shared_ptr<CCamera>		m_pMainCamera = { nullptr };
	CAMERA					m_eMainCamera = { CAMERA::END };

private:
	shared_ptr<CCamera> Find_Camera(CAMERA eCameraID);

public:
	static unique_ptr<CCamera_Manager> Create();
};

NS_END