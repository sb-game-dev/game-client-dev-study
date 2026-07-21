#include "pch.h"
#include "CBlock.h"
#include "CProtoMgr.h"

CBlock::CBlock(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CBlock::~CBlock()
{
}
HRESULT CBlock::Ready_GameObject()
{
	if (FAILED(AddComponent()))
	{
		return E_FAIL;
	}
	_vec3 vStartPos = { 5,5,5 };
	m_pTransformCom->Set_Pos(&vStartPos);
	return S_OK;
}
_int CBlock::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	return iExit;
}
void CBlock::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);
}
void CBlock::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pBufferCom->Render_Buffer();

}
CBlock* CBlock::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBlock* pBlock = new CBlock(pGraphicDev);
	if (FAILED(pBlock->Ready_GameObject()))
	{
		MSG_BOX("Block Failed");
		return nullptr;
	}
	return pBlock;
}
HRESULT CBlock::AddComponent()
{
	CComponent* pComponent = nullptr;
	pComponent = m_pBufferCom = dynamic_cast<CRcCol*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_RcCol"));
	if (nullptr == pComponent)
	{
		return E_FAIL;
	}
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer",pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
	{
		return E_FAIL;
	}
	m_mapComponent[ID_STATIC].insert({ L"Com_Transform",pComponent });

	return S_OK;
}

void CBlock::Free()
{
	Safe_Release(m_pBufferCom);

	Safe_Release(m_pTransformCom);

	CGameObject::Free();
}