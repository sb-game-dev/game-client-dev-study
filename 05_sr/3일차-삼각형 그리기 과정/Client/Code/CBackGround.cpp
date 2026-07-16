#include "pch.h"
#include "CBackGround.h"
#include "CTriCol.h"
#include "CRectCol.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CBackGround::~CBackGround()
{
}

HRESULT CBackGround::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;

	//m_pBufferCom = Engine::CTriCol::Create(m_pGraphicDev);
	//if (nullptr == m_pBufferCom)
	//	return E_FAIL;

	m_vScale = { 1,1,1 };
	m_vPos = { 0,0,0 };
	m_vRot = { 0,0,0 };
	m_vLook = { 0,0,1 };
	m_vDir = { 0,0,0 };


	m_pRectBufferCom = Engine::CRectCol::Create(m_pGraphicDev);
	if (nullptr == m_pRectBufferCom)
		return E_FAIL;

	return S_OK;
}

_int CBackGround::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	KetInput();
	return iExit;
}

void CBackGround::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CBackGround::Render_GameObject()
{
	_matrix matWorld,matRotX,matRotY,matTrans;

	D3DXMatrixRotationX(&matRotX, m_vRot.x);
	D3DXMatrixRotationY(&matRotY, m_vRot.y);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);



	D3DXMatrixIdentity(&matWorld);
	matWorld = matRotX* matRotY * matTrans;

	D3DXVec3TransformNormal(&m_vDir, &m_vLook, &matWorld);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//m_pBufferCom->Render_Buffer();
	m_pRectBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CBackGround::Add_Component()
{
	return S_OK;
}

void CBackGround::KetInput()
{
	if (GetAsyncKeyState('W'))
		m_vRot.x += D3DXToRadian(3.f);
	if (GetAsyncKeyState('S'))
		m_vRot.x += D3DXToRadian(3.f);
	if (GetAsyncKeyState('A'))
		m_vRot.y += D3DXToRadian(3.f);
	if (GetAsyncKeyState('D'))
		m_vRot.y += D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_UP))
		m_vPos += m_vDir;
	if (GetAsyncKeyState(VK_DOWN))
		m_vPos -= m_vDir;
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBackGround* pBackGround = new CBackGround(pGraphicDev);

	if (FAILED(pBackGround->Ready_GameObject()))
	{
		Safe_Release(pBackGround);
		MSG_BOX("pBackGround Create Failed");
		return nullptr;
	}

	return pBackGround;
}

void CBackGround::Free()
{
	//Safe_Release(m_pBufferCom);
	Safe_Release(m_pRectBufferCom);

	CGameObject::Free();
}
