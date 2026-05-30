#include "pch.h"
#include "CBlock.h"
#include "CBmpMgr.h"
CBlock::CBlock()
{
}

CBlock::~CBlock()
{
	Release();
}

void CBlock::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/block_v2.bmp", L"Block");
}

int CBlock::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	return NONEVENT;
}

void CBlock::LateUpdate()
{
}

void CBlock::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(L"Block");
	BitBlt(hDC,							// 목적지 DC
		m_tRect.left,					// 목적지 LEFT,RIGHT
		m_tRect.top-7,
		40,								// 원본 DC에서 가져올 영역의 크기(int)m_tInfo.fCX
		47,								//
		hMemDC,							// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력
}

void CBlock::Release()
{
}
