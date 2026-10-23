#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

NS_BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Rect;
NS_END


NS_BEGIN(Client)

class CBackGround final : public CGameObject
{
public:
	typedef struct tagBackGroundDesc : public CGameObject::GAMEOBJECT_DESC
	{
		uint32_t		iBackData{};
	}BACKGROUND_DESC;
private:
	CBackGround(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CBackGround() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fTimeDelta) override;
	virtual void Update(f32_t fTimeDelta) override;
	virtual void Late_Update(f32_t fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	uint32_t						m_iBackData = {};


	shared_ptr<CTexture>			m_pTextureCom = { nullptr };
	shared_ptr<CShader>				m_pVSCom = { nullptr };
	shared_ptr<CShader>				m_pPSCom = { nullptr };
	shared_ptr<CVIBuffer_Rect>		m_pVIBufferCom = { nullptr };

private:
	HRESULT Ready_Components();



public:
	static shared_ptr<CBackGround> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END