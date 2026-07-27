#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CPyramidCol : public CVIBuffer
{
protected:
	explicit CPyramidCol();
	explicit CPyramidCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPyramidCol(const CPyramidCol& rhs);
	virtual ~CPyramidCol();

public:
	virtual HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CPyramidCol* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone();

private:
	virtual void	Free();
};

END