#pragma once
#include "CObj.h"
class CBullet:public CObj
{
public :
	CBullet(const char& key);
	~CBullet();

public:
	void Initialize()			override;
	void Update()				override;
	void Render(HDC hDC)		override;
	void Release()				override;

public:
	bool GetIsDead() { return isDead; }
private:
	float m_fXSpeed;
	float m_fYSpeed;
	bool isDead;
};

