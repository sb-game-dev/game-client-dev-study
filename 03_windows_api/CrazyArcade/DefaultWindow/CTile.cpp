#include "pch.h"
#include "CTile.h"
#include "CImgMgr.h"

CTile::CTile():m_bHit(false), m_dwFrameCount(GetTickCount64())
{

}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Tile/tile.png", L"tile");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Tile/tile_hit.png", L"tile_hit");

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 11;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = TILECX;
	m_tFrame.iCY = TILECY;
	m_tFrame.dwSpeed = 50.f;
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
	return NOEVENT;
}

void CTile::LateUpdate()
{
}

void CTile::Render(Graphics* _pGraphics)
{
	Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);

	Rect rect = { int(m_tInfo.fX - (m_tFrame.iCX / 2)),
				int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
				m_tFrame.iCX,
				m_tFrame.iCY };

	_pGraphics->DrawImage(pImg, rect,
		m_tFrame.iCX * m_tFrame.iStart, m_tFrame.iCY * m_tFrame.iMotion,
		m_tFrame.iCX, m_tFrame.iCY,
		UnitPixel);
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
		m_pFrameKey = L"tile_hit";
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
void CTile::CheckFrame()
{
	if (m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
}
