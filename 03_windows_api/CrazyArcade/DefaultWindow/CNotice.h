#pragma once
#include "Define.h"
#include "CObj.h"
class CNotice
{
public:
	CNotice();
	CNotice(const CNotice* rhs) = delete;
	CNotice& operator=(const CNotice* rhs) = delete;
	~CNotice();

public:
	void	Initialize();
	int		Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

public:
	bool			GetDraw() { return m_bDraw; }

	void			SetDraw(bool bDraw) { m_bDraw = bDraw; }


public:
	static CNotice* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CNotice;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CNotice* m_pInstance;

	bool			m_bDraw;
	CObj*			m_pExitNoticeButton;
	CObj*			m_pReLoginButton;
	CObj*			m_pExitGameButton;

	int				m_iExitNoticeButtonFrame;
	int				m_iReLoginButtonFrame;
	int				m_iExitGameButtonFrame;

	bool			m_bButtonPreState;
	bool			m_bButtonCurState;
};

