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


    void        SetChoiceItem(int iItem) { m_iChoiceItem = iItem; }
    int         GetChoiceItem() { return m_iChoiceItem; }

private:
    TILEID      m_eChoiceTile;
    int         m_iChoiceItem;
};

