#pragma once
#include "CScene.h"
#include "CPlayer.h"
class CStage3 :
    public CScene
{
public:
    CStage3();
    virtual~CStage3();
public:
    void    Initialize()                override;
    int     Update()                    override;
    void    LateUpdate()                override;
    void    Render(HDC hDC)             override;
    void    Release()                   override;
private:
    void        CheckSceneFrame();
    void        ChangeScene();
private:
    CObj*       m_pPlayer;
    CObj*       m_pPlayer2;
    PLAYMODE*   m_pPlayMode;
};

