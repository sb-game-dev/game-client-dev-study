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
private:
    void        ChangeMotion();
    void        CheckFrame();

private:
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    ULONGLONG   m_dwFrameCount;
};

