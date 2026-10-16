#include "BackGround.h"

#include "GameInstance.h"

CBackGround::CBackGround(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject { pDevice, pContext }
{
}

HRESULT CBackGround::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    /* 백그라운드 원형객체에 필요한 정보를 다 채워둔다. */


    return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
    /* 백그라운드 사본객체를 생성할때 원형이 읽어놓은 정보를 사본객체에게 채워준다. */
    CBackGround::BACKGROUND_DESC        BackGroundDesc{};
    BackGroundDesc.iBackData = 10;
    BackGroundDesc.iData = 100;
    BackGroundDesc.fSpeedPerSec = 10.f;
    BackGroundDesc.fDegreeRotPerSec = 180.f;

    m_iBackData = BackGroundDesc.iBackData;

    if (FAILED(__super::Initialize(&BackGroundDesc)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    return S_OK;
}

void CBackGround::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CBackGround::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
}

void CBackGround::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);


    // dynamic_pointer_cast<CGameObject>(shared_from_this())

    /* shared_from_this()가 shared_ptr<CPrototype>을 리턴 */
    /* dynamic_pointer_cast<CGameObject>로 shared_ptr<CGameObject>로 형변환 */

    /* 백그라운드가 화면에 그려져야하는 상황이라면 렌더러추가해준다. */
    CGameInstance::Get().Add_RenderGroup(RENDERGROUP::UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CBackGround::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    return S_OK;
}

HRESULT CBackGround::Ready_Components()
{
  /*  m_pTextureCom = dynamic_pointer_cast<CTexture>(CGameInstance::Get().Clone_Prototype(ETOUI(LEVEL::LOGO), TEXT("Prototype_Component_Texture_BackGround")));
    if (nullptr == m_pTextureCom)
        return E_FAIL;

    if(nullptr == __super::Find_Component(TEXT("Com_Texture")))
        m_Components.emplace(TEXT("Com_Texture"), m_pTextureCom);*/

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOGO), TEXT("Prototype_Component_Texture_BackGround"),
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;



    return S_OK;
}

shared_ptr<CBackGround> CBackGround::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CBackGround>(new CBackGround(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CBackGround");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CBackGround::Clone(void* pArg)
{
    shared_ptr<CBackGround> pInstance = shared_ptr<CBackGround>(new CBackGround(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CBackGround");
        pInstance.reset();
    }

    return pInstance;
}