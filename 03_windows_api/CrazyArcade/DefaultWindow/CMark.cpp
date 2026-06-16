#include "pch.h"
#include "CMark.h"
#include "CBmpMgr.h"

CMark::CMark()
{
}

CMark::~CMark()
{
}

void CMark::Initialize()
{
	m_tInfo.fCX = 7.f;
	m_tInfo.fCY = 7.f;
	m_tFrame.iStart = 0.f;
	m_tFrame.iEnd = 2;
	m_tFrame.iCX = m_tInfo.fCX;
	m_tFrame.iCY = m_tInfo.fCY;
}

int CMark::Update()
{
	return 0;
}

void CMark::LateUpdate()
{
}

void CMark::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;
	HDC hMark = CBmpMgr::GetInstance()->FindImage(L"Mark");
	BitBlt(hDC,							    // 목적지 DC
		m_tRect.left,		// 목적지 LEFT,RIGHT
		m_tRect.top,
		(int)m_tInfo.fCX,				// 원본 DC에서 가져올 영역의 크기
		(int)m_tInfo.fCY,
		hMark,							// 원본 DC
		m_tFrame.iStart * m_tFrame.iCX,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력
}

void CMark::Release()
{
}
