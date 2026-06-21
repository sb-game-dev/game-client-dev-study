#pragma once
#include "CObj.h"
class CGasStation :
    public CObj
{
public:
    CGasStation();
    virtual~CGasStation();
public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void    SetRefuel(bool bRefuel) { m_bRefuel = bRefuel; }

private:
    bool    m_bRefuel;
};

