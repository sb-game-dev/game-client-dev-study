#pragma once
#include "Engine_Defines.h"
#include "GameObject.h"

NS_BEGIN(Engine)

class ENGINE_DLL CMouse : public CGameObject
{
public:
	typedef struct tagMouseDesc : public CGameObject::GAMEOBJECT_DESC
	{

	}MOUSE_DESC;
	enum class MOUSESTATE { CURSOR, DOT, BAR, ARROW, END };

protected:
	CMouse(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CMouse() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta);
	virtual		void		Update(f32_t fTimeDelta);
	virtual		void		Late_Update(f32_t fTimeDelta);
	virtual		HRESULT		Render() override;

	MOUSESTATE				GetMouseState() { return m_eMouseState; }
	void					SetMouseState(MOUSESTATE eMouseState) { m_eMouseState = eMouseState; }

protected:
	MOUSESTATE				m_eMouseState = {};

protected:
	HRESULT Ready_Components();

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) PURE;
};

NS_END