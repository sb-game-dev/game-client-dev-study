#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
class CImGui_Manager final
{
private:
    CImGui_Manager() = default;
public:
    ~CImGui_Manager();

public:
    HRESULT     Initialize(HWND hWnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    void        Begin_Frame();      // 매 프레임 Update 맨 앞
    void        Render();           // 매 프레임 씬 Draw 뒤, Present 전

private:
    bool_t      m_bInitialized = { false };

public:
    static unique_ptr<CImGui_Manager> Create(HWND hWnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END