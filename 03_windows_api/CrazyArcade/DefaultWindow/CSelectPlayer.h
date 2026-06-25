#pragma once
#include "Define.h"
#include "CObj.h"
class CSelectPlayer
{
public:
	CSelectPlayer();
	CSelectPlayer(const CSelectPlayer* rhs) = delete;
	CSelectPlayer& operator=(const CSelectPlayer* rhs) = delete;
	~CSelectPlayer();

public:
	void	Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();


public:
	void		SetDraw(bool bDraw) { m_bDraw = bDraw; }
	void		SetNextStage(STAGESTATE eStage) { m_eStageState = eStage; }
	
	bool		GetDraw() { return m_bDraw; }
	PLAYERID	GetSelectPlayerID() { return m_eSelectPlayerID; }
	STAGESTATE	GetNextStage() { return m_eStageState; }

public:
	static CSelectPlayer* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CSelectPlayer;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CSelectPlayer* m_pInstance;

	bool	m_bDraw;
	CObj*	m_pButtonSelectPlayer1;
	CObj*	m_pButtonSelectPlayer2;
	CObj*	m_pExitSelectPlayer;

	int				m_iButtonSelectPlayer1Frame;
	int				m_iButtonSelectPlayer2Frame;
	int				m_iExitSelectPlayerFrame;

	bool			m_bButtonPreState;
	bool			m_bButtonCurState;

	PLAYERID		m_eSelectPlayerID;
	STAGESTATE		m_eStageState;
};

