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

private:
	void		Restart();
private:
	HDC			m_hDC;
	DWORD		m_dwTime1;
	DWORD		m_dwTime2;
	DWORD		m_dwTime3;
	DWORD		m_dwTime4;
	DWORD		m_dwTime5;
	DWORD		m_dwTime6;
	DWORD		m_dwTime7;
};

