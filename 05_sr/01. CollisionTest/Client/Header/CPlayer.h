#pragma once

#include "CGameObject.h"
#include "Engine_Enum.h"

namespace Engine
{
	class CPyramidCol;
	class CTransform;
	class CTexture;
	class CCameraCom;
	class CCollider;
	class CCube_Collider;
	class CSphere_Collider;
	class CCubeTex;
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
	HRESULT			Add_PointLight();
	void			Key_Input(const _float& fTimeDelta);
	void			Key_Input2(const _float& fTimeDelta);
	void			Mouse_Input(const _float& fTimeDelta);

	void			Shoot();
	void			MoveToTarget(const _float& fTimeDelta);
	_vec3			GetRayPickPos();

private:
	Engine::CCubeTex*		m_pBufferCom;
	Engine::CTransform*			m_pTransformCom;
	Engine::CTexture*			m_pTextureCom;
	Engine::CCameraCom*			m_pCameraCom;
	Engine::CCube_Collider*		m_pColliderCom;
	//Engine::CSphere_Collider*	m_pColliderCom;

	int			m_iBulletCnt;

	float		m_fSpeed;
	float		m_fNormalSpeed;
	float		m_fBoostSpeed;

	vector<_vec3> m_vTerrainVertex;
	vector<_vec3> m_vTerrainIndex;

	_vec3			m_vLightPos;
	D3DLIGHT9       m_tLightInfo;


	_vec3		m_vTargetPos;

	MOVE_STATE	m_eMoveState;

	_vec3		m_vGravity;
	float		m_fJumpPower;

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

	void	SetMoveState(MOVE_STATE eMove) { m_eMoveState = eMove; }

private:
	virtual void	Free();

	void			ReSetGravity() { m_vGravity = { 0,-9.8f,0 }; }

};

