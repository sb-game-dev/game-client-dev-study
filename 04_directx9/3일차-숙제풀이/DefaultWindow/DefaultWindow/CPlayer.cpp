#include "pch.h"
#include "CPlayer.h"

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

	// 꼭짓점
	m_vOriginPoint[0] = { - 50.f,- 50.f,  0.f };
	m_vOriginPoint[1] = { + 50.f,- 50.f,  0.f };
	m_vOriginPoint[2] = { + 50.f,+ 50.f,  0.f };
	m_vOriginPoint[3] = { - 50.f,+ 50.f,  0.f };

	// 포신 
	m_vGunOriginPoint = { 0.f, - 100.f, 0.f };

	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 4.f;
}

void CPlayer::Update()
{
	KeyInput();

#pragma region 벡터만 이용한 숙제 풀이
	//for (int i = 0; i < 4; ++i)
	//{
	//	D3DXVECTOR3			vTemp = m_vOriginPoint[i];
	//	// 크기
	//	float fSizeX = 2.f;
	//	float fSizeY = 1.f;
	//	float fSizeZ = 1.f;
	//
	//	vTemp.x *= fSizeX;
	//	vTemp.y *= fSizeY;
	//	vTemp.z *= fSizeZ;
	//
	//	// 자전
	//	m_vPoint[i].x = vTemp.x * cos(m_fAngle) - vTemp.y * sin(m_fAngle);
	//	m_vPoint[i].y = vTemp.x * sin(m_fAngle) + vTemp.y * cos(m_fAngle);
	//
	//	// 이동
	//	m_vPoint[i] += m_tInfo.vPos;
	//}
	//
	//D3DXVECTOR3			vTemp = m_vGunOriginPoint;
	//
	//// 자전
	//m_vGunPoint.x = vTemp.x * cos(m_fAngle) - vTemp.y * sin(m_fAngle);
	//m_vGunPoint.y = vTemp.x * sin(m_fAngle) + vTemp.y * cos(m_fAngle);
	//
	//// 이동
	//m_vGunPoint += m_tInfo.vPos;
#pragma endregion

	D3DXMATRIX	matScale, matRotZ, matTrans;
	
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	
	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
	
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	
	m_vGunPoint = m_vGunOriginPoint;
	
	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);
	
	//x * cos(m_fAngle) - y * sin(m_fAngle), x * sin(m_fAngle) + y * cos(m_fAngle);

}

void CPlayer::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

		if (i > 0)
			continue;

		Ellipse(hDC, 
			m_vPoint[i].x - 5.f,
			m_vPoint[i].y - 5.f,
			m_vPoint[i].x + 5.f,
			m_vPoint[i].y + 5.f);
	}

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	// 포신 그리기

	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
	LineTo(hDC, m_vGunPoint.x, m_vGunPoint.y);

}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState('A'))
	{
		m_fAngle += D3DXToRadian(3.f);
	}
	if (GetAsyncKeyState('D'))
	{
		m_fAngle -= D3DXToRadian(3.f);
	}

	if (GetAsyncKeyState('W'))
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cos(m_fAngle) - m_tInfo.vLook.y * sin(m_fAngle);
		//m_tInfo.vDir.y = m_tInfo.vLook.x * sin(m_fAngle) + m_tInfo.vLook.y * cos(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}


	if (GetAsyncKeyState('S'))
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cos(m_fAngle) - m_tInfo.vLook.y * sin(m_fAngle);
		//m_tInfo.vDir.y = m_tInfo.vLook.x * sin(m_fAngle) + m_tInfo.vLook.y * cos(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

}



