#include "pch.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CWave.h"
#include "CAbstractFactory.h"
CBomb::CBomb():m_dwBombTime(GetTickCount64())
{
}

CBomb::~CBomb()
{
    Release();
}

void CBomb::Initialize()
{
    CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Bomb/BlueBubble.bmp", L"BlueBubble");
    CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Bomb/RainbowBubble.bmp", L"RainbowBubble");
    m_tInfo.fCX = 40.f;
    m_tInfo.fCY = 40.f;
    //MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OKCANCEL);
    if (!lstrcmp(m_pFrameKey, L"BlueBubble"))
    {
        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 4;
        m_tFrame.iMotion = 0;
        m_tFrame.bLoop = true;
        m_tFrame.iCX = 46;
        m_tFrame.iCY = 46;
        m_tFrame.dwSpeed = 150.f;
        m_tFrame.dwTime = GetTickCount64();
    }
    else
    {
        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 4;
        m_tFrame.iMotion = 0;
        m_tFrame.bLoop = true;
        m_tFrame.iCX = 56;
        m_tFrame.iCY = 54;
        m_tFrame.dwSpeed = 150.f;
        m_tFrame.dwTime = GetTickCount64();
    }
}

int CBomb::Update()
{
    if (m_bDead == DEAD)
        return DEAD;
   
    MoveFrame();
    return 0;
}

void CBomb::LateUpdate()
{
    if (m_dwBombTime + 1500 <= GetTickCount())
    {
        CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CreateWave());
        m_bDead = DEAD;
    }
}

void CBomb::Render(HDC hDC)
{
    HDC hTile = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
    //if(hTile)
    //    MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OKCANCEL);
    GdiTransparentBlt(hDC,			// 목적지 DC
        int(m_tInfo.fX - (m_tFrame.iCX * 0.5)),
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

void CBomb::Release()
{
}


CObj* CBomb::CreateWave()
{
    CObj* pWave = CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY,L"WaveCenter");

    dynamic_cast<CWave*>(pWave)->Spread(m_iBombRange);
    return pWave;
}
