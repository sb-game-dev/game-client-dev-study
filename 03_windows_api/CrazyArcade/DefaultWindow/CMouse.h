#pragma once
#include "CObj.h"
class CMouse :
    public CObj
{

public:
    CMouse();
    virtual~CMouse();
public:
    void        Initialize()                   override;
    int         Update()                       override;
    void        LateUpdate()                   override;
    void        Render(HDC hDC)                 override;
    void        Release()                      override;

public:
    void        SetChoiceTile(int eID);
    TILEID      GetChoiceTile() { return m_eChoiceTile; }

private:
    TILEID      m_eChoiceTile;
};

