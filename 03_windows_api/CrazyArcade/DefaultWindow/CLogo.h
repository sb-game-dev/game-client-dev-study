#pragma once
#include "CScene.h"
class CLogo :
    public CScene
{
public:
    CLogo();
    ~CLogo();
public:
    void Initialize()                   override;
    int Update()                        override;
    void LateUpdate()                   override;
    void Render(Graphics* _pGraphics)   override;
    void Release()                      override;
private:
    float       m_fAlpha;
    ULONGLONG   m_dwTime;
};

