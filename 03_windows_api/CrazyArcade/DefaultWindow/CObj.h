#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	~CObj();

public:
	virtual void Initialize()	PURE;
	virtual int Update()		PURE;
	virtual void LateUpdate()	PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

public:
	INFO GetInfo() { return m_tInfo; }
	RECT* GetRect() { return &m_tRect; }

	void AdjustPos(float fX, float fY) { m_tInfo.fX = ((int)fX / 40) * 40.f + 20; m_tInfo.fY = ((int)fY / 40) * 40.f + 20; };

	void SetDir(DIRECTION eDir) { m_eDirection = eDir; }
	void SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetDead() { m_bDead = DEAD; }
	void SetPosX(float fNum) { m_tInfo.fX += fNum; }
	void SetPosY(float fNum) { m_tInfo.fY += fNum; }
	void SetFrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	const TCHAR* GetFrameKey() { return m_pFrameKey; }

	void Update_Rect();
	void MoveFrame();
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDirection;
	RENDERINFO	m_tRenderInfo;

	//
	DWORD		m_dwAniTime;
	int         m_iFrame;
	//

	FRAME		m_tFrame;


	float		m_fSpeed;
	bool		m_bDead;

	const TCHAR* m_pFrameKey;
};

