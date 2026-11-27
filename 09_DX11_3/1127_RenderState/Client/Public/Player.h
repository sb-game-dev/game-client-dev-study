#pragma once

#include "Client_Defines.h"
#include "ContainerObject.h"

NS_BEGIN(Client)

class CPlayer final : public CContainerObject
{
public:
	typedef struct tagPlayerDesc : public Engine::CContainerObject::CONTAINEROBJECT_DESC
	{

	}PLAYER_DESC;

	enum STATE {
		IDLE		= 0x00000001, 
		RUN			= 0x00000002,
		ATT			= 0x00000004,
	};

private:
	CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CPlayer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fTimeDelta)override ;
	virtual void Update(f32_t fTimeDelta) override;
	virtual void Late_Update(f32_t fTimeDelta) override;
	virtual HRESULT Render() override;


private:
	uint32_t		m_iState = { };

private:
	HRESULT Ready_Components();
	HRESULT Ready_PartObjects();

public:
	static shared_ptr<CPlayer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END