#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"

CPlayer::CPlayer() :m_fRotateAngle(5.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	m_tInfo.vDir = { 0.f,-1.f,0.f };
	m_fSpeed = 10.f;
}

void CPlayer::Update()
{
	//m_tInfo.vDir = ::GetMouse() - m_tInfo.vPos;

	////float fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
	////
	////m_tInfo.vDir.x /= fLength;
	////m_tInfo.vDir.y /= fLength;
	////m_tInfo.vDir.z = 0.f;
	////
	////float fLength2 = sqrtf(m_tInfo.vLook.x * m_tInfo.vLook.x + m_tInfo.vLook.y * m_tInfo.vLook.y);
	////
	////m_tInfo.vLook.x /= fLength;
	////m_tInfo.vLook.y /= fLength;
	////m_tInfo.vLook.z = 0.f;
	//
	//// 벡터의 크기를 계산해주는 함수
	//// float	fLength = D3DXVec3Length(&m_tInfo.vDir);
	//
	//// 단위 벡터를 만들어주는 함수
	//// D3DXVec3Normalize(결과 값을 저장할 벡터의 주소, 단위 벡터로 변환할 벡터의 주소);
	//
	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	//D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	//
	//// float fDot = m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y;
	//
	//// 두 방향 벡터의 내적의 결과를 반환하는 함수
	//float	fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
	//
	//// 라디안 각도가 반환
	//float	fAngle = acosf(fDot);
	//
	//if (m_tInfo.vPos.y < GetMouse().y)
	//	fAngle = 2.f * D3DX_PI - fAngle;
	//
	//m_tInfo.vPos.x += cos(fAngle) * m_fSpeed;
	//m_tInfo.vPos.y -= sin(fAngle) * m_fSpeed;
	//
	//// 두 방향 벡터의 외적의 결과를 반환하는 함수
	//// D3DXVec3Cross(결과 값을 저장할 벡터의 주소, 방향 벡터 1의 주소, 방향 벡터 2의 주소)



	KeyInput();

	//FollowMouse();
}

void CPlayer::Render(HDC hDC)
{

	float fSize = 100.f;
	D3DXVECTOR3 vecRU = {
		m_tInfo.vPos.x - fSize/2 * (m_tInfo.vDir.y) + fSize / 2 * (m_tInfo.vDir.x),
		m_tInfo.vPos.y + fSize / 2 * (m_tInfo.vDir.x) + fSize / 2 * (m_tInfo.vDir.y),
		0.f };
	D3DXVECTOR3 vecLU = {
		vecRU.x + fSize * (m_tInfo.vDir.y),
		vecRU.y - fSize * (m_tInfo.vDir.x),
		0.f };
	D3DXVECTOR3 vecLD = {
		vecLU.x - fSize * (m_tInfo.vDir.x) ,
		vecLU.y - fSize * (m_tInfo.vDir.y),
		0.f };
	D3DXVECTOR3 vecRD = {
		vecLD.x - fSize * (m_tInfo.vDir.y),
		vecLD.y + fSize * (m_tInfo.vDir.x),
		0.f };
	Ellipse(hDC,
		vecRU.x - 5.f,
		vecRU.y - 5.f,
		vecRU.x + 5.f,
		vecRU.y + 5.f);
	MoveToEx(hDC, vecRU.x, vecRU.y, NULL);
	LineTo(hDC, vecLU.x, vecLU.y);
	LineTo(hDC, vecLD.x, vecLD.y);
	LineTo(hDC, vecRD.x, vecRD.y);
	LineTo(hDC, vecRU.x, vecRU.y);

	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y,NULL);
	LineTo(hDC, m_tInfo.vPos.x + m_tInfo.vDir.x * 100, m_tInfo.vPos.y + m_tInfo.vDir.y * 100);
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	
	if (GetAsyncKeyState('A'))
	{
		D3DXMATRIX matTemp;
		D3DXMatrixRotationZ(&matTemp, D3DXToRadian(-m_fRotateAngle));

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &matTemp);
	}
	if (GetAsyncKeyState('D'))
	{
		D3DXMATRIX matTemp;
		D3DXMatrixRotationZ(&matTemp, D3DXToRadian(m_fRotateAngle));

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &matTemp);

	}if (GetAsyncKeyState('W'))
	{
		D3DXMATRIX matTemp;

		D3DXMatrixTranslation(&matTemp,
			m_tInfo.vDir.x * m_fSpeed,
			m_tInfo.vDir.y * m_fSpeed,
			0.f);

		D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &matTemp);
	}
	if (GetAsyncKeyState('S'))
	{
		D3DXMATRIX matTemp;

		D3DXMatrixTranslation(&matTemp,
			m_tInfo.vDir.x * -m_fSpeed,
			m_tInfo.vDir.y * -m_fSpeed,
			0.f);

		D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &matTemp);

	}

}

void CPlayer::FollowMouse()
{
	m_tInfo.vDir = ::GetMouse() - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
}



