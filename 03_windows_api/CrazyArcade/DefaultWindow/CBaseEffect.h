#pragma once
#include "CObj.h"
class CBaseEffect :
    public CObj
{
public:
    CBaseEffect();
    virtual~CBaseEffect();
public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void    SetMoveFrame(bool bMove) { m_bMoveFrame = bMove; }

private:
    bool    m_bMoveFrame;
};

