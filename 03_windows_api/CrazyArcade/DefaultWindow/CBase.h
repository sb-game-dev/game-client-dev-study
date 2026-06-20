#pragma once
#include "CObj.h"
class CBase :
    public CObj
{
public:
    CBase();
    virtual~CBase();
public:
    void    Initialize()       override;
    int     Update()           override;
    void    LateUpdate()       override;
    void    Render(HDC hDC)    override;
    void    Release()          override;

public:
    void    SetBaseMoveFrame(bool bBaseMoveFrame) { m_bBaseMoveFrame = bBaseMoveFrame; }


private:
    void    BaseMoveFrame();

private:
    bool    m_bBaseMoveFrame;
};

