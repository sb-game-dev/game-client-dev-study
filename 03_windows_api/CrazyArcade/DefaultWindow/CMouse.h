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
    int         Update()                        override;
    void        LateUpdate()                   override;
    void        Render(Graphics* _pGraphics)   override;
    void        Release()                      override;

public:
    void        SetChoiceTile(TILEID eID) { m_eChoiceTile = eID; }
    POINT       GetPoint();
private:
    TILEID      m_eChoiceTile;
};

