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
	virtual void LateUpdate()	PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

	INFO		GetInfo() { return m_tInfo; }
protected:
	INFO		m_tInfo;		

	D3DXVECTOR3     m_vLocalBody[4];
	D3DXVECTOR3     m_vWorldBody[4];
	D3DXVECTOR3     m_vViewBody[4];

	float		m_fSpeed;
	float		m_fAngle;
};

