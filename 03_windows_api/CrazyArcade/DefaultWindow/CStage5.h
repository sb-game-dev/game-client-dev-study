#pragma once
#include "CScene.h"
#include "CObj.h"
class CStage5 :
    public CScene
{
public:
    CStage5();
    virtual~CStage5();

public:
    void            Initialize()                override;
    int             Update()                    override;
    void            LateUpdate()                override;
    void            Render(HDC hDC)             override;
    void            Release()                   override;
private:
    void            CheckBase();
    void            CheckBase2();
    void            CheckCollisionGasStation();
    void            CheckCollisionGasStation2();
    void            CheckNoCollisionGasStation();

    void            CheckSceneFrame();
    void            ChangeScene();

private:
    HDC             m_hBackGround;
    vector<CObj*>*  m_pTileVector;

    CObj*           m_pBaseStart;
    CObj*           m_pBase1;
    CObj*           m_pBase2;
    CObj*           m_pBase3;
    CObj*           m_pBase4;
    CObj*           m_pBaseFinal;

    CObj*           m_pPlayer;
    CObj*           m_pPlayer2;
    CObj*           m_pGasStation;
    
    CObj*           m_pBaseStartEffect1;
    CObj*           m_pBaseStartEffect2;

    CObj*           m_pBase1Effect1;
    CObj*           m_pBase1Effect2;
    CObj*           m_pBase2Effect1;
    CObj*           m_pBase2Effect2;
    CObj*           m_pBase3Effect1;
    CObj*           m_pBase3Effect2;
    CObj*           m_pBase4Effect1;
    CObj*           m_pBase4Effect2;

    int             m_iTrackCnt;
    int             m_iNextBase;

    int             m_iTrackCnt2;
    int             m_iNextBase2;

    float*          m_pPlayerRemainGas;
    float*          m_pPlayerRemainGas2;
    PLAYMODE*       m_pPlayMode;
};
