#pragma once
#include "Define.h"
#include "CObj.h"
class CCameraMgr
{
public:
	CCameraMgr();
	CCameraMgr(const CCameraMgr& rhs) = delete;
	CCameraMgr operator= (CCameraMgr& rhs) = delete;
	~CCameraMgr();
public:
	static	CCameraMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CCameraMgr;
		return m_pInstance;
	}

	static	void	DestroyInstance()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CCameraMgr* m_pInstance;

public:
	void	Initialize();
	void	Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

	void	SetTarget(CObj* pObj) { m_pTarget = pObj; }
	

	D3DXMATRIX	GetMatView() { return m_matView; }
	D3DXMATRIX  GetMatProj() { return m_matProj; }

	D3DXMATRIX* GetMatViewPtr() { return &m_matView; }
	D3DXMATRIX* GetMatProjPtr() { return &m_matProj; }

private:
	void	KeyInput();

public:
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vUp;

	D3DXMATRIX	m_matView;
	D3DXMATRIX	m_matProj;

	CObj*		m_pTarget;
};

