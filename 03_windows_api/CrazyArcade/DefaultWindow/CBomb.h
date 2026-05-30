#pragma once
#include "CObj.h"
class CBomb :
    public CObj
{
public:
    CBomb();
    ~CBomb();

public:
    void        Initialize()        override;
    int         Update()            override;
    void        LateUpdate()        override;
    void        Render(HDC hDC)     override;
    void        Release()           override;

public:
    void        SetBombRange(int iNum) { m_iBombRange = iNum; }
    CObj*       CreateWater();

    bool        GetPlayerCollision() { return m_bPlayerCollision; }

private:
    DWORD       m_dwTime;
    int         m_iBombRange;

    bool        m_bPlayerCollision;
};

