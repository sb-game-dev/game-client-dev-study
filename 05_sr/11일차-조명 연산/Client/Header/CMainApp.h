#pragma once

#include "CBase.h"
#include "CGraphicDev.h"
#include "CTimerMgr.h"
#include "CFrameMgr.h"

#include "CManagement.h"

class CMainApp : public CBase
{
private:		// 생성자, 소멸자
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp();
	int			Update_MaintApp(const float& fTimeDelta);
	void		LateUpdate_MainApp(const float& fTimeDelta);
	void		Render_MainApp();

protected:

private:
	HRESULT		Ready_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	HRESULT		Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev);


private:
	Engine::CGraphicDev*	m_pDeviceClass;
	Engine::CManagement* m_pManagementClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;


public:		// 생성 함수
	static CMainApp* Create();

private:	// 소멸 함수
	virtual void	Free();
};

// 뷰스페이스 행렬 변환 함수와 원근 투영행렬 변환 함수를 직접 만들어라

// 개인당 SR시연회때 했으면 하는 게임 4가지를 골라서 메모장에 작성
// - 왜 그 게임을 시연회때 했으면 하는지 사유(공부 관점에서)
// - 게임 링크 첨부