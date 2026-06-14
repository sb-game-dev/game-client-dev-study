#include "pch.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CWave.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CSoundMgr.h"
CBomb::CBomb():m_dwBombTime(GetTickCount64()), m_bPlayerCollision(false),m_iBombRange(0)
{
}

CBomb::~CBomb()
{
    Release();
}

void CBomb::Initialize()
{
    m_eRenderID = GAMEOBJECT;

    m_tInfo.fCX = 40.f;
    m_tInfo.fCY = 40.f;
    if (!lstrcmp(m_pFrameKey, L"BlueBubble"))
    {
        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 4;
        m_tFrame.iMotion = 0;
        m_tFrame.bLoop = true;
        m_tFrame.iCX = 46;
        m_tFrame.iCY = 46;
        m_tFrame.dwSpeed = (ULONGLONG)150.f;
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
        m_tFrame.dwSpeed = (ULONGLONG)150.f;
        m_tFrame.dwTime = GetTickCount64();
    }
    m_fSpeed = 10.f;
}

int CBomb::Update()
{
    if (m_bDead == DEAD)
        return DEAD;
    if (m_bCanMove == true)
        MoveBomb();
    else
    {

        m_tInfo.fX = AdjustPosX(m_tInfo.fX);
        m_tInfo.fY = AdjustPosY(m_tInfo.fY);

    }
    MoveFrame();
    return 0;
}

void CBomb::LateUpdate()
{
    if (m_dwBombTime + 2500 <= GetTickCount64())
    {
        CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CreateWave());
        dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front())->SetReduceBombCnt();
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
    //TCHAR	szBuff[32] = L"";
    //swprintf_s(szBuff, L"BombX : %.0f", m_tInfo.fX);
    //TextOut(hDC, 50, 100, szBuff, lstrlen(szBuff));
    //TCHAR	szBuff2[32] = L"";
    //swprintf_s(szBuff2, L"BombY : %.0f", m_tInfo.fY);
    //TextOut(hDC, 50, 125, szBuff2, lstrlen(szBuff2));
}

void CBomb::Release()
{
}


CObj* CBomb::CreateWave()
{
    CObj* pWave = CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY,L"WaveCenter");

    dynamic_cast<CWave*>(pWave)->Spread(m_iBombRange);

    CSoundMgr::Get_Instance()->PlaySound(L"ExplodeBomb2.wav", BOMB_EXPLODE, 0.3f);
    return pWave;
}

void CBomb::MoveBomb()
{
    if (m_tInfo.fX<=40 || m_tInfo.fX>=600 || m_tInfo.fY <=60 || m_tInfo.fY >= 540)
    {
        m_bCanMove = false;
        return;
    }
    switch (m_eDIR)
    {
    case DIR_UP:
        m_tInfo.fY -= m_fSpeed;
        break;
    case DIR_DOWN:
        m_tInfo.fY += m_fSpeed;
        break;
    case DIR_LEFT:
        m_tInfo.fX -= m_fSpeed;
        break;
    case DIR_RIGHT:
        m_tInfo.fX += m_fSpeed;
        break;
    default:
        break;
    }
}