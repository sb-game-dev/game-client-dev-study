#pragma once
#include "CGameObject.h"
namespace Engine
{
	class CRcTex;
	class CCubeTex;
	class CTerainTex;
	class CTransform;
	class CTexture;
}

class CTerain : public CGameObject
{
private:
	explicit CTerain(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTerain();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			_int		Update_GameObject(const _float& fTimeDelta);
	virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void		Render_GameObject();

private:
	HRESULT			Add_Component();

private:
	Engine::CTerainTex* m_pBufferCom;
	Engine::CTransform* m_pTransformCom;

	Engine::CTexture* m_pTextureCom;

public:
	static CTerain* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void	Free();

};

