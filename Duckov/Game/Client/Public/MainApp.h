#pragma once

#include "Client_Defines.h"

NS_BEGIN(Client)

class CMainApp final// 자식 클래스
{
private:
	CMainApp();
public:
	~CMainApp();// 스마트 포인터를 사용하기 때문에 default로 설정. = default -> {}한 것과 같음. 가독성이 높음 
				// 이었으나 GameInstance의 멤버를 지워야 하기 때문에 소멸자 몸체 완성해줌

public:
	HRESULT		Initialize();
	void		Update(f32_t fDeltaTime);
	HRESULT		Render();

	HRESULT		Ready_Cube();
	void		Render_Cube();
	void		KeyInput(f32_t fDeltaTime);

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };


	ComPtr<ID3D11Buffer>       m_pVB;           // 버텍스 버퍼
	ComPtr<ID3D11Buffer>       m_pIB;           // 인덱스 버퍼
	ComPtr<ID3D11InputLayout>  m_pInputLayout;  // 정점 메모리 해석표
	ComPtr<ID3D11VertexShader> m_pVS;
	ComPtr<ID3D11PixelShader>  m_pPS;

	// 변환 행렬들을 VS로 전달하는 배달 상자의 개념
	ComPtr<ID3D11Buffer>	   m_pCB;

	f32_t               m_fRotX = 0.f;
	f32_t               m_fRotY = 0.f;
	f32_t               m_fRotZ = 0.f;
	float3_t			m_vPosition = { 0.f,0.f,0.f };
	

public:
	static		unique_ptr<CMainApp>		Create();
};

NS_END
