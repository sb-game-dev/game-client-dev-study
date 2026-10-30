#include "Camera_Manager.h"
#include "Camera.h"
CCamera_Manager::CCamera_Manager()
{
}

void CCamera_Manager::Add_Camera(CAMERA eCameraID, shared_ptr<CCamera> pCamera)
{
	if (eCameraID >= CAMERA::END || nullptr == pCamera)
		return;
	m_Cameras[ETOUI(eCameraID)] = pCamera;
}

void CCamera_Manager::Set_MainCamera(CAMERA eCameraID)
{
	auto pCamera = Find_Camera(eCameraID);
	if (nullptr == pCamera)
		return;
	m_pMainCamera = pCamera;
	m_eMainCamera = eCameraID;
}

shared_ptr<CCamera> CCamera_Manager::Find_Camera(CAMERA eCameraID)
{
	if (eCameraID >= CAMERA::END)
		return nullptr;
	return m_Cameras[ETOUI(eCameraID)];
}

unique_ptr<CCamera_Manager> CCamera_Manager::Create()
{
	return unique_ptr<CCamera_Manager>(new CCamera_Manager());
}
