#pragma once
#include "CObj.h"
class CWater :
    public CObj
{
public:
    CWater();
    ~CWater();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Spread(int iBombRange);

private:
    DWORD m_dwTime;

};

