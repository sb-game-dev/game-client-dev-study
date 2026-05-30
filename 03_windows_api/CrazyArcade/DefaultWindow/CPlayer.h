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
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Update_Rect() ;

public:
    void SetBubble() { m_bBubble = true; }

private:
    bool KeyDown();
    CObj* CreateBomb();

private:
    int         m_iBombRange;
    int         m_iBombMax;

    bool        m_bBubble;
    MOVE_STATE  m_tMoveState;
};

