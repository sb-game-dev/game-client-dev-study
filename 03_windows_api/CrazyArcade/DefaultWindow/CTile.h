#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
public:
    CTile();
    virtual~CTile();
public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(Graphics* _pGraphics) override;
    void Release() override;
};

