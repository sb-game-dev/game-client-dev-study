#pragma once
#include "CVIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRectPillarCol : public CVIBuffer
{
protected:
    explicit CRectPillarCol();
    explicit CRectPillarCol(LPDIRECT3DDEVICE9 pGraphicDev);
    explicit CRectPillarCol(const CRectPillarCol& rhs);
    virtual ~CRectPillarCol();

public:
	virtual	HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CRectPillarCol* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone();

private:
	virtual void	Free();
};

END
