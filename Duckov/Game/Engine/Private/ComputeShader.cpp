#include "ComputeShader.h"

CComputeShader::CComputeShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CShader{ pDevice,pContext }
{
}

HRESULT CComputeShader::Initialize_Prototype(const tchar_t* pShaderFilePath, const char_t* pMainName)
{
    ComPtr<ID3DBlob> pCSBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    // 셰이더를 디버그 모드에서 컴파일한다. | 컴파일시 최적화를 사용하지 않는다(디버깅에 유용함)
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        pShaderFilePath,                   // 파일 경로 (작업 디렉터리 기준)
        nullptr,                           // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // 헤더파일 인클루드  
        pMainName,                         // 진입점 함수 이름
        "cs_5_0",                          // 타깃: 버텍스 셰이더, 셰이더 모델 5.0
        iFlags,                            // 컴파일 옵션
        0,                                 // 이 책에서는 사용하지 않는 고급 효과 컴파일 옵션(항상 NULL 또는 0)
        &pCSBlob,                          // 결과: 컴파일된 바이트코드
        &pErrBlob)))                       // 실패 시 에러 메시지
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }
    // 픽셀 셰이더 객체 생성
    if (FAILED(m_pDevice->CreateComputeShader(pCSBlob->GetBufferPointer(), pCSBlob->GetBufferSize(), nullptr, &m_pCS)))
        return E_FAIL;
}

HRESULT CComputeShader::Initialize(void* pArg)
{
    return S_OK;
}

shared_ptr<CComputeShader> CComputeShader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath, const char_t* pMainName)
{
    auto pInstance = shared_ptr<CComputeShader>(new CComputeShader(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath, pMainName)))
    {
        MSG_BOX("Failed to Created : CComputeShader");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CComputeShader::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CComputeShader>(new CComputeShader(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CComputeShader");
        pInstance.reset();
    }

    return pInstance;
}