#pragma once
#include "CScene.h"
class CEdit :
    public CScene
{
public:
    CEdit() {}
    virtual~CEdit() {}

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

};

