#pragma once

#include "CObj.h"
class CLine;

class CPlayer : public CObj
{

public:
    enum MOVE_STATE {
        MOVE_GROUND,
        MOVE_JUMP,
        MOVE_FALL,
        MOVE_DOWNJUMP,
        MOVE_WALL,
        MOVE_ROPE,
        MOVE_END
    };
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override;

private:
    void        KeyInput();
    void        Jump();
    void        Gravity();
    void        DownJump();
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

