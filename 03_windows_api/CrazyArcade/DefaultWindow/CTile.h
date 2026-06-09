#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
public:
    CTile();
    virtual~CTile();
public:
    void        Initialize()                    override;
    int         Update()                        override;
    void        LateUpdate()                    override;
    void        Render(Graphics* _pGraphics)    override;
    void        Release()                       override;

public :
    void        CheckFrame();
    void        SetHit() { m_eCurMotion = HIT; ChangeMotion(); }
    void        ChangeMotion();
private :
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    bool        m_bHit;
    ULONGLONG   m_dwFrameCount;
};

