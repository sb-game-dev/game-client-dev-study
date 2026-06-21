#pragma once
#include "Define.h"
class CScene
{
public:
	CScene();
	virtual~CScene();

public:
	virtual void Initialize()					PURE;
	virtual int	 Update()						PURE;
	virtual void LateUpdate()					PURE;
	virtual void Render(HDC hDC)				PURE;
	virtual void Release()						PURE;

protected:
	float			m_fAlpha;
	float			m_fDeltaAlpha;
	bool			m_bStartScene;
	bool			m_bEndScene;

	SCENESTATE		m_ePreSceneState;
	SCENESTATE		m_eCurSceneState;

	ULONGLONG		m_dwFrameTime;
};

