#pragma once
#include "CScene.h"
class CStage5 :
    public CScene
{
public:
    CStage5();
    virtual~CStage5();

public:
    void    Initialize()                override;
    int     Update()                    override;
    void    LateUpdate()                override;
    void    Render(HDC hDC)             override;
    void    Release()                   override;


private:
    HDC             m_hBackGround;
};
