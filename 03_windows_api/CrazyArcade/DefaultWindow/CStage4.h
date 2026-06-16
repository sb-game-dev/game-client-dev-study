#pragma once
#include "CScene.h"
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
    void    InsertImg()                 override;
};

