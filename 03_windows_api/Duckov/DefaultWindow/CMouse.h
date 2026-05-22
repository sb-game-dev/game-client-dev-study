#pragma once
#include "CObj.h"
class CMouse :
    public CObj
{
public:
    CMouse();
    ~CMouse();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

};

