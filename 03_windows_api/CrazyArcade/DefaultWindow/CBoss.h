#pragma once
#include "CObj.h"
class CBoss
	:public CObj
{
public:
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
};

