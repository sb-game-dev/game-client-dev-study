#include "pch.h"
#include "CTile.h"
#include "CImgMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
CTile::CTile():m_bHit(false), m_dwFrameCount(GetTickCount64()), m_pImg(nullptr), m_eDirection(DIR_END), m_eCurMotion(IDLE),m_ePreMotion(MOTION_END)
{

}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile.bmp", L"tile");

	
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Tile/tile_hit.png", L"tile_hit");
	m_pImg = CImgMgr::GetInstance()->FindImg(L"tile");

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_pFrameKey = L"tile";
	m_fSpeed = 0;
	m_tFrame.iEnd = 11;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = TILECX;
	m_tFrame.iCY = TILECY;
	m_tFrame.dwSpeed = 123456789.f;
	m_tFrame.dwTime = GetTickCount64();
}

int CTile::Update()
{
	if (m_bDead == DEAD)
		return DEAD;

	if (m_eCurMotion == HIT)
	{
		MoveFrame();
		CheckFrame();
	}
	if (m_bMove == true)
		Move();
	return NOEVENT;
}

void CTile::LateUpdate()
{

}

void CTile::Render(HDC hDC)
{
	if (!lstrcmp(L"tile", m_pFrameKey) && m_tFrame.iStart <= 1)
		return;

	HDC hTile = CBmpMgr::GetInstance()->FindImage(L"tile");

	GdiTransparentBlt(hDC,			// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,				// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hTile,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,							// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CTile::Release()
{
}
void CTile::ChangeMotion()
{
	if (m_ePreMotion == m_eCurMotion)
		return;
	switch (m_eCurMotion)
	{
	case HIT:
		m_pImg = CImgMgr::GetInstance()->FindImg(L"tile_hit");
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 13;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 44;
		m_tFrame.iCY = 48;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	default:
		break;
	}
	m_ePreMotion = m_eCurMotion;
}
void CTile::Move()
{
	for (auto& pTile : CObjMgr::GetInstance()->GetTile())
	{
		if (pTile == this) continue;

		if (pTile->GetFrame().iStart >= 1
			&&fabsf(m_fDstX - pTile->GetInfo()->fX) <= 20.f
			&& fabsf(m_fDstY - pTile->GetInfo()->fY) <= 20.f)
		{
			m_bMove = false;
			return;
		}
	}

	if (m_tInfo.fX < m_fDstX) m_tInfo.fX += 2.0f;
	else if (m_tInfo.fX > m_fDstX) m_tInfo.fX -= 2.0f;
	else if (m_tInfo.fY < m_fDstY) m_tInfo.fY += 2.0f;
	else if (m_tInfo.fY > m_fDstY)m_tInfo.fY -= 2.0f;
	else m_bMove = false;
}
void CTile::SetMove(DIRECTION eDIR)
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
void CTile::CheckFrame()
{
	if (m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
}
