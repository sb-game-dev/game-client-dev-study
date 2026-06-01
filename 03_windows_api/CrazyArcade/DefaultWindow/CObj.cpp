#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f),m_bDead(NONEVENT), m_eDirection(DIR_END), m_dwAniTime(GetTickCount()), m_iFrame(0), m_pFrameKey(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tRenderInfo, sizeof(m_tRenderInfo));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
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
	if (m_tFrame.dwTime + m_tFrame.dwSpeed <= GetTickCount())
	{
		m_tFrame.iStart= (m_tFrame.iStart + 1)% m_tFrame.iEnd;

		m_tFrame.dwTime = GetTickCount();

	}
}
