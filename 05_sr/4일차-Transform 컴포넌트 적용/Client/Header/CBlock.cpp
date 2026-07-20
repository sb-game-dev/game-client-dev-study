#include "pch.h"
#include "CBlock.h"

CBlock::CBlock(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CBlock::~CBlock()
{
}
HRESULT CBlock::Ready_GameObject()
{
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
}
CBlock* CBlock::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBlock* pBlock = new CBlock(pGraphicDev);
	if (FAILED(pBlock->AddComponent()))
	{
		MSG_BOX("Block Failed");
		return nullptr;
	}
	return pBlock;
}
HRESULT CBlock::AddComponent()
{

}

void CBlock::Free()
{
	CGameObject::Free();
}