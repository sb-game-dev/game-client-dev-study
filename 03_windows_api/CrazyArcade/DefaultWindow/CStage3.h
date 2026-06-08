#pragma once
#include "CScene.h"
class CStage3 :
    public CScene
{
public:
    CStage3();
    virtual~CStage3();
public:
    void Initialize()                       override;
    int Update()                            override;
    void LateUpdate()                       override;
    void Render(Graphics* _pGraphics)       override;
    void Release()                          override;
};

