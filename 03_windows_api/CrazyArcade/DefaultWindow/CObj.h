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
	void			SetDirection(DIRECTION eID) { m_eDIR = eID; }
	void			SetRenderID(RENDERID eID) { m_eRenderID = eID; }

	void			SetDead() { m_bDead = DEAD; }
	virtual void	SetHit() { m_bHit = true; }

	void			SetFrameKey(const WCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void			SetStartFrame(int eID) { m_tFrame.iStart = eID; }

	void			SetDraw(bool bDraw) { m_bDraw = bDraw; }
	
	void			SetCanMove(bool bMove) { m_bCanMove = bMove; }

	void			SetPlayerID(PLAYERID eID) { m_ePlayerID = eID; }

	FRAME			GetFrame() { return m_tFrame; }
	RECT*			GetRect() { return &m_tRect; }
	INFO*			GetInfo() { return &m_tInfo; }
	const RENDERID& GetRenderID() const { return m_eRenderID; }
	bool			GetCanMove() { return m_bCanMove; }
	bool			GetDraw() { return m_bDraw; }
	PLAYERID		GetPlayerID() { return m_ePlayerID; }

	void			MoveFrame();
protected:
	INFO			m_tInfo;		
	RECT			m_tRect;	
	bool			m_bDead;
	bool			m_bHit;
	DIRECTION		m_eDIR;

	float			m_fSpeed;
	
	const WCHAR*	m_pFrameKey;
	FRAME			m_tFrame;

	RENDERID		m_eRenderID;
	bool			m_bCanMove;
	bool			m_bDraw;
	PLAYERID		m_ePlayerID;
};

