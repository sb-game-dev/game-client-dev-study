#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()	PURE;
	virtual int  Update()		PURE;
	virtual void LateUpdate()	PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

public:
	void		Update_Rect();

public :
	void SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetPosX(float fX) { m_tInfo.fX += fX; }
	void SetPosY(float fY) { m_tInfo.fY += fY; }
	void SetSize(float fCX, float fCY) { m_tInfo.fCX = fCX; m_tInfo.fCY = fCY; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	void SetAbility(float fHp, float fAttack) { m_tAbility.fHp = fHp; m_tAbility.fAttack = fAttack; }
	void SetDead() { m_bDead = DEAD; }
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed;}

	void TakeDamge(float fAttack) { m_tAbility.fHp -= fAttack; }
	bool GetDead() { return m_bDead; }

	const INFO GetInfo()		const 	{ return m_tInfo; }
	const RECT* GetRect()		const 	{ return &m_tRect; }
	const ABILITY GetAbility()	const	{ return m_tAbility; }

protected:
	INFO		m_tInfo;		
	RECT		m_tRect;		
	ABILITY		m_tAbility;

	float		m_fSpeed;
	float		m_fAngle;
	
	bool		m_bDead;
};

