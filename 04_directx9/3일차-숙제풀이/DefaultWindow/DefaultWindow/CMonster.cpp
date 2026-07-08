#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
}

void CMonster::Update()
{

}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tInfo.vPos.x - 50.f,
		m_tInfo.vPos.y - 50.f,
		m_tInfo.vPos.x + 50.f,
		m_tInfo.vPos.y + 50.f);
}

void CMonster::Release()
{
}
