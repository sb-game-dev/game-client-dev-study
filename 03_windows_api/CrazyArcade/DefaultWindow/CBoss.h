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
	void		SetBossWin() { m_bBossWin = true; }
	MOTION		GetCurMotion() { return m_eCurMotion; }
	void		SetDeath() { m_eCurMotion = DEATH; ChangeMotion(); }
private:
	void        ChangeMotion();
	void        CheckFrame();

	void		BossAttackAround(int iRange);
	void		CreateDst();

	void		BossPattern();
	void		AttackPattern1();
	void		AttackPattern2();
	void		Move();

	void		CreateBomb(float fX, float fY, DIRECTION eDir);
private:
	MOTION      m_ePreMotion;
	MOTION      m_eCurMotion;
	MOTION		m_eReturnMotion;
	float       m_fWalkSpeed;
	float       m_fAngrySpeed;
	float       m_fBubbleSpeed;

	ULONGLONG   m_dwFrameCount;

	float       m_fBlockMoveTime;
	int         m_iBombRange;
	int         m_iBombMax;
	int			m_iHP;

	int			m_iAttackRange;
	int			m_iAttackRangeDelta;

	bool		m_bMoveAttack;
	ULONGLONG	m_dwAttackTime;

	float		m_fDstX;
	float		m_fDstY;
	int			m_iShootCnt;
	bool		m_bCheckRemainTile;
	int			m_iRemainTile;

	bool		m_bBossWin;
};

