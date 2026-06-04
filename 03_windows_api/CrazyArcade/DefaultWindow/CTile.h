#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
public:
    CTile();
    virtual~CTile();

public:
    void    NextDrawID();

    void    SetDrawID(TILEID eID) { m_eDrawID = eID; }
    void    SetFrameKey();

    TILEID     GetDrawID() { return m_eDrawID; }
    int     GetOption() { return m_iOption; }

public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override;

private:
    TILEID      m_eDrawID;
    int         m_iOption;
};

