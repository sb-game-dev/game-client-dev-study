#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
public:
    CPlayer();
    ~CPlayer();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void KeyDown();
    CObj* CreateBomb();

private:
    int m_iBombPower;
    int m_iMaxBomb;
};

