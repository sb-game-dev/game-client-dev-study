#pragma once
#include "CScene.h"
class CShop :
    public CScene
{
public:
    CShop();
    virtual~CShop();
public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override; 
};

