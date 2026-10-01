#include "Level_Logo.h"

CLevel_Logo::CLevel_Logo(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_Logo::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    /* 로고레벨에서 사용하기 위한 사본 객체들을 생성해준다. */
    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    return S_OK;
}

void CLevel_Logo::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

HRESULT CLevel_Logo::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    /* 원형 객체를 찾고 -> 복제하고 -> 오브젝트 메니져에 다시 분류해서 보관한다. */
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOI(LEVEL::LOGO), TEXT("Prototype_GameObject_BackGround"),
        ETOUI(LEVEL::LOGO), pLayerTag, TEXT("GameObject_BackGround"))))
        return E_FAIL;
    return S_OK;
}


shared_ptr<CLevel_Logo> CLevel_Logo::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    return shared_ptr<CLevel_Logo>(new CLevel_Logo(pDevice,pContext));
}