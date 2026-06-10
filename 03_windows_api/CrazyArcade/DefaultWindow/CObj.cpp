#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f), m_pFrameKey(nullptr), m_bDead(false), m_bHit(false), m_eRenderID(RENDER_END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::MoveFrame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed <= GetTickCount64())
	{
		m_tFrame.dwTime = GetTickCount64();
		++m_tFrame.iStart;
		if (m_tFrame.bLoop)
			m_tFrame.iStart %= m_tFrame.iEnd;
		else if (m_tFrame.iStart >= m_tFrame.iEnd)
			m_tFrame.iStart -= 1;
	}
}
