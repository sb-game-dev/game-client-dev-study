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
	void SetBullet(list<CObj*>* BulletListp) { m_BulletListp = BulletListp; }
	void KeyDown();
private:
	list<CObj*>* m_BulletListp;
};

