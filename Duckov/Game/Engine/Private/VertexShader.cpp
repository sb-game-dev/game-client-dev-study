#include "VertexShader.h"

CVertexShader::CVertexShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CShader{pDevice,pContext}
{
}

HRESULT CVertexShader::Initialize_Prototype(const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements, const char_t* pEntryPoint, const char_t* pTarget)
{
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
        pEntryPoint,                         // 진입점 함수 이름
        pTarget,                            // 타깃: 버텍스 셰이더, 셰이더 모델 5.0
        iFlags,                            // 컴파일 옵션
        0,                                 // 이 책에서는 사용하지 않는 고급 효과 컴파일 옵션(항상 NULL 또는 0)
        &m_pShaderByteCode,                          // 결과: 컴파일된 바이트코드
        nullptr)))                       // 실패 시 에러 메시지
    {
        return E_FAIL;
    }
    // 버텍스 셰이더 객체 생성
    if (FAILED(m_pDevice->CreateVertexShader(m_pShaderByteCode->GetBufferPointer(), m_pShaderByteCode->GetBufferSize(), nullptr, &m_pVS)))
        return E_FAIL;

    // Input Layout 생성 (VS 바이트코드와 대조)
    if (FAILED(m_pDevice->CreateInputLayout(pElements,                      // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
                                            iNumElements,                   // 배열 원소의 개수
                                            m_pShaderByteCode->GetBufferPointer(),    // 정점셰이더를 컴파일해서 얻은 바이트코드를 가리키는 포인터
                                            m_pShaderByteCode->GetBufferSize(),       // 바이트코드의 크기
                                            &m_pInputLayout)))              // 생성된 입력 배치를 돌려줄 포인터
        return E_FAIL;
	return S_OK;
}

HRESULT CVertexShader::Initialize(void* pArg)
{
	return S_OK;
}

shared_ptr<CVertexShader> CVertexShader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements, const char_t* pEntryPoint, const char_t* pTarget)
{
    auto pInstance = shared_ptr<CVertexShader>(new CVertexShader(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath, pElements, iNumElements, pEntryPoint, pTarget)))
    {
        MSG_BOX("Failed to Created : CVertexShader");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVertexShader::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CVertexShader>(new CVertexShader(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVertexShader");
        pInstance.reset();
    }

    return pInstance;
}