#pragma once

#include "CObj.h"

class CPlayer : public CObj
{   
private:
    enum ITEMTYPE { BUBBLE, DART, FLUID, NEEDLE, ROLLER, SHIELD, SHOE, TRAMPOLINE, ITEMTYPE_END };
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
    void        ShowItemGainEffect(HDC hDC);
public:
    void        SetHit() { m_eCurMotion = HIT; ChangeMotion(); }
    void        SetBossHit(){ m_eCurMotion = DEATH; ChangeMotion(); }
    void        SetReduceBombCnt() { --m_iBombCnt; }

    void        PickUpItem(const WCHAR* pItemFrameKey);
private:
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    float       m_fWalkSpeed;
    float       m_fBubbleSpeed;

    ULONGLONG   m_dwFrameCount;
    ULONGLONG   m_dwItemEffectFrameCount;

    float       m_fBlockMoveTime;
    int         m_iBombRange;
    int         m_iBombCnt;
    int         m_iBombMax;
    bool        m_bShowItemGainEffect;
    ITEMTYPE    m_pItemFrameKey;
};

