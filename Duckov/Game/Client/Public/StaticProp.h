#pragma once
#include "Client_Defines.h"
#include "MapObject.h"
NS_BEGIN(Client)
class CStaticProp : public CMapObject
{
public:
    typedef struct tagStaticPropDesc : public MAPOBJECT_DESC
    {

    }STATICPROP_DESC;
private:
    CStaticProp(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    ~CStaticProp() = default;
public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual	void	Priority_Update(f32_t fDeltaTime) override;
    virtual	void	Update(f32_t fDeltaTime) override;
    virtual	void	Late_Update(f32_t fDeltaTime) override;
    virtual HRESULT	Render() override;

    HRESULT Change_Texture(const wstring_t& strTexturePath);
    HRESULT Change_Mesh(const wstring_t& strMeshPath);

private:
    shared_ptr<CTexture>            m_pTextureCom;
    shared_ptr<CModel>              m_pModelCom;
    shared_ptr<CVertexShader>       m_pVS;
    shared_ptr<CPixelShader>        m_pPS;
    shared_ptr<CConstantBuffer>     m_pCB;
    CB_PER_OBJECT_LIT               m_tCBData = {};

private:
    HRESULT Ready_Components();
    HRESULT Ready_ConstantBuffer();
    HRESULT Ready_Mesh();
    
    HRESULT Update_ConstantBuffer(const matrix_t& matWorld);

    HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS);
    HRESULT Bind_ShaderResources(const matrix_t& matWorld);

    HRESULT Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS);

public:
    static shared_ptr<CStaticProp> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};
NS_END