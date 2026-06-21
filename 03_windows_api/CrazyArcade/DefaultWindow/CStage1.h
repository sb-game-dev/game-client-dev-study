#pragma once
#include "CScene.h"
#include "CPlayer.h"
class CStage1 :
    public CScene
{
public:
    CStage1();
    virtual~CStage1();
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
    CObj*       m_pPlayer;
};

