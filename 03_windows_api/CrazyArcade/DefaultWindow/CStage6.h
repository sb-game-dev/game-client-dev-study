#pragma once
#include "CScene.h"
#include "CObj.h"
#include "CLine.h"
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

    HDC			m_hDC;

    HDC			m_memDC;
    HBITMAP		m_Bit;
    HBITMAP		m_Old;

    HDC             m_hBackGround;

    CObj*               m_pPlayer;


    list<CLine*>*		m_pLineList;
    list<CLine*>*		m_pRopeList;
    
};

