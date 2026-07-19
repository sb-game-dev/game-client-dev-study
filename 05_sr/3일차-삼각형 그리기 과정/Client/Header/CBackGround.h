#pragma once

#include "CGameObject.h"

namespace Engine
{
	class CTriCol;
	class CRectCol;
	class CPillarCol;
}

class CBackGround :  public CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBackGround();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			_int		Update_GameObject(const _float& fTimeDelta);
	virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void		Render_GameObject();

private:
	HRESULT			Add_Component();
	void			KetInput(const _float& fTimeDelta);

private:
	Engine::CTriCol*		m_pBufferCom;
	Engine::CRectCol*		m_pRectBufferCom;
	Engine::CPillarCol*		m_pPillarBufferCom;

	D3DXVECTOR3				m_vScale;
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vRot;
	D3DXVECTOR3				m_vDir;
	D3DXVECTOR3				m_vLook;


public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void	Free();

};

