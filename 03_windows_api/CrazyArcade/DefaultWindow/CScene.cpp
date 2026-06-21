#include "pch.h"
#include "CScene.h"
CScene::CScene():m_fAlpha(0.99f), m_fDeltaAlpha (1.f), m_bStartScene(true),m_bEndScene(false),
m_ePreSceneState(SCENE_END), m_eCurSceneState(SCENE_START), m_dwFrameTime(GetTickCount64())
{
}

CScene::~CScene()
{
}