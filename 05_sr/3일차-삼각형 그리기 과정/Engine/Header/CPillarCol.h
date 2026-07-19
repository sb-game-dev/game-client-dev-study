#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CPillarCol : public CVIBuffer
{
protected:
	explicit CPillarCol();
	explicit CPillarCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPillarCol(const CPillarCol& rhs);
	virtual~CPillarCol();

public:
	virtual	HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CPillarCol* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone();

private:
	virtual void	Free();
};

END