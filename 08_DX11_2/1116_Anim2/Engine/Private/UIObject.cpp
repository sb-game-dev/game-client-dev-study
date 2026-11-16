#include "UIObject.h"

#include "GameInstance.h"

CUIObject::CUIObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject { pDevice, pContext }
{
}

HRESULT CUIObject::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CUIObject::Initialize(void* pArg)
{
    auto        pDesc = static_cast<UIOBJECT_DESC*>(pArg);

    m_fX = pDesc->fX;
    m_fY = pDesc->fY;
    m_fSizeX = pDesc->fSizeX;
    m_fSizeY = pDesc->fSizeY;

    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    uint32_t        iNumViewports = { 1 };
    D3D11_VIEWPORT  ViewportDesc{};

    m_pContext->RSGetViewports(&iNumViewports, &ViewportDesc);

    m_iWinSizeX = ViewportDesc.Width;
    m_iWinSizeY = ViewportDesc.Height;

    Update_State();

    return S_OK;
}

void CUIObject::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CUIObject::Update(f32_t fTimeDelta)
{
    Update_State();

    __super::Update(fTimeDelta);
}

void CUIObject::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
}

HRESULT CUIObject::Render()
{
    return S_OK;
}

void CUIObject::Update_State()
{    
    m_pTransformCom->Set_Scale(m_fSizeX, m_fSizeY, 1.f);
    m_pTransformCom->Set_State(STATE::POSITION, 
        XMVectorSet(m_fX - m_iWinSizeX * 0.5f, -m_fY + m_iWinSizeY * 0.5f, 0.f, 1.f));
}

