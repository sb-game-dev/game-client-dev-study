#include "pch.h"
#include "CBarrel.h"

CBarrel::CBarrel():dwTime(GetTickCount()), m_pPlayer(nullptr)
{
}

CBarrel::~CBarrel()
{
    Release();
}

void CBarrel::Initialize()
{
    m_tInfo.fCX = 30.f;
    m_tInfo.fCY = 30.f;
    //m_fRadian = 2 * PI * (3 / 8);
}

int CBarrel::Update()
{
    //// 1. 플레이어 주위로 회전
    if (dwTime + 10 < GetTickCount())
    {
        m_fRadian = (m_fRadian>=2*PI) ? 0.f : (m_fRadian + 0.05f) ;
        dwTime = GetTickCount();
    }

    //// 3. 포신 방향으로 플레이어 이동
    //if (GetAsyncKeyState('W'))
    //{
    //    if (m_fRadian <= PI * 0.5f)
    //        m_fRadian = (m_fRadian >= 2 * PI) ? 0.f : (m_fRadian + 0.05f);
    //    else if (m_fRadian >= PI * 0.5f && m_fRadian <= PI * 1.5f)
    //        m_fRadian = (m_fRadian <= 0) ? 0.f : (m_fRadian - 0.05f);
    //    else if (m_fRadian >= PI * 1.5f)
    //        m_fRadian = (m_fRadian >= 2 * PI) ? 0.f : (m_fRadian + 0.05f);
    //    else if(m_fRadian >=2.0f)
    //        m_fRadian = (m_fRadian >= 2 * PI) ? 0.f : (m_fRadian + 0.05f);
    //}
    //else if (GetAsyncKeyState('A'))
    //{
    //    if (0 <= m_fRadian && m_fRadian <= PI)
    //        m_fRadian = (m_fRadian >= 2 * PI) ? 0.f : (m_fRadian + 0.05f);
    //    else if (PI <= m_fRadian && m_fRadian <= PI * 2.0f)
    //        m_fRadian = (m_fRadian <= 0) ? 0.f : (m_fRadian - 0.05f);
    //}
    //else if (GetAsyncKeyState('S'))
    //{
    //    if (PI * 0.5f <= m_fRadian && m_fRadian <= PI * 1.5f)
    //        m_fRadian = (m_fRadian >= 2 * PI) ? 0.f : (m_fRadian + 0.05f);
    //    else if (0 <= m_fRadian && m_fRadian <= PI * 0.5f)
    //        m_fRadian = (m_fRadian <= -PI*0.5f) ? PI * 1.5f : (m_fRadian - 0.05f);
    //    else if(PI * 1.5f <= m_fRadian && m_fRadian <= PI * 2.0f)
    //        m_fRadian = (m_fRadian <= -PI * 0.5f) ? PI * 1.5f : (m_fRadian - 0.05f);
    //    else if (m_fRadian >= 2.0f || m_fRadian <= 0.f)
    //        m_fRadian = (m_fRadian <= -PI * 0.5f) ? PI * 1.5f : (m_fRadian - 0.05f);
    //}
    //else if (GetAsyncKeyState('D'))
    //{
    //    if (PI <= m_fRadian && m_fRadian <= PI * 2.f)
    //        m_fRadian = (m_fRadian >= 2 * PI) ? 0.f : (m_fRadian + 0.05f);
    //    else if (0 <= m_fRadian && m_fRadian <= PI)
    //        m_fRadian = (m_fRadian <= 0) ? 0.f : (m_fRadian - 0.05f);
    //}
    __super::UpdateRect();
    return NONEVENT;
}

void CBarrel::LateUpdate()
{
    m_tInfo.fX = m_pPlayer->GetInfo().fX + 100 * cos(m_fRadian);
    m_tInfo.fY = m_pPlayer->GetInfo().fY - 100 * sin(m_fRadian);
}

void CBarrel::Render(HDC hDC)
{
    Ellipse(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);
    TCHAR	szBuff[32] = L"";
    swprintf_s(szBuff, L"Radian : %f", m_fRadian);
    TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
}

void CBarrel::Release()
{
}
