#pragma once
#include "CScene.h"
#include "CObj.h"

class CStage4 :
    public CScene
{
public:
    CStage4();
    virtual~CStage4();

public:
    void    Initialize()                override;
    int     Update()                    override;
    void    LateUpdate()                override;
    void    Render(HDC hDC)             override;
    void    Release()                   override;

private:
    int     CheckRange(INTRECT tIntRect, CObj* pMark);
    void    CheckSceneFrame();
    void    ChangeScene();
    void    DestroyMonster();
private:
    HDC             m_hBackGround;
    list<CObj*>*    m_pMarkList;
    vector<CObj*>*  m_pTileVector;

    int             m_iBlockCheck[19];

    int             m_iPlayer1MarkCnt[19];
    int             m_iPlayer2MarkCnt[19];

    int             m_iBlockCntAnswer[19];

    int             m_iBlockSize[19];

    int             m_iPlayer1ClearCnt;
    int             m_iPlayer2ClearCnt;

    bool            m_bFristBlockCheck;
    int             m_iFirstBlockCnt;
    INTRECT         m_BlockRect[19][2];
    vector<int>     m_TileBlockVec[19];
    CObj*           m_pPlayer; 
    CObj*           m_pPlayer2;

    PLAYMODE*       m_pPlayMode;
};

