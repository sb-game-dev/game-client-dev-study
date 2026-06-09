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
    void        Render(HDC hDC)                 override;
    void        Release()                       override;

public :
    void        CheckFrame();
    void        SetHit() { m_eCurMotion = HIT; ChangeMotion(); }
    void        ChangeMotion();
    void        Move();
    void        SetMove(DIRECTION eDIR);
private :
    MOTION      m_ePreMotion;
    MOTION      m_eCurMotion;
    bool        m_bHit;
    ULONGLONG   m_dwFrameCount;

    Image*      m_pImg;

    DIRECTION   m_eDirection;
    bool        m_bMove;
    float       m_fDstX;
    float       m_fDstY;
};

