#pragma once
#include "imgui.h"
#include "EditorUI_Defines.h"

// 패널들이 같이 쓰는 ImGui 도우미
NS_BEGIN(MapTool)

inline constexpr ImGuiWindowFlags g_FixedPanelFlags =
	ImGuiWindowFlags_NoMove                 // 제목 표시줄을 드래그해도 안 움직임
	| ImGuiWindowFlags_NoResize             // 모서리를 끌어도 크기 안 바뀜
	| ImGuiWindowFlags_NoCollapse           // 제목 표시줄의 접기 버튼 제거
	| ImGuiWindowFlags_NoSavedSettings;     // 창 정보를 저장하지 않음

inline void Set_NextPanelRect(const PANEL_RECT& tRect)
{
	ImGui::SetNextWindowPos(ImVec2(tRect.fX, tRect.fY), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(tRect.fW, tRect.fH), ImGuiCond_Always);
}

// wstring -> UTF-8 (ImGui에 표시할 때)
inline string To_UTF8(const wstring_t& strWide)
{
	if (strWide.empty())
		return {};
	// 1번째 호출: 필요한 버퍼 크기만 구함
	int32_t iSize = WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), (int)strWide.size(), nullptr, 0, nullptr, nullptr);
	string strOut(iSize, '\0');
	// 2번째 호출: 실제 변환
	WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), (int)strWide.size(), strOut.data(), iSize, nullptr, nullptr);
	return strOut;
}

// UTF-8  wstring (ImGui 입력을 엔진에 넘길 때)
inline wstring_t To_Wide(const char* pUTF8)
{
	int32_t iSize = MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, nullptr, 0);   // -1: 널 문자까지 포함
	if (iSize <= 1)
		return {};
	wstring_t strOut(iSize - 1, L'\0');                                        // 널 문자 제외
	MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, strOut.data(), iSize);
	return strOut;
}

// { pName, pPath } 구조의 목록을 콤보로 그린다.
// strCurrent : 객체가 지금 가진 경로 (정규화된 태그, 소문자)
// OnChange   : 다른 항목을 골랐을 때 호출 (고른 항목의 원본 경로를 넘김)
template<typename ITEM, size_t N, typename FUNC>
void Render_AssetCombo(const char* pLabel, const ITEM(&Items)[N], const wstring_t& strCurrent, FUNC&& OnChange)
{
	// 1. 현재 값이 목록의 몇 번째인지 찾기
	int32_t iCurrent = -1;
	for (int32_t i = 0; i < static_cast<int32_t>(N); ++i)
	{
		if (Normalize_AssetPath(Items[i].pPath) == strCurrent)
		{
			iCurrent = i;
			break;
		}
	}

	// 2. 콤보 닫혀 있을 때 보일 글자
	//    목록에 없으면 (불러온 맵 등) 경로를 그대로 보여줌
	const string strPreview = (-1 != iCurrent) ? Items[iCurrent].pName : To_UTF8(strCurrent);

	// 3. 콤보
	if (ImGui::BeginCombo(pLabel, strPreview.c_str()))
	{
		for (int32_t i = 0; i < static_cast<int32_t>(N); ++i)
		{
			const bool_t bSelected = (i == iCurrent);

			if (ImGui::Selectable(Items[i].pName, bSelected) && !bSelected)
				OnChange(Items[i].pPath);

			// 콤보를 열었을 때 현재 항목으로 스크롤
			if (bSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

NS_END
