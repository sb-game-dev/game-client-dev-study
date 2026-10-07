#include "Renderer.h"
#include "GameObject.h"
CRenderer::CRenderer()
{
}

void CRenderer::Add_RenderGroup(RENDERID eRenderID, shared_ptr<CGameObject> pGameObject)
{
	if (eRenderID >= RENDERID::END || nullptr == pGameObject)
		return;

	m_RenderGroup[ETOUI(eRenderID)].push_back(pGameObject);
}

void CRenderer::Render_GameObject()
{
	Render_Priority();
	Render_NonAlpha();
	Render_Alpha();
	Render_NonAlpha_UI();
	Render_Alpha_UI();

	Clear_RenderGroup();
}

void CRenderer::Clear_RenderGroup()
{
	for (uint32_t i = 0; i < ETOUI(RENDERID::END); ++i)
		m_RenderGroup[i].clear();
}

void CRenderer::Render_Priority()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::PRIORITY)])
		pObj->Render();
}

void CRenderer::Render_NonAlpha()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::NONALPHA)])
		pObj->Render();
}

void CRenderer::Render_Alpha()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::ALPHA)])
		pObj->Render();
}

void CRenderer::Render_NonAlpha_UI()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::NONALPHA_UI)])
		pObj->Render();
}

void CRenderer::Render_Alpha_UI()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::ALPHA_UI)])
		pObj->Render();
}

unique_ptr<CRenderer> CRenderer::Create()
{
	return unique_ptr<CRenderer>(new CRenderer());
}
