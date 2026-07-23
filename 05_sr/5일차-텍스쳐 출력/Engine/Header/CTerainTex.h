#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"


BEGIN(Engine)

class ENGINE_DLL CTerainTex : public CVIBuffer
{
protected:
	explicit CTerainTex();
	explicit CTerainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerainTex(const CTerainTex& rhs);
	virtual ~CTerainTex();

public:
	virtual HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CTerainTex* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone();

private:
	virtual void	Free();
};

END