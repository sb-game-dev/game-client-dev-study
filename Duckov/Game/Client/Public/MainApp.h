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
	void		LateUpdate(f32_t fDeltaTime);
	HRESULT		Render();

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };	

public:
	static		unique_ptr<CMainApp>		Create();
};

NS_END
