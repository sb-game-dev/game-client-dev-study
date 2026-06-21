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
    void        CheckKickBomb(DIRECTION eDIR);
    void        CreateBomb();
    void        CreateDart();
    void        ShowItemGainEffect(HDC hDC);
    void        ShowCtrlSlot(HDC hDC);
    void        ShowShield(HDC hDC);
public:
    void        SetHit();// { m_eCurMotion = HIT; ChangeMotion(); }
    void        SetBossHit(){ m_eCurMotion = DEATH; ChangeMotion(); }
    void        SetReduceBombCnt() { --m_iBombCnt; }
    void        AddGas(float fGas) { m_fRemainGas += fGas; }
    void        SetWin() { m_eCurMotion = WIN; ChangeMotion(); }

    MOTION      GetCurMotion() { return m_eCurMotion; }
    bool        GetShield() { return m_bShowShieldEffect; }
    bool        GetRide() { return m_bRide; }
    float       GetRemainGas() { return m_fRemainGas; }
    float*      GetRemainGasPtr() { return &m_fRemainGas; }
    void        PickUpItem(const WCHAR* pItemFrameKey);
private:
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    float       m_fWalkSpeed;
    float       m_fBubbleSpeed;
    float       m_fKartSpeed;

    ULONGLONG   m_dwFrameCount;
    ULONGLONG   m_dwItemEffectFrameCount;
    ULONGLONG   m_dwShieldEffectFrameCount;

    float       m_fBlockMoveTime;
    int         m_iBombRange;
    int         m_iBombCnt;
    int         m_iBombMax;
    bool        m_bShowItemGainEffect;
    bool        m_bShowShieldEffect;
    int         m_iShieldFrame;

    ITEMTYPE    m_eItemFrameKey;

    ITEMTYPE    m_eCtrlSlot;
    int         m_iCtrlSlotCnt;

    bool        m_bRide;
    bool        m_bShoe;
    float       m_fKickBombTime;

    vector<CObj*>* m_pTileVector;

    float       m_fRemainGas;
};

