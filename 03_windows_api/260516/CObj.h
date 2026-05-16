#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()	PURE;
	virtual void Update()		PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

public:
	void SetPos(float fX,float fY){
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}

	void UpdateRect();

protected:
	INFO m_tInfo;
	RECT m_tRect;

	float m_fSpeed;
};

