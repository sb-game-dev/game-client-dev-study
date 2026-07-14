#pragma once

class CMainApp
{
private:		// 생성자, 소멸자
	explicit CMainApp();
	~CMainApp();

public:
	HRESULT		Ready_MainApp();
	int			Update_MaintApp(const float& fTimeDelta);
	void		LateUpdate_MainApp(const float& fTimeDelta);
	void		Render_MainApp();

protected:

private:

public:		// 생성 함수
	static CMainApp* Create();

private:	// 소멸 함수
	virtual void	Free();
};

