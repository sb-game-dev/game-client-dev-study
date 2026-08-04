#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL CCylinderTex : public CVIBuffer
{
protected:
	explicit CCylinderTex();
	explicit CCylinderTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCylinderTex(const CCylinderTex& rhs);
	virtual ~CCylinderTex();

public:
	virtual HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CCylinderTex* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(CGameObject* pOwner) override;

private:
	virtual void	Free();

	// CVIBuffer을(를) 통해 상속됨
};

END