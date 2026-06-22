#pragma once
#include "CObj.h"
class CUI :
    public CObj
{
public:
    CUI();
    ~CUI();
public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override;
};

