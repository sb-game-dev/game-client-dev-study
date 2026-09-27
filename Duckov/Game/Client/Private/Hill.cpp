#include "Hill.h"

CHill::CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CHill::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    uint32_t    ivtxCntX = 129;
    uint32_t    ivtxCntZ = 129;

    uint32_t    ivtxCnt = ivtxCntX * ivtxCntZ;
    uint32_t    iFaceCnt = (ivtxCntX - 1) * (ivtxCntZ - 1) * 2;
    f32_t       fHalfWidth = 0.5f * (ivtxCntX -1);
    f32_t       fHalfDepth = 0.5f * (ivtxCntZ -1);

    f32_t   dx = 1.f;//128.f / (ivtxCntZ);
    f32_t   dz = 1.f;//128.f / (ivtxCntX);

    f32_t   du = 1.f / (ivtxCntX);
    f32_t   dv = 1.f / (ivtxCntZ);

    
    m_tMeshData.Vertices.resize(ivtxCnt);
    m_tMeshData.Indices.resize(iFaceCnt * 3);

    for (uint32_t i = 0; i < ivtxCntZ; ++i)
    {
        float z = fHalfDepth - i * dz;
        for (uint32_t j = 0; j < ivtxCntX; ++j)
        {
            float x = -fHalfWidth + j * dx;
            m_tMeshData.Vertices[i * ivtxCntX + j].vPosition = float3_t(x, 0.f, z);
            
            m_tMeshData.Vertices[i * ivtxCntX + j].vNormal = float3_t(0.f, 1.f, 0.f);
            m_tMeshData.Vertices[i * ivtxCntX + j].vTangentU = float3_t(1.f, 0.f, 0.f);

            m_tMeshData.Vertices[i * ivtxCntX + j].TexC.x = j*du;
            m_tMeshData.Vertices[i * ivtxCntX + j].TexC.y = i*dv;
        }
    }

    uint32_t k = 0;
    for (uint32_t i = 0; i < ivtxCntZ - 1; ++i)
    {
        for (uint32_t j = 0; j < ivtxCntX - 1; ++j)
        {
            m_tMeshData.Indices[k] = i * ivtxCntX + j;
            m_tMeshData.Indices[k + 1] = i * ivtxCntX + j + 1;
            m_tMeshData.Indices[k + 2] = (i + 1) * ivtxCntX + j;
            m_tMeshData.Indices[k + 3] = (i + 1) * ivtxCntX + j;
            m_tMeshData.Indices[k + 4] = i * ivtxCntX + j + 1;
            m_tMeshData.Indices[k + 5] = (i + 1) * ivtxCntX + j + 1;

            k += 6;
        }
    }
    m_iIndexCnt = m_tMeshData.Indices.size();
    vector<VTXCOL> vertices(m_tMeshData.Vertices.size());
    for (size_t i = 0; i < m_tMeshData.Vertices.size(); ++i)
    {
        float3_t& p = m_tMeshData.Vertices[i].vPosition;
        p.y = GetHeight(p.x, p.z);
        vertices[i].vPosition = p;
        if (p.y < -10.0f)
            vertices[i].vColor = XMFLOAT4(1.0f, 0.96f, 0.62f, 1.0f);
        else if (p.y < 5.0f)
            vertices[i].vColor = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
        else if (p.y < 12.0f)
            vertices[i].vColor = XMFLOAT4(0.1f, 0.48f, 0.19f, 1.0f);
        else if (p.y < 20.0f)
            vertices[i].vColor = XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
        else
            vertices[i].vColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    }


    // ���� ���� ����
    D3D11_BUFFER_DESC   VBDesc{};
    VBDesc.ByteWidth = sizeof(VTXCOL) * m_tMeshData.Vertices.size();
    VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  VBData{};
    VBData.pSysMem = &vertices[0];  
    if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
        return E_FAIL;

    
    D3D11_BUFFER_DESC IBDesc{};
    IBDesc.ByteWidth = sizeof(UINT) * m_iIndexCnt;
    IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;


    D3D11_SUBRESOURCE_DATA IBData{};
    IBData.pSysMem = &m_tMeshData.Indices[0];
    if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
        return E_FAIL;

    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_TRANSFORM);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, &m_pCB)))
        return E_FAIL;


    ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    
#endif
    
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxCol.hlsl",  
        nullptr,                          
        nullptr,                          
        "VS_MAIN",                        
        "vs_5_0",                         
        iFlags,                           
        0,                                
        &pVSBlob,                         
        &pErrBlob)))                      
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }
    // PS ������
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_VtxCol.hlsl", nullptr, nullptr,
        "PS_MAIN", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }

    // ���ؽ� ���̴� ��ü ����
    if (FAILED(m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS)))
        return E_FAIL;

    // �ȼ� ���̴� ��ü ����
    if (FAILED(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS)))
        return E_FAIL;

    // Input Layout ���� (VS ����Ʈ�ڵ�� ����)
    if (FAILED(m_pDevice->CreateInputLayout(VTXCOL::Elements,               // ���� ����ü�� �����ϴ� D3D11_INPUT_LEELMENT_DESC���� �迭
        VTXCOL::iNumElements,           // �迭 ������ ����
        pVSBlob->GetBufferPointer(),    // �������̴��� �������ؼ� ���� ����Ʈ�ڵ带 ����Ű�� ������
        pVSBlob->GetBufferSize(),       // ����Ʈ�ڵ��� ũ��
        &m_pInputLayout)))              // ������ �Է� ��ġ�� ������ ������
        return E_FAIL;

    // �����Ͷ����� ����
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // �ð������ ����
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());
    return S_OK;
}

void CHill::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CHill::LateUpdate(f32_t fDeltaTime)
{
    __super::LateUpdate(fDeltaTime);
}

HRESULT CHill::Render()
{
    XMMATRIX matWorld = GetWorld();

    // VS�� ������ ����ü ä���
    // HLSL�� �⺻������ �� ������ �����͸� �б� ������ ��ġ�� �ؾ� ��
    CB_TRANSFORM cbData;
    XMStoreFloat4x4(&cbData.WorldMatrix, XMMatrixTranspose(matWorld));

    // ��ȯ ����� ������ �������ִ� m_pCB ���۷� ����(USAGE_DEFAULT�� �����ؼ� ����̹��� ���� ����)
    // �Ʒ����� VS�� b0 �������Ϳ� ���� ����
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

// ���������ο� �ȱ�
    //IA(�Է� ������ �ܰ�)
    // ���� �ϳ��� ũ��� ������ ���� ��ġ ����
    uint32_t iStride = sizeof(VTXCOL);
    uint32_t iOffset = 0;
    // ���ؽ� ���� �ȱ�
    m_pContext->IASetVertexBuffers(0,                       // ���� ���۵��� ���̱� ������ �ε���
                                   1,                       // �Է� ���Կ� ���̰��� �ϴ� ������ ����
                                   m_pVB.GetAddressOf(),    // ���۸� ���� �迭�� ù ���Ҹ� ����Ű�� ������
                                   &iStride,                // ������ �� ������ ����Ʈũ�� ����(�ּҸ� �Ѱ������)
                                   &iOffset);               // ���� ������ ������ġ�������� �ǳʶ� �ε���

    // �ε��� ���� �ȱ�
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);

    // �ﰢ�� �׸��� ����
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // InputLayoyt �ȱ�(FVF�� ����)
    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    // VS(���ؽ� ���̴� �ܰ�) -> ���庯ȯ, �佺���̽� ��ȯ, ���� ��ȯ ����� ���޹޾Ƽ� ���ؽ� ���ۿ� �����
    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

    // VS�� ������۽���(b0)�� �������(��ȯ ��� ����) �ȱ�
    m_pContext->VSSetConstantBuffers(0, //register(b0)�� �����
        1,
        m_pCB.GetAddressOf());

    // PS(�ȼ� ���̴�) -> ������ �� �ۿ� ����
    m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0);

    // RS(�����Ͷ����� ����)
    m_pContext->RSSetState(m_pRS.Get());

    // �׸���
    m_pContext->DrawIndexed(m_iIndexCnt, // IndexCnt: �ε��� ������ ũ��
        0,                      // StartIndexLocation : ����� �ε����� ��ġ
        0);                     // BaseVertexLocation : �������� �������� ���� �� ȣ�⿡�� ����� �ε����� �������� ������

    return S_OK;
}

shared_ptr<CHill> CHill::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CHill>(new CHill(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}