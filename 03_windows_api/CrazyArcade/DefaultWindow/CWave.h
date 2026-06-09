#pragma once
#include "CObj.h"
class CWave :
    public CObj
{
public:
    CWave();
    virtual~CWave();
public:
    void        Initialize()        override;
    int         Update()            override;
    void        LateUpdate()        override;
    void        Render(HDC hDC)     override;
    void        Release()           override;


public:
    void        CheckFrame();
    void        Spread(int iBombRange);
private:
    ULONGLONG   m_dwFrameCount;
};

