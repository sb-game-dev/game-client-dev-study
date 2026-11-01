// MapObject.h
#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include <fstream>

NS_BEGIN(Client)
class CMapObject abstract : public CGameObject
{
public:
    typedef struct tagMapObjectDesc : public GAMEOBJECT_DESC
    {
        uint32_t  iLevelIndex = {};
        float3_t  vPosition = {};
        float3_t  vRotation = {};                 // degree
        float3_t  vScale = { 1.f, 1.f, 1.f };
        wstring_t strMeshPath;
        wstring_t strTexturePath;
        bool_t    bEditorMode = { false };
    }MAPOBJECT_DESC;

protected:
    CMapObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CMapObject() = default;

public:
    virtual HRESULT Initialize(void* pArg) override;

    const float3_t& Get_Position() const { return m_vPosition; }
    const float3_t& Get_Rotation() const { return m_vRotation; }
    const float3_t& Get_Scale()    const { return m_vScale; }
    void Set_Position(const float3_t& v) { m_vPosition = v; Apply_Transform(); }
    void Set_Rotation(const float3_t& v) { m_vRotation = v; Apply_Transform(); }
    void Set_Scale(const float3_t& v) { m_vScale = v;    Apply_Transform(); }

    virtual void Save_Extra(ofstream& Out) const {}
    virtual void Load_Extra(ifstream& In, MAPOBJECT_DESC& Desc) {}

protected:
    void Apply_Transform();

protected:
    uint32_t  m_iLevelIndex = {};
    float3_t  m_vPosition = {};
    float3_t  m_vRotation = {};
    float3_t  m_vScale = { 1.f, 1.f, 1.f };
    wstring_t m_strMeshPath;
    wstring_t m_strTexturePath;
    bool_t    m_bEditorMode = { false };
};
NS_END