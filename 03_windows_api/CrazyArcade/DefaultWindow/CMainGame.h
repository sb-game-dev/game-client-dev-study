#pragma once

#include "Define.h"
#include "CPlayer.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render();	// 매 프레임마다 출력하는 코드를 모아놓는 함수
	void		Release();
	void		InsertImg();
private:
	HDC			m_hDC;

	HDC			m_memDC; 
	HBITMAP		m_Bit;
	HBITMAP		m_Old;

	Graphics* m_pGraphics;


	ULONGLONG		m_dwTime;
	int				m_iFPS;
	TCHAR			m_szFPS[32];
};

