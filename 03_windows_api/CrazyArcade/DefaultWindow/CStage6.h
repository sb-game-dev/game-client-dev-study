#pragma once
#include "CScene.h"
#include "CObj.h"
class CStage6 :
    public CScene
{
public:
    CStage6();
    virtual~CStage6();
public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    CObj*       m_pPlayer;
};

