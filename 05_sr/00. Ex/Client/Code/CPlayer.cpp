#include "pch.h"
#include "CPlayer.h"
#include "CProtoMgr.h"
#include "CBullet.h"
#include "CManagement.h"
#include "CKeyMgr.h"
CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;
	m_pTransformCom->Rotation(ROT_X, 90);
	m_fNormalSpeed = 10.f;
	m_fBoostSpeed = 20.f;
	m_fSpeed = m_fNormalSpeed;
	m_iBulletCnt = 0;
	return S_OK;
}

_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	_vec3 vPlayerPos;
	_vec3 vPlayerLook;
	_vec3 vMousePos;

	m_pTransformCom->Get_Info(INFO_POS, &vPlayerPos);

	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	vMousePos = _vec3((float)pt.x, (float)pt.y, 0.f);

	//m_pCameraCom->MouseControl(&vPlayerPos,&vPlayerLook,&vMousePos);

	//_vec3	vLookTarget;
	//vLookTarget = vPlayerPos + vPlayerLook;
	//
	//_matrix matRot = *(m_pTransformCom->Compute_Lookattarget(&vLookTarget));


	//Key_Input(fTimeDelta);
	Key_Input2(fTimeDelta);

	return iExit;
}

void CPlayer::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);

	CTerrainTex* pTerrainCom = dynamic_cast<CTerrainTex*>
		(CManagement::GetInstance()->Get_Component(ID_STATIC, L"Environment_Layer", L"Terrain", L"Com_Buffer"));

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	if (vPos.x > 0 && vPos.x < 129 && vPos.z < 0 && vPos.z > -129)
	{
		float fY = pTerrainCom->GetHeight(vPos.x, vPos.z);
		m_pTransformCom->m_vInfo[INFO_POS].y = fY;
	}
}

void CPlayer::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	m_pBufferCom->Render_Buffer();
}

HRESULT CPlayer::Add_Component()
{
	Engine::CComponent* pComponent = nullptr;

	// RcCol
	pComponent = m_pBufferCom = dynamic_cast<CPyramidCol*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Pyramid"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	/////////////////////////////////////////////////////////////////
	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	// Camera
	pComponent = m_pCameraCom = dynamic_cast<CCameraCom*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Camera"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Camera", pComponent });

	// Texture
	//pComponent = m_pTextureCom = dynamic_cast<CTexture*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_PlayerTexture"));
	//if (nullptr == pComponent)
	//	return E_FAIL;
	//
	//m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	_vec3	vLook;
	m_pTransformCom->Get_Info(INFO_UP, &vLook);

	if (GetAsyncKeyState(VK_UP))
	{
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vLook, &vLook), m_fSpeed, fTimeDelta);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vLook, &vLook), -m_fSpeed, fTimeDelta);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_pTransformCom->Rotation(ROT_Y, -180.f * fTimeDelta);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_pTransformCom->Rotation(ROT_Y, 180.f * fTimeDelta);
	}

	if (GetAsyncKeyState('W'))
	{
		m_pTransformCom->Rotation(ROT_X, -80.f * fTimeDelta);
	}

	if (GetAsyncKeyState('S'))
	{
		m_pTransformCom->Rotation(ROT_X, 80.f * fTimeDelta);
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
	{
		Shoot();
	}

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		m_fSpeed = m_fBoostSpeed;
	}
	else
	{
		m_fSpeed = m_fNormalSpeed;
	}
}

void CPlayer::Key_Input2(const _float& fTimeDelta)
{
	_vec3	vCameraLook;
	_vec3	vPlayerLook;

	CTransform* pCameraTransformCom = dynamic_cast<CTransform*>
		(CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"Environment_Layer", L"Camera", L"Com_Transform"));
	
	vCameraLook = pCameraTransformCom->m_vInfo[INFO_LOOK];
	vPlayerLook = m_pTransformCom->m_vInfo[INFO_UP];
	
	if (GetAsyncKeyState('W'))
	{
		vCameraLook.y = 0;
		vPlayerLook.y = 0;
		
		_vec3 cross;
		D3DXVec3Cross(&cross, &vPlayerLook, &vCameraLook);

		float fAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&vPlayerLook, &vPlayerLook),
										 D3DXVec3Normalize(&vCameraLook, &vCameraLook)));
		
		if (D3DXToDegree(fAngle) > 1)
		{
			if (cross.y < 0) fAngle *= -1;

			m_pTransformCom->Rotation(ROT_Y, D3DXToDegree(fAngle));
		}
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vCameraLook, &vCameraLook), m_fSpeed, fTimeDelta);
	}

	if (GetAsyncKeyState('S'))
	{
		_vec3 cross;
		D3DXVec3Cross(&cross, &vPlayerLook, &vCameraLook);

		float fAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&vPlayerLook, &vPlayerLook),
			D3DXVec3Normalize(&vCameraLook, &vCameraLook)));
		if (cross.y < 0) fAngle *= -1;

		m_pTransformCom->Rotation(ROT_Y, fAngle);
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vCameraLook, &vCameraLook), -m_fSpeed, fTimeDelta);
	}

	if (CKeyMgr::GetInstance()->KeyPressing(VK_SPACE))
	{

	}
	//if (GetAsyncKeyState('A'))
	//{
	//	m_pTransformCom->Rotation(ROT_Y, -180.f * fTimeDelta);
	//}
	//
	//if (GetAsyncKeyState('S'))
	//{
	//	m_pTransformCom->Rotation(ROT_Y, 180.f * fTimeDelta);
	//}
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		m_fSpeed = m_fBoostSpeed;
	}
	else
	{
		m_fSpeed = m_fNormalSpeed;
	}
}

void CPlayer::Shoot()
{
	_vec3 vDir;
	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO_UP, &vDir);
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	vPos += vDir * 4;
	CGameObject* pBullet = CBullet::Create(m_pGraphicDev, vPos, vDir);

	CLayer* pLayer = CManagement::GetInstance()->Get_Layer(L"Environment_Layer");
	if (pLayer == nullptr)
	{
		MSG_BOX("Shoot and Layer Create Failed");
		return;
	}
	++m_iBulletCnt;

	const _tchar* szBuff = L"Bullet" + m_iBulletCnt;
	//cout << szBuff << endl;
	pLayer->Add_GameObject(szBuff, pBullet);
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pPlayer = new CPlayer(pGraphicDev);

	if (FAILED(pPlayer->Ready_GameObject()))
	{
		Safe_Release(pPlayer);
		MSG_BOX("pPlayer Create Failed");
		return nullptr;
	}

	return pPlayer;
}

void CPlayer::Free()
{

	CGameObject::Free();
}
