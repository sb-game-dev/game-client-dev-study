#include "pch.h"
#include "CBomb.h"

CBomb::CBomb():m_dwTime(GetTickCount()), m_eState(ST_READY)
{
}

CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
}

int CBomb::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	if (m_eState == ST_READY && m_dwTime + 1500 <= GetTickCount())
	{
		m_dwTime = GetTickCount();
		m_eState = ST_EXPLODE_READY;
	}
	if (m_eState == ST_EXPLODE_ING && m_dwTime + 500 <= GetTickCount())
	{
		m_eState = ST_END;
	}
	__super::UpdateRect();
	return NONEVENT;
}

void CBomb::LateUpdate()
{
	if (m_eState == ST_END)
		m_bDead = DEAD;
}

void CBomb::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CBomb::Release()
{
}
