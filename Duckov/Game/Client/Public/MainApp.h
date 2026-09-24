#pragma once

#include "Client_Defines.h"

NS_BEGIN(Client)

class CMainApp final// 자식 클래스
{
private:
	CMainApp();
public:
	~CMainApp();// 스마트 포인터를 사용하기 때문에 default로 설정. = default -> {}한 것과 같음. 가독성이 높음

public:
	HRESULT		Initialize();
	void		Update(f32_t fDeltaTime);
	HRESULT		Render();

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };


	//ComPtr<ID3D11Buffer>       m_pVB;           // 정점 버퍼
	//ComPtr<ID3D11Buffer>       m_pIB;           // 인덱스 버퍼
	//ComPtr<ID3D11InputLayout>  m_pInputLayout;  // 정점 메모리 해석표
	//ComPtr<ID3D11VertexShader> m_pVS;
	//ComPtr<ID3D11PixelShader>  m_pPS;


public:
	static		unique_ptr<CMainApp>		Create();
};

NS_END
