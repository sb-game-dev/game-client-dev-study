#pragma once
#include "CObj.h"
class CBullet :
    public CObj
{
public:
    CBullet();
    virtual ~CBullet();
  
public:
    void Initialize() override;
    void Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

