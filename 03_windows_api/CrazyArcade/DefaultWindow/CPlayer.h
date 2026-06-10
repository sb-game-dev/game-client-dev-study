#pragma once

#include "CObj.h"

class CPlayer : public CObj
{   
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void        Initialize()                       override;
    int         Update()                           override;
    void        LateUpdate()                       override;
    void        Render(HDC hDC)                    override;
    void        Release()                          override;

private:
    void        KeyInput();
    void        ChangeMotion();
    void        CheckFrame();
    void        CheckPushBlock(DIRECTION eDIR);
    void        CreateBomb();

public:
    void        SetHit() { m_eCurMotion = HIT; ChangeMotion(); }
    void        SetBossHit(){ m_eCurMotion = DEATH; ChangeMotion(); }
private:
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    float       m_fWalkSpeed;
    float       m_fBubbleSpeed;

    ULONGLONG   m_dwFrameCount;

    float       m_fBlockMoveTime;
    int         m_iBombRange;
    int         m_iBombMax;
};

