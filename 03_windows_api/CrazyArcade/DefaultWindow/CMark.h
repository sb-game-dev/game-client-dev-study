#pragma once
#include "CObj.h"
class CMark :
    public CObj
{
public:
    CMark();
    ~CMark();
public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override;
};

