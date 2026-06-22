#pragma once
#include "CScene.h"
#include "CPlayer.h"
class CStage2 :
    public CScene
{
public:
    CStage2();
    virtual~CStage2();
public:
    void    Initialize()        override;
    int     Update()            override;
    void    LateUpdate()        override;
    void    Render(HDC hDC)     override;
    void    Release()           override;
private:
    void        CheckSceneFrame();
    void        ChangeScene();

private:
    CObj*   m_pPlayer;
    CObj*   m_pPlayer2;
};

