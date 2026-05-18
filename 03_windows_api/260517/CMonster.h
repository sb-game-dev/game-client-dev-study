#pragma once
#include "CObj.h"
class CMonster :public CObj
{
public:
	CMonster();
	~CMonster();

public:
	void Initialize()		override;
	bool Update()			override;
	void Render(HDC hDC)	override;
	void Release()			override;

	// CObj을(를) 통해 상속됨
	void LateUpdate() override;

};

