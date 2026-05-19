#include "pch.h"
#include "CObj.h"
CObj::CObj():m_fSpeed(0.f),m_bDead(NONEVENT), m_eDir(DIR_END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tStat, sizeof(STAT));
}
CObj::~CObj()
{
}

void CObj::UpdateRect()
{
	m_tRect.left	= LONG(m_tInfo.fX - m_tInfo.fCX/2.f);
	m_tRect.top		= LONG(m_tInfo.fY - m_tInfo.fCY/2.f);
	m_tRect.right	= LONG(m_tInfo.fX + m_tInfo.fCX/2.f);
	m_tRect.bottom	= LONG(m_tInfo.fY + m_tInfo.fCY/2.f);
}
