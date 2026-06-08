#pragma once

#include "CObj.h"

class CPlayer : public CObj
{
private:
    enum MOTION { START, IDLE, LEFT, RIGHT, UP, DOWN, HIT, DEATH, REVIVAL, MOTION_END };
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void        Initialize()                       override;
    int         Update()                           override;
    void        LateUpdate()                       override;
    void        Render(Graphics* _pGraphics)       override;
    void        Release()                          override;

private:
    void        KeyInput();
    void        ChangeMotion();
    void        CheckDead();
private:
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    float       m_fWalkSpeed;
    float       m_fBubbleSpeed;

    ULONGLONG   m_dwFrameCount;

};

