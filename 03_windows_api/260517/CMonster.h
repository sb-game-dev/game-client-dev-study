#pragma once
#include "CObj.h"
class CMonster :public CObj
{
public:
	CMonster();
	~CMonster();

public:
	void Initialize()		override;
	void Update()			override;
	void Render(HDC hDC)	override;
	void Release()			override;

};

