#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CRcTex : public CVIBuffer
{
protected:
	explicit CRcTex();
	explicit CRcTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRcTex(const CRcTex& rhs);
	virtual ~CRcTex();

public:
	virtual HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CRcTex* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(CGameObject* pOwner) override;

private:
	virtual void	Free();

	// CVIBuffer을(를) 통해 상속됨
};

END