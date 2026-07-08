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
	MoveToEx(hDC, vecRU.x, vecRU.y, NULL);
	LineTo(hDC, vecLU.x, vecLU.y);
	LineTo(hDC, vecLD.x, vecLD.y);
	LineTo(hDC, vecRD.x, vecRD.y);
	LineTo(hDC, vecRU.x, vecRU.y);

	Ellipse(hDC,
		vecRU.x - 5.f,
		vecRU.y - 5.f,
		vecRU.x + 5.f,
		vecRU.y + 5.f);

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



