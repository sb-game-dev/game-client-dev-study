#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
private:
    enum MOVE_STATE { MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_BUBBLE, MOVE_END };
public:
    CPlayer();
    ~CPlayer();

public:
    void    Initialize()        override;
    int     Update()            override;
    void    LateUpdate()        override;
    void    Render(HDC hDC)     override;
    void    Release()           override;
    void    Update_Rect() ;

public:
    void    SetBubble() { m_bBubble = true; }

    void    UpBomb()    { m_iBombMax += 1; }
    void    UpSpeed()   { m_fSpeed += 1; }
    void    UpPower()   { m_iBombRange += 1; }

private:
    bool    KeyDown();
    CObj*   CreateBomb();
    void    CheckPushBlock(DIRECTION eDIR);

private:
    int         m_iBombRange;
    int         m_iBombMax;

    bool        m_bBubble;
    MOVE_STATE  m_tMoveState;

    float       m_fBlockMoveTime;
    DIRECTION   m_ePrevKey;
    DIRECTION   m_eCurKey;
};

