#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CCameraMgr.h"

CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{

	m_vLocalBody[0] = { -50.f,	-50.f,	0.f };
	m_vLocalBody[1] = { 50.f,	-50.f,	0.f };
	m_vLocalBody[2] = { 50.f,	50.f,	0.f };
	m_vLocalBody[3] = { -50.f,	50.f,	0.f };

	m_tInfo.vPos = { 0.f, 0.f, 0.f };

	m_tInfo.vLook = { 0.f,-1.f,0.f };

	m_tInfo.vDir = { 0.f,1.f,0.f };
	m_fSpeed = 1.f;

	
}

void CPlayer::Update()
{
	D3DXMATRIX matView;
	matView = CCameraMgr::GetInstance()->GetMatView();
	m_tInfo.matView = matView;

	KeyInput();
}

void CPlayer::LateUpdate()
{
	// 월드 변환
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vWorldBody[i], &m_vLocalBody[i], &m_tInfo.matWorld);

	// 뷰 변환
	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vViewBody[i], &m_vWorldBody[i], &m_tInfo.matView);

	for (int i = 0; i < 4; ++i) {
		m_vViewBody[i] += {WINCX / 2, WINCY / 2, 0};
	}

}

void CPlayer::Render(HDC hDC)
{
	MoveToEx(hDC, m_vViewBody[0].x, m_vViewBody[0].y, NULL);
	for (int i = 0; i < 4; ++i)
	{
		//cout << i << ": " << m_vViewBody[i].x << ", " << m_vViewBody[i].y << endl;
		LineTo(hDC, m_vViewBody[i].x, m_vViewBody[i].y);
		if (i < 2)
		{
			Ellipse(hDC,
				m_vViewBody[i].x - 5.f,
				m_vViewBody[i].y - 5.f,
				m_vViewBody[i].x + 5.f,
				m_vViewBody[i].y + 5.f);
		}
	}
	LineTo(hDC, m_vViewBody[0].x, m_vViewBody[0].y);
	
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState('A'))
		m_fAngle -= D3DXToRadian(1.f);
	else if (GetAsyncKeyState('D'))
		m_fAngle += D3DXToRadian(1.f);

	if (GetAsyncKeyState('W'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matView);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	if (GetAsyncKeyState('S'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matView);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}
	
}



