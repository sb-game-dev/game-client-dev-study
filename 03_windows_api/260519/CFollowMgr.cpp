#include "pch.h"
#include "CFollowMgr.h"

void CFollowMgr::Follow(INFO tDst, INFO& tScr, float fSpeed)
{
    float fDstX = tDst.fX;
    float fDstY = tDst.fY;

    float fDeltaX = abs(fDstX - tScr.fX);
    float fDeltaY = abs(fDstY - tScr.fY);

    float fPlayerDistance = sqrtf(fDeltaX * fDeltaX + fDeltaY * fDeltaY);
    float m_fRadian = acosf(fDeltaX / fPlayerDistance);

    if (tScr.fY < fDstY)
    {
        // 1사분면
        if (fDstX < tScr.fX)
        {
            tScr.fX -= fSpeed * cosf(m_fRadian);
            tScr.fY += fSpeed * sinf(m_fRadian);
        }
        // 2사분면
        else
        {
            tScr.fX += fSpeed * cosf(m_fRadian);
            tScr.fY += fSpeed * sinf(m_fRadian);
        }
    }
    else
    {
        // 3사분면
        if (fDstX > tScr.fX)
        {
            tScr.fX += fSpeed * cosf(m_fRadian);
            tScr.fY -= fSpeed * sinf(m_fRadian);
        }
        // 4사분면
        else
        {
            tScr.fX -= fSpeed * cosf(m_fRadian);
            tScr.fY -= fSpeed * sinf(m_fRadian);
        }
    }
}
