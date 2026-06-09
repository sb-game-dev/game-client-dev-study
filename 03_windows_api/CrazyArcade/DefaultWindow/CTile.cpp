#include "pch.h"
#include "CTile.h"
#include "CImgMgr.h"
CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Tile/tile.png", L"tile");
}

int CTile::Update()
{
	return 0;
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
