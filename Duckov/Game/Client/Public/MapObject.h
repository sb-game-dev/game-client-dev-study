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
        float4_t  vQuaternion = { 0.f, 0.f, 0.f, 1.f };     // 단위 쿼터니언 (회전 없음)
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
    const float3_t& Get_Scale()    const { return m_vScale; }
    void Set_Position(const float3_t& v) { m_vPosition = v; Apply_Transform(); }
    void Set_Scale(const float3_t& v) { m_vScale = v;    Apply_Transform(); }

    const float4_t& Get_Quaternion() const { return m_vQuaternion; }
    const float3_t& Get_EulerHint()  const { return m_vEulerHint; }

    void Set_RotationEuler(const float3_t& vDeg);
    void Set_Transform(const float3_t& vPos, const float4_t& vQuat, const float3_t& vScale); 

    virtual void Save_Extra(ofstream& Out) const {}
    virtual void Load_Extra(ifstream& In, MAPOBJECT_DESC& Desc) {}

    const wstring_t& Get_MeshPath() const { return m_strMeshPath; }
    const wstring_t& Get_TexturePath() const { return m_strTexturePath; }

protected:
    void Apply_Transform();

protected:
    uint32_t  m_iLevelIndex = {};
    float3_t  m_vPosition = {};
    float3_t  m_vScale = { 1.f, 1.f, 1.f };
    wstring_t m_strMeshPath;
    wstring_t m_strTexturePath;
    float4_t  m_vQuaternion = { 0.f, 0.f, 0.f, 1.f };   // 원본 값: Transform, 저장 모두 이 값 기준
    float3_t  m_vEulerHint = {};                        // 표시용: Inspector에 보여 줄 각도(degree)

    bool_t    m_bEditorMode = { false };
};
NS_END