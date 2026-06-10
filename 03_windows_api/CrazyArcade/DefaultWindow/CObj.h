#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void	Initialize()				PURE;
	virtual int		Update()					PURE;
	virtual void	LateUpdate()				PURE;
	virtual void	Render(HDC hDC)				PURE;
	virtual void	Release()					PURE;

public:
	void			Update_Rect();
	const WCHAR*	GetFrameKey() { return m_pFrameKey; }

	void			SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void			SetPosX(float fNum) { m_tInfo.fX += fNum; }
	void			SetPosY(float fNum) { m_tInfo.fY += fNum; }

	void			SetFrameKey(const WCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void			MoveFrame();
	void			SetStartFrame(int eID) { m_tFrame.iStart = eID; }
	FRAME			GetFrame() { return m_tFrame; }


	RECT*			GetRect() { return &m_tRect; }
	INFO*			GetInfo() { return &m_tInfo; }

	void			SetDead() { m_bDead = DEAD; }
	void			SetHit() { m_bHit = true; }

protected:
	INFO			m_tInfo;		
	RECT			m_tRect;	
	bool			m_bDead;
	bool			m_bHit;

	float			m_fSpeed;
	
	const WCHAR*	m_pFrameKey;
	FRAME			m_tFrame;
};

