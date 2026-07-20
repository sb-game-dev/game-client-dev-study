#pragma once
#include "CGameObject.h"
namespace Engine
{
	class CRcCol;
	class CTransform;
}
class CBlock : public CGameObject
{
private:
	explicit CBlock(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBlock();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			_int		Update_GameObject(const _float& fTimeDelta);
	virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void		Render_GameObject();

private:
	Engine::CRcCol*		m_pBufferCom;
	Engine::CTransform* m_pTransformCom;

public:
	static CBlock* Create(LPDIRECT3DDEVICE9 pGraphicDev);

	virtual void Free();
	virtual HRESULT AddComponent();
};

