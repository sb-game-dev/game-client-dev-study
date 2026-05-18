#pragma once
#include "CObj.h"
class CBullet:public CObj
{
public :
	CBullet();
	~CBullet();

public:
	void Initialize()			override;
	bool Update()				override;
	void Render(HDC hDC)		override;
	void Release()				override;

public:

	// CObj을(를) 통해 상속됨
	void LateUpdate() override;
};

