#pragma once

#include "CBase.h"
#include "CGraphicDev.h"
#include "CTimerMgr.h"
#include "CFrameMgr.h"

#include "CManagement.h"

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z)
	{
		_x = x, _y = y, _z = z;
	}
	float _x, _y, _z;
	static const DWORD FVF;
};

struct ColorVertex
{
	ColorVertex() {}
	ColorVertex(float x, float y, float z, D3DCOLOR color)
	{
		_x = x, _y = y, _z = z;
		_color = color;
	}
	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF;
};

class CMainApp : public CBase
{
private:		// 생성자, 소멸자
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp();
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp(const float& fTimeDelta);
	void		Render_MainApp();

protected:

private:
	Engine::CGraphicDev*	m_pDeviceClass;
	Engine::CManagement* m_pManagementClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;

	void	RenderCube();
	void	RenderCube2();
	void	RenderPyramid();
	void	RenderTriangle();
	void	KeyInput();

	D3DXVECTOR3	GetMouse();


public:		// 생성 함수
	static CMainApp* Create();


private:	// 소멸 함수
	virtual void	Free();

private:
	float m_fRotateY;
	float m_fRotateX;
	float m_fCameraMoveSpeed;

	D3DXVECTOR3	m_vCameraPos;
	D3DXVECTOR3	m_vCameraDir;
	D3DXVECTOR3	m_vCameraLook;

	D3DXVECTOR3	m_vMousePos;
	D3DXVECTOR3	m_vPreMousePos;


};

