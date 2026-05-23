#pragma once
#include "CObj.h"
class CWall :
    public CObj
{
public:
    CWall();
    ~CWall();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
};

