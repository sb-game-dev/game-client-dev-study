#include "pch.h"
#include "CBlock.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CItem.h"
CBlock::CBlock():m_bMove(false), m_fDstX(0.f), m_fDstY(0.f), m_eBT(BT_END)
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
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/block_v2.bmp", L"Push");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/block_v1.bmp", L"Break");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/Wall_f1.bmp", L"Wall");
}

int CBlock::Update()
{
	if (m_bDead == DEAD)
	{
		CreateItem();
		return DEAD;
	}
	if (m_bMove == true)
		Move();

	return NONEVENT;
}

void CBlock::LateUpdate()
{
}

void CBlock::Render(HDC hDC)
{
	HDC hMemDC = nullptr;

	switch (m_eBT)
	{
	case BT_PUSH:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"Push");
		break;
	case BT_BREAK:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"Break");
		break;
	case BT_WALL:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"Wall");
		break;
	}
	BitBlt(hDC,							// 목적지 DC
		m_tRect.left,					// 목적지 LEFT,RIGHT
		m_tRect.top-7,
		40,								// 원본 DC에서 가져올 영역의 크기(int)m_tInfo.fCX
		47,								//
		hMemDC,							// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"m_bMove : %d", m_bMove);
	//TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
}

void CBlock::Release()
{
}

void CBlock::SetMove(DIRECTION eDIR)
{
	m_bMove = true;
	m_eDirection = eDIR;
	m_fDstX = m_tInfo.fX;
	m_fDstY = m_tInfo.fY;

	switch (m_eDirection)
	{
	case DIR_LEFT:
		m_fDstX -= 40.f;
		break;
	case DIR_UP:
		m_fDstY -= 40.f;
		break;
	case DIR_RIGHT:
		m_fDstX += 40.f;
		break;
	case DIR_DOWN:
		m_fDstY += 40.f;
		break;
	}
}

void CBlock::Move()
{
	//뒤에 블록이 있으면 return + m_bMove = false; 설정하는 코드
	for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
	{
		if (pBlock == this) continue;
		if (fabsf(m_fDstX - pBlock->GetInfo().fX) <= 20.f
			&& fabsf(m_fDstY - pBlock->GetInfo().fY) <= 20.f)
		{
			m_bMove = false;
			return;
		}
	}
	
	if (m_tInfo.fX < m_fDstX) m_tInfo.fX		+= 2.0f;
	else if (m_tInfo.fX > m_fDstX) m_tInfo.fX	-= 2.0f;
	else if (m_tInfo.fY < m_fDstY) m_tInfo.fY	+= 2.0f;
	else if (m_tInfo.fY > m_fDstY)m_tInfo.fY	-= 2.0f;
	else m_bMove = false;
}

void CBlock::CreateItem()
{
	int iRandomNum = rand() % IT_END;
	CObj* pItem = CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY);
	switch (iRandomNum)
	{
	case IT_BOMB_UP:
		dynamic_cast<CItem*>(pItem)->SetType(IT_BOMB_UP);
		break;
	case IT_POWER_UP:
		dynamic_cast<CItem*>(pItem)->SetType(IT_POWER_UP);
		break;
	case IT_SPEED_UP:
		dynamic_cast<CItem*>(pItem)->SetType(IT_SPEED_UP);
		break;
	case IT_NEEDLE:
		dynamic_cast<CItem*>(pItem)->SetType(IT_NEEDLE);
		break;
	}
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, pItem);
}
