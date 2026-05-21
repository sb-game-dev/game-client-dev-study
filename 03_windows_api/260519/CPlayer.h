#pragma once
#include "CObj.h"
class CPlayer:public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	void Initialize()		override;
	int Update()			override;
	void LateUpdate()		override;
	void Render(HDC hDC)	override;
	void Release()			override;

public:
	void KeyDown();
	CObj* CreateBullet();

private:
	void MovePosin();
	
private:
	POINT m_tPosin;
};

