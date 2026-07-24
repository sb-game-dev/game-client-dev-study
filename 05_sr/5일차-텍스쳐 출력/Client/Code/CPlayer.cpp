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

	return iExit;
}

void CPlayer::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);

	Key_Input(fTimeDelta);

	_vec3 vTemp;
	m_pTransformCom->Get_Info(INFO_UP, &vTemp);
}

void CPlayer::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pTextureCom->Set_Texture(0);

	m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_PlayerTexture"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

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
