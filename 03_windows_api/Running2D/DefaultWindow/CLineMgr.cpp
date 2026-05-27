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
	m_LineList.push_back(new CLine(LINEPOINT{ 0.f,400.f }, LINEPOINT{ 250.f, 400.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ 250.f,400.f }, LINEPOINT{ 550.f, 200.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ 550.f,200.f }, LINEPOINT{ 800.f, 200.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ 550.f,100.f }, LINEPOINT{ 800.f, 100.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ 550.f,400.f }, LINEPOINT{ 800.f, 400.f }));
	m_LineList.push_back(new CLine(LINEPOINT{ 350.f,500.f }, LINEPOINT{ 800.f, 500.f }));


	m_RopeList.push_back(new CLine(LINEPOINT{ 400.f,300.f }, LINEPOINT{ 400.f,400.f }));
	m_RopeList.push_back(new CLine(LINEPOINT{ 600.f,100.f }, LINEPOINT{ 600.f,300.f }));
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
