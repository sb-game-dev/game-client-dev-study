#pragma once

#include "CGameObject.h"

namespace Engine
{
	class CPyramidCol;
	class CTransform;
	class CTexture;
	class CCameraCom;
	class CCollider;
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
	void			Mouse_Input(const _float& fTimeDelta);


	void			Shoot();
	void			MoveToTarget(const _float& fTimeDelta);

private:
	Engine::CPyramidCol*		m_pBufferCom;
	Engine::CTransform*			m_pTransformCom;
	Engine::CTexture*			m_pTextureCom;
	Engine::CCameraCom*			m_pCameraCom;
	Engine::CCollider*			m_pColliderCom;

	int			m_iBulletCnt;

	float		m_fSpeed;
	float		m_fNormalSpeed;
	float		m_fBoostSpeed;

	vector<_vec3> m_vTerrainVertex;
	vector<_vec3> m_vTerrainIndex;

	_vec3		m_vTargetPos;

	enum MOVE_STATE { GROUND, JUMP, FALL, MOVE_END };

	MOVE_STATE	m_eMoveState;

	_vec3		m_vGravity;
	float		m_fJumpPower;


public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void	Free();

	void			ReSetGravity() { m_vGravity = { 0,-9.8f,0 }; }

};

