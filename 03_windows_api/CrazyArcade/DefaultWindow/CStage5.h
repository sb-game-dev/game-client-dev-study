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
    void            CheckCollisionGasStation();
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
    CObj*           m_pGasStation;

    int             m_iTrackCnt;
    int             m_iNextBase;

    float*          m_pPlayerRemainGas;
};
