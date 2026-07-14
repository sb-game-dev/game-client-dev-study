#pragma once
class CMainApp
{
private:
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp();
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp(const float& fTimeDelta);
	void		Render_MainApp();

protected:

public:
	static	CMainApp* Create();

private:
	virtual	void	Free();
};

