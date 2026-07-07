#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"

CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_fSpeed = 4.f;
}

void CPlayer::Update()
{
	m_tInfo.vDir = ::GetMouse() - m_tInfo.vPos;

	//float fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
	//
	//m_tInfo.vDir.x /= fLength;
	//m_tInfo.vDir.y /= fLength;
	//m_tInfo.vDir.z = 0.f;
	//
	//float fLength2 = sqrtf(m_tInfo.vLook.x * m_tInfo.vLook.x + m_tInfo.vLook.y * m_tInfo.vLook.y);
	//
	//m_tInfo.vLook.x /= fLength;
	//m_tInfo.vLook.y /= fLength;
	//m_tInfo.vLook.z = 0.f;

	// 벡터의 크기를 계산해주는 함수
	// float	fLength = D3DXVec3Length(&m_tInfo.vDir);

	// 단위 벡터를 만들어주는 함수
	// D3DXVec3Normalize(결과 값을 저장할 벡터의 주소, 단위 벡터로 변환할 벡터의 주소);
	
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	// float fDot = m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y;

	// 두 방향 벡터의 내적의 결과를 반환하는 함수
	float	fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	// 라디안 각도가 반환
	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < GetMouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cos(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sin(fAngle) * m_fSpeed;

	// 두 방향 벡터의 외적의 결과를 반환하는 함수
	// D3DXVec3Cross(결과 값을 저장할 벡터의 주소, 방향 벡터 1의 주소, 방향 벡터 2의 주소)

}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 
		m_tInfo.vPos.x - 50.f, 
		m_tInfo.vPos.y - 50.f,
		m_tInfo.vPos.x + 50.f,
		m_tInfo.vPos.y + 50.f);
}

void CPlayer::Release()
{
}



