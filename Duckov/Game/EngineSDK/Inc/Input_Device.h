#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CInput_Device 
{
private:
	CInput_Device(void);
public:
	~CInput_Device(void);

public:
	int8_t	Get_DIKeyState(uint8_t byKeyID)
	{
		return m_byKeyState[byKeyID];
	}

	int8_t	Get_DIMouseState(DIM eMouse)
	{
		return m_tMouseState.rgbButtons[ETOUI(eMouse)];
	}

	// 현재 마우스의 특정 축 좌표를 반환
	int32_t	Get_DIMouseMove(DIMM eMouseState)
	{
		return *((reinterpret_cast<int32_t*>(&m_tMouseState)) + ETOUI(eMouseState));
	}
	bool_t  Key_Down(uint8_t byKey) 
	{ 
		return (m_byKeyState[byKey] & 0x80) && !(m_byPrevKeyState[byKey] & 0x80); 
	}
	bool_t  Key_Up(uint8_t byKey) 
	{ 
		return !(m_byKeyState[byKey] & 0x80) && (m_byPrevKeyState[byKey] & 0x80); 
	}
	bool_t  Key_Pressing(uint8_t byKey) 
	{ 
		return (m_byKeyState[byKey] & 0x80) != 0; 
	}

	bool_t  Mouse_Down(DIM eMouse) 
	{ 
		return (m_tMouseState.rgbButtons[ETOUI(eMouse)] & 0x80) && !(m_tPrevMouseState.rgbButtons[ETOUI(eMouse)] & 0x80); 
	}
	bool_t  Mouse_Up(DIM eMouse) 
	{ 
		return !(m_tMouseState.rgbButtons[ETOUI(eMouse)] & 0x80) && (m_tPrevMouseState.rgbButtons[ETOUI(eMouse)] & 0x80); 
	}
	bool_t  Mouse_Pressing(DIM eMouse)
	{
		return (m_tMouseState.rgbButtons[ETOUI(eMouse)] & 0x80) != 0;
	}

	POINT   Get_MousePos() 
	{ 
		return m_ptMouse; 
	}  

public:
	HRESULT Initialize(HINSTANCE hInst, HWND hWnd);
	void	Update(void);

private:
	ComPtr<IDirectInput8>			m_pInputSDK = {};

private:
	ComPtr<IDirectInputDevice8>		m_pKeyBoard = {};
	ComPtr<IDirectInputDevice8>		m_pMouse = {};

private:
	HWND					m_hWnd = {};

	int8_t					m_byPrevKeyState[256] = {};
	int8_t					m_byKeyState[256] = {};		// 키보드에 있는 모든 키값을 저장하기 위한 변수

	POINT					m_ptMouse = {};
	DIMOUSESTATE			m_tMouseState = {};
	DIMOUSESTATE			m_tPrevMouseState = {};

public:
	static unique_ptr<CInput_Device> Create(HINSTANCE hInst, HWND hWnd);
};

NS_END


