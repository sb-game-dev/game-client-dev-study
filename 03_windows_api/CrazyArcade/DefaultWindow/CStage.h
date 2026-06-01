#pragma once
#include "CScene.h"
class CStage :
    public CScene
{
public:
    CStage() {}
    virtual~CStage() {}

public:
    

    // CScene을(를) 통해 상속됨
    void Initialize() override;

    int Update() override;

    void LateUpdate() override;

    void Render(HDC hDC) override;

    void Release() override;

};

