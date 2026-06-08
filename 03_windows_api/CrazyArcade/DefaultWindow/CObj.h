#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()					PURE;
	virtual int  Update()						PURE;
	virtual void LateUpdate()					PURE;
	virtual void Render(Graphics* _pGraphics)	PURE;
	virtual void Release()						PURE;

public:
	void		Update_Rect();
	WCHAR*		GetFrameKey() { return m_pFrameKey; }

	void		SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void		SetPosX(float fX) { m_tInfo.fX = fX; }
	void		SetPosY(float fY) { m_tInfo.fY = fY; }

	void		SetFrameKey(WCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
protected:
	INFO		m_tInfo;		
	RECT		m_tRect;	
	bool		m_bDead;

	float		m_fSpeed;
	
	WCHAR*		m_pFrameKey;
	FRAME		m_pFrame;
};

