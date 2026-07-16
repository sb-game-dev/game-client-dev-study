#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CRectCol :  public CVIBuffer
{
protected:
	explicit CRectCol();
	explicit CRectCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRectCol(const CRectCol& rhs);
	virtual~CRectCol();

public:
	virtual	HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CRectCol* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone();

private:
	virtual void	Free();
};

END