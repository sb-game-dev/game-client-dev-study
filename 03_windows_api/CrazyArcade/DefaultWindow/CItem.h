#pragma once
#include "CObj.h"
class CItem :
    public CObj
{
public:
    CItem();
    virtual~CItem();
public:
    void    Initialize()        override;
    int     Update()            override;
    void    LateUpdate()        override;
    void    Render(HDC hDC)     override;
    void    Release()           override;

public:
    void    SetHit() { m_bDead = DEAD; }
};

