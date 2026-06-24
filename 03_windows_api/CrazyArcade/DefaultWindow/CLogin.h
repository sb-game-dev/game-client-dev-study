#pragma once
#include "CScene.h"
#include "CObj.h"
class CLogin :
    public CScene
{
public:
    CLogin();
    virtual~CLogin();

public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override;

private:
    void        CheckSceneFrame();
    void        ChangeScene();

private:
    CObj*       m_pButton2p;
    CObj*       m_pButton1p;
    bool        m_bShow2pControls;
    bool        m_bClickButton2P;
};

