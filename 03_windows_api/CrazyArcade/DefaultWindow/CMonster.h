#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
public:
    CMonster();
    virtual~CMonster();
public:
    void        Initialize()        override;
    int         Update()            override;
    void        LateUpdate()        override;
    void        Render(HDC hDC)     override;
    void        Release()           override;
public:
    void	    SetHit() { m_eCurMotion = HIT; ChangeMotion(); }
    void        LeftHandRuleMove();
private:
    void        ChangeMotion();
    void        CheckFrame();
    void        SetDestination(DIRECTION eDir, int iIndex);
private:
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    ULONGLONG   m_dwFrameCount;

    vector<CObj*>*  m_pTile;
    list<CObj*>*    m_pBombList;
    list<CObj*>*    m_pBombList2;

    float       m_fDstX;
    float       m_fDstY;
};

