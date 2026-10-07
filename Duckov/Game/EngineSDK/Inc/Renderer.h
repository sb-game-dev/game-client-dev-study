#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CGameObject;
class CRenderer
{
private:
	CRenderer();
public:
	~CRenderer() = default;

public:
	void	Add_RenderGroup(RENDERID eRenderID, shared_ptr<CGameObject> pGameObject);
	void	Render_GameObject();

private:
	void	Render_Priority();
	void	Render_NonAlpha();
	void	Render_Alpha();
	void	Render_NonAlpha_UI();
	void	Render_Alpha_UI();

	void	Clear_RenderGroup();

private:
	list<shared_ptr<CGameObject>> m_RenderGroup[ETOUI(RENDERID::END)];

public:
	static unique_ptr<CRenderer> Create();
};

NS_END