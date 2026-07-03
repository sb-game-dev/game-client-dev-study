#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO& GetInfo()const { return m_tInfo; }

public:
	virtual void Initialize()	PURE;
	virtual void Update()		PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

protected:
	INFO		m_tInfo;		

	float		m_fSpeed;
};

