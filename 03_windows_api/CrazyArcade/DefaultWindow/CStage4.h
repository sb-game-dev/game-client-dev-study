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
    bool    CheckRange(INTRECT tIntRect, CObj* pMark);
    void    CheckSceneFrame();
    void    ChangeScene();
    void    DestroyMonster();
private:
    HDC             m_hBackGround;
    list<CObj*>*    m_pMarkList;
    vector<CObj*>*  m_pTileVector;

    bool            m_bBlockCheck[19];
    int             m_iBlockCnt[19];
    int             m_iBlockCntAnswer[19];
    int             m_iClearRangeCnt;

    bool            m_bFristBlockCheck;
    int             m_iFirstBlockCnt;
    INTRECT         m_BlockRect[19][2];
    vector<int>     m_TileBlockVec[19];
    CObj*           m_pPlayer;
};

