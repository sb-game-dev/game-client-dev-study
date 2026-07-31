#pragma once

#include "CBase.h"
#include "CGraphicDev.h"
#include "CTimerMgr.h"
#include "CFrameMgr.h"

#include "CManagement.h"

class CMainApp : public CBase
{
private:		// 생성자, 소멸자
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp();
	int			Update_MaintApp(const float& fTimeDelta);
	void		LateUpdate_MainApp(const float& fTimeDelta);
	void		Render_MainApp();

protected:

private:
	HRESULT		Ready_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	HRESULT		Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev);


private:
	Engine::CGraphicDev*	m_pDeviceClass;
	Engine::CManagement* m_pManagementClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;


public:		// 생성 함수
	static CMainApp* Create();

private:	// 소멸 함수
	virtual void	Free();
};

// 평면의 방정식을 이용하여 지형을 타는 플레이어를 만들어라
// ax + by + cz + d = 0

// D3DXPLANE Plane;
// D3DXPlaneFromPoints();

// 마우스 클릭을 이용하여 지형을 타는 플레이어를 만들어라
// ray - picking

// https://learn.microsoft.com/vi-vn/Windows/win32/direct3d9/d3dxintersecttri
// 결과 : V1 + U(V2 - V1) + V(V3 - V1).
// D3DXVec3IntersectTri();