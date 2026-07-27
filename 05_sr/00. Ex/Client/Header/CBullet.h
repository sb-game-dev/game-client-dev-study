#pragma once
#include "CGameObject.h"
namespace Engine
{
    class CCubeTex;
    class CTransform;
    class CTexture;
}
class CBullet :
    public CGameObject
{
private:
    explicit CBullet(LPDIRECT3DDEVICE9 pGraphicDev,_vec3 vPos,_vec3 vDir);
    virtual ~CBullet();

public:
    virtual			HRESULT		Ready_GameObject();
    virtual			_int		Update_GameObject(const _float& fTimeDelta);
    virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
    virtual			void		Render_GameObject();

private:
    HRESULT         Add_Component();

public:
    static          CBullet*    Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, _vec3 vDir);
    virtual         void        Free();


private:
    Engine::CCubeTex*   m_pBufferCom;
    Engine::CTransform* m_pTransformCom;
    Engine::CTexture*   m_pTextureCom;

    _vec3               m_vDir;
    _vec3               m_vPos;
    float               m_fSpeed;
};

