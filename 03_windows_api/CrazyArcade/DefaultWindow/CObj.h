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
	void		Update_Rect();

protected:
	INFO		m_tInfo;		
	RECT		m_tRect;		

	float		m_fSpeed;
};

