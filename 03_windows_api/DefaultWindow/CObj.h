#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void SetPos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}
	INFO GetInfo()
	{
		return m_tInfo;
	}

public:
	virtual void Initialize()	PURE;
	virtual void Update()		PURE;
	virtual void Render(HDC hDC)PURE; // 그리기를 할 때는 dc가 필요하다 dc는 메인함수에 있기 때문에 매개변수로 입력받아서 사용
	virtual void Release()		PURE;

public:
	void		UpdateRect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	float		m_fSpeed;
};

