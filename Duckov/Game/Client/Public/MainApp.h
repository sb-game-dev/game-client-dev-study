#pragma once

#include "Client_Defines.h"

NS_BEGIN(Client)

class CMainApp final// 자식 클래스
{
private:
	CMainApp();
public:
	~CMainApp() = default; // 스마트 포인터를 사용하기 때문에 default로 설정. = default -> {}한 것과 같음. 가독성이 높음

public:
	HRESULT		Initialize();
	void		Update();
	HRESULT		Render();

public:
	static		unique_ptr<CMainApp>		Create();
};

NS_END
