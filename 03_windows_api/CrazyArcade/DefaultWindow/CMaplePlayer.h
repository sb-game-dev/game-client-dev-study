#pragma once
#include "CObj.h"
#include "CLine.h"

class CMaplePlayer :public CObj
{
public:
	CMaplePlayer();
	virtual~CMaplePlayer();

public:
	void		Initialize()		override;
	int			Update()			override;
	void		LateUpdate()		override;
	void		Render(HDC hDC)	override;
	void		Release()			override;
	

public:
	void		Offset();
	bool		GetOffsetMove() { return m_bOffsetMove; }
private:
	void        KeyInput();
	void        ChangeMotion();
	void        CheckFrame();


	void        Jump();
	void        Gravity();
	void        DownJump();
	void        TakeDamage();

private:
	MOTION      m_ePreMotion;
	MOTION      m_eCurMotion;

	ULONGLONG   m_dwFrameCount;
	float       m_time;
	float       m_fJumpPower;
	bool        m_bJump;
	bool        m_bFalling;

	MOVE_STATE  m_eMoveState;
	MOVE_STATE  m_ePreMoveState;

	float       m_fPrevX;
	float       m_fPrevY;

	CLine*		m_pCurLine;

	bool		m_bMoveFrame;

	float		m_fOffsetSpeed;
	bool		m_bOffsetMove;
};

