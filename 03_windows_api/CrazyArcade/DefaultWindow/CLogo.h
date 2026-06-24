#pragma once
#include "CScene.h"
class CLogo :
    public CScene
{
public:
    CLogo();
    ~CLogo();
public:
    void        Initialize()                   override;
    int         Update()                        override;
    void        LateUpdate()                   override;
    void        Render(HDC hDC)                override;
    void        Release()                      override;

private:
    void        CheckSceneFrame();
    void        ChangeScene();
};

