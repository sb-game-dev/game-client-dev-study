#pragma once
#include "CCamera.h"

class CCameraMgr
{
	DECLARE_SINGLETON(CCameraMgr);

private:
	explicit CCameraMgr();
	virtual ~CCameraMgr();

public:
	void			AddCamera(CGameObject*);
	D3DVIEWPORT9	GetCameraViewPort(CAMERATYPE eType);
	_matrix			GetCameraView(CAMERATYPE eType);
	_matrix			GetCameraProj(CAMERATYPE eType);
	int				GetCameraCnt() { return m_vCamera.size(); }

private:
	vector<CGameObject*>		m_vCamera;
};

