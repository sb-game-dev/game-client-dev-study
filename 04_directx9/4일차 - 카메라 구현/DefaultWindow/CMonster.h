#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
public:
    CMonster();
    virtual~CMonster();
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

};

