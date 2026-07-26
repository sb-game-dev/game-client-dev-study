#pragma once

#include "CGameObject.h"

namespace Engine
{
	class CPyramidCol;
	class CTransform;
	class CTexture;
}

class CPlayer : public CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			_int		Update_GameObject(const _float& fTimeDelta);
	virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void		Render_GameObject();

private:
	HRESULT			Add_Component();
	void			Key_Input(const _float& fTimeDelta);
	void			Key_Input2(const _float& fTimeDelta);
	void			Shoot();

private:
	Engine::CPyramidCol*				m_pBufferCom;
	Engine::CTransform*			m_pTransformCom;
	Engine::CTexture*			m_pTextureCom;

	float m_fSpeed;
	float m_fNormalSpeed;
	float m_fBoostSpeed;

	int	  m_iBulletCnt;
public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void	Free();

};

