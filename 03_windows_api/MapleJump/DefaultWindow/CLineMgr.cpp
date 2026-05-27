#include "pch.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"
CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::SetLine(float fPlayerX, float& fPlayerY, float fPrevX, float fPrevY)
{
	if (m_LineList.empty())
		return false;

	for (auto& pLine : m_LineList)
	{
		LINE tline = pLine->GetLine();
		
		if (fPlayerX >= tline.tLeft.fX &&
			fPlayerX <= tline.tRight.fX)
		{
			float x1 = tline.tLeft.fX;
			float y1 = tline.tLeft.fY;

			float x2 = tline.tRight.fX;
			float y2 = tline.tRight.fY;

			float fSlop = 0.f;

			if (x1 != x2)
				fSlop = (y1 - y2) / (x1 - x2);
			float y = fSlop * (fPlayerX - x1) + y1;
			float x = (y - y1) / fSlop;
			if (fabsf(y - fPlayerY) <= 20.f || (min(fPrevY, fPlayerY) <= y && y <= max(fPrevY, fPlayerY)))//fabsf(y - fPlayerY) <= 20.f
			{
				fPlayerY = y;
				return true;
			}
		}
	}
	return false;
}

bool CLineMgr::CheckRopeLine(float fPlayerX, float fPlayerY)
{
	if (m_RopeList.empty())
		return false;

	for (auto& pLine : m_RopeList)
	{
		LINE tline = pLine->GetLine();

		if (fPlayerY >= tline.tLeft.fY -2.f
			&&fPlayerY <= tline.tRight.fY +2.f
			&&fabsf(fPlayerX - tline.tLeft.fX)<=20.f)
		{
			//fPlayerX = tline.tLeft.fX;
			return true;
		}
	}
	return false;
}

bool CLineMgr::SetRopeLine(float& fPlayerX, float fPlayerY)
{
	if (m_RopeList.empty())
		return false;

	for (auto& pLine : m_RopeList)
	{
		LINE tline = pLine->GetLine();

		if (fPlayerY >= tline.tLeft.fY - 2.f
			&& fPlayerY <= tline.tRight.fY + 2.f
			&& fabsf(fPlayerX - tline.tLeft.fX) <= 20.f)
		{
			fPlayerX = tline.tLeft.fX;
			return true;
		}
	}
	return false;
}

bool CLineMgr::CheckDownJumpLine(float fPlayerX, float fPlayerY,CLine* pLine)
{
	LINE tline = pLine->GetLine();
	
	float x1 = tline.tLeft.fX;
	float y1 = tline.tLeft.fY;

	float x2 = tline.tRight.fX;
	float y2 = tline.tRight.fY;

	float fSlop = 0.f;

	if (x1 != x2)
		fSlop = (y1 - y2) / (x1 - x2);
	float y = fSlop * (fPlayerX - x1) + y1;

	if (y + 15.f <= fPlayerY)
	{
		return true;
	}
	return false;
}

CLine* CLineMgr::FindCurrentLine(float fPlayerX, float fPlayerY)
{
	for (auto& pLine : m_LineList)
	{
		LINE tline = pLine->GetLine();
		if (fPlayerX >= tline.tLeft.fX &&
			fPlayerX <= tline.tRight.fX)
		{
			float x1 = tline.tLeft.fX;
			float y1 = tline.tLeft.fY;

			float x2 = tline.tRight.fX;
			float y2 = tline.tRight.fY;

			float fSlop = 0.f;

			if (x1 != x2)
				fSlop = (y1 - y2) / (x1 - x2);
			float y = fSlop * (fPlayerX - x1) + y1;

			if (fabsf(y - fPlayerY) <= 2.f)
				return pLine;
		}
	}
	return nullptr;
}

void CLineMgr::Initialize()
{
	// 시작 지점
	m_LineList.push_back(new CLine(LINEPOINT{ 0.f,400.f }	, LINEPOINT{ 200.f, 400.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ 200.f,400.f }	, LINEPOINT{ 220.f, 450.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ 220.f, 450.f }, LINEPOINT{ 270.f, 450.f }));


	//< 22개 벽>
	
	float fB2Floor		= 500.f;
	float fB1Floor		= 450.f;
	float fFirstFloor	= 400.f;
	float fSecondFloor	= 350.f;
	float fThirdFloor	= 300.f;
	float fFourthFloor	= 250.f;

	float ListY[] = {
		fFirstFloor ,fSecondFloor ,fFirstFloor ,fFirstFloor,
		fSecondFloor,fSecondFloor ,fFirstFloor,fSecondFloor,
		fThirdFloor,  fSecondFloor ,fFirstFloor ,fSecondFloor ,
		fFirstFloor ,fSecondFloor ,fThirdFloor ,fFourthFloor,
		fFirstFloor ,fSecondFloor ,fThirdFloor,fFirstFloor ,
		fB1Floor,fB2Floor };
	float fX = 250.f;
	for (int i = 0; i < sizeof(ListY) / sizeof(ListY[0]); ++i)
	{
		m_LineList.push_back(new CLine(LINEPOINT{ fX,ListY[i]}, LINEPOINT{ fX+ 50.f, ListY[i] }));
		fX += 100.f;
	}
	// 쉬는 지점
	m_LineList.push_back(new CLine(LINEPOINT{ fX,fB2Floor }, LINEPOINT{ fX + 200.f, fB2Floor }));
	fX += 250;

	// 로프
	m_RopeList.push_back(new CLine(LINEPOINT{ fX,0 }, LINEPOINT{ fX, fB2Floor }));
	fX += 100.f;

	m_RopeList.push_back(new CLine(LINEPOINT{ fX,0 }, LINEPOINT{ fX, fFirstFloor }));
	fX += 100.f;

	m_RopeList.push_back(new CLine(LINEPOINT{ fX,0 }, LINEPOINT{ fX, fFirstFloor }));
	fX += 100.f;

	m_RopeList.push_back(new CLine(LINEPOINT{ fX,0 }, LINEPOINT{ fX, fSecondFloor - 50.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ fX-25.f,fSecondFloor }, LINEPOINT{ fX + 25.f, fSecondFloor }));
	fX += 100.f;

	
}
void CLineMgr::Update()
{
}
void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_LineList)
	{
		pLine->Render(hDC);
	}
	for (auto& pLine : m_RopeList)
	{
		pLine->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for (auto& pLine : m_LineList)
	{
		Safe_Delete(pLine);
	}
	m_LineList.clear();
	for (auto& pLine : m_RopeList)
	{
		Safe_Delete(pLine);
	}
	m_LineList.clear();
}
