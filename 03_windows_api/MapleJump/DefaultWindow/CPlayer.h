#pragma once

#include "CObj.h"
class CLine;

class CPlayer : public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override;

public:
    void SetState(MOVE_STATE eState) { m_eMoveState = eState; }

private:
    void        KeyInput();
    void        Jump();
    void        Gravity();
    void        DownJump();
    void        TakeDamage();
    void        Offset();

private:
    float       m_time;
    float       m_fJumpPower;
    bool        m_bJump;
    bool        m_bFalling;

    MOVE_STATE  m_eMoveState;

    float       m_fPrevX;
    float       m_fPrevY;

    CLine*      m_pCurLine;
};

