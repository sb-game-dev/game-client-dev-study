#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
public:
    CMonster();
    ~CMonster();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void Shoot();
    CObj* CreateBullet();

private:
    float m_fAngleSpeed;
    DWORD m_dwTime;
};

