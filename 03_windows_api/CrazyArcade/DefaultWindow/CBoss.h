#pragma once
#include "CObj.h"
class CBoss
	:public CObj
{
public:
	CBoss();
	virtual ~CBoss();
public:
	void		Initialize()		override;
	int			Update()			override;
	void		LateUpdate()		override;
	void		Render(HDC hDC)		override;
	void		Release()			override;

public:
	void		SetHit()			override;
	MOTION		GetCurMotion() { return m_eCurMotion; }
	void		SetDeath() { m_eCurMotion = DEATH; ChangeMotion(); }
private:
	void        ChangeMotion();
	void        CheckFrame();

private:
	MOTION      m_ePreMotion;
	MOTION      m_eCurMotion;
	float       m_fWalkSpeed;
	float       m_fBubbleSpeed;

	ULONGLONG   m_dwFrameCount;

	float       m_fBlockMoveTime;
	int         m_iBombRange;
	int         m_iBombMax;
	int			m_iHP;
};

