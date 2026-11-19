#pragma once
#include "Engine_Defines.h"
#include "GameObject.h"
NS_BEGIN(Engine)
class CPartObject :public CGameObject
{
public:
	typedef struct tagPartObjectDesc : public CGameObject::GAMEOBJECT_DESC
	{

	}PARTOBJECT_DESC;

protected:
	CPartObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CPartObject() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual void		Priority_Update(f32_t fDeltaTime)override;
	virtual void		Update(f32_t fDeltaTime)override;
	virtual void		Late_Update(f32_t fDeltaTime)override;
	virtual HRESULT		Render()override;

public:
	static shared_ptr<CPartObject> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END