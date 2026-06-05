#pragma once
#include "CObj.h"
class CItem :
    public CObj
{
public:
    CItem();
    ~CItem();

public:
    void        Initialize()       override;
    int         Update()           override;
    void        LateUpdate()       override;
    void        Render(HDC hDC)    override;
    void        Release()          override;

public:
    void        SetType(ITEM_TYPE eType)    { m_eType = eType; }
    ITEM_TYPE   GetType()                   { return m_eType; }

private:
    ITEM_TYPE       m_eType;
};

