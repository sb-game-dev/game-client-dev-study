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

public:
    void SetBomb(list<CObj*>* BombListp) { m_BombListp = BombListp; }

private:
    list<CObj*>* m_BombListp;
    int m_iBombPower;
    int m_iMaxBomb;
};

