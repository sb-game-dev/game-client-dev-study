#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

NS_BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Rect;
NS_END


NS_BEGIN(Client)

class CTerrain final : public CGameObject
{
public:
	typedef struct tagTerrainDesc : public CGameObject::GAMEOBJECT_DESC
	{
		
	}TERRAIN_DESC;
private:
	CTerrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CTerrain() = default;

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
	shared_ptr<CVIBuffer_Terrain>	m_pVIBufferCom = { nullptr };

private:
	HRESULT Ready_Components();
	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources();



public:
	static shared_ptr<CTerrain> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END