#pragma once
#include "Client_Defines.h"

// C++20에서 u8"" 리터럴은 char8_t라서 ImGui(const char*)에 바로 못 넘김
//u8"한글"은 "UTF-8 바이트로 넣어라" 라는 뜻
#define U8(str) reinterpret_cast<const char*>(u8##str)

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