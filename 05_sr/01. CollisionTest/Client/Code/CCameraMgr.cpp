#include "pch.h"
#include "CCameraMgr.h"

IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
{
}

CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::AddCamera(CGameObject* pCamera)
{
	m_vCamera.push_back(pCamera);
}

D3DVIEWPORT9 CCameraMgr::GetCameraViewPort(CAMERATYPE eType)
{
	for (auto pObj : m_vCamera)
	{
		CCamera* pCamera = dynamic_cast<CCamera*> (pObj);
		if (pCamera->GetCameraType() == eType)
		{
			return pCamera->GetViewPort();
		}
	}
	MSG_BOX("NO CameraType");
}

_matrix CCameraMgr::GetCameraView(CAMERATYPE eType)
{
	for (auto pObj : m_vCamera)
	{
		CCamera* pCamera = dynamic_cast<CCamera*> (pObj);
		if (pCamera->GetCameraType() == eType)
		{
			return pCamera->GetVeiwMat();
		}
	}
	MSG_BOX("NO CameraType");
}

_matrix CCameraMgr::GetCameraProj(CAMERATYPE eType)
{
	for (auto pObj : m_vCamera)
	{
		CCamera* pCamera = dynamic_cast<CCamera*> (pObj);
		if (pCamera->GetCameraType() == eType)
		{
			return pCamera->GetProjMat();
		}
	}
	MSG_BOX("NO CameraType");
}
