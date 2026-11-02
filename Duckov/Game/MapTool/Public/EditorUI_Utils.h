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

// { pDisplayName, pPath } 목록을 콤보로 그린다.
// pItems / iCount : 콤보에 보일 목록 (g_Meshes, _countof(g_Meshes))
// strCurrent      : 객체가 지금 가진 경로 (정규화된 태그, 소문자)
// 반환            : 다른 항목을 고른 프레임에만 그 항목의 원본 경로, 아니면 nullptr
inline const wchar_t* Render_AssetCombo(const char* pLabel, const ASSET_ITEM* pItems, size_t iCount, const wstring_t& strCurrentPath)
{
	// 1. 현재 값이 목록의 몇 번째인지 찾기
	int32_t iCurrentIIndex = -1;
	for (int32_t i = 0; i < static_cast<int32_t>(iCount); ++i)
	{
		if (Normalize_AssetPath(pItems[i].pPath) == strCurrentPath)
		{
			iCurrentIIndex = i;
			break;
		}
	}

	// 2. 콤보 닫혀 있을 때 보일 글자 -> 현재 선택된 항목의 콤보 표시용 글자가 들어감
	//    목록에 없으면 (불러온 맵 등) 경로를 그대로 보여줌
	string strPreview;
	if (-1 != iCurrentIIndex)
		strPreview = pItems[iCurrentIIndex].pDisplayName;
	else
		strPreview = To_UTF8(strCurrentPath);

	// 3. 콤보(토글) — 고른 항목은 기억만 해 두고 EndCombo 뒤에 반환
	const wchar_t* pPickedPath = nullptr;
	// 첫 번째 매개변수 : 토글 옆에 보일 문자 (ex. Mesh or Texture)
	// 두 번째 매개변수 : 토글 안에 보일 미리보기 문자 (위의 2번에서 구한 값)
	// 토글을 열었을 때만 true 반환
	if (ImGui::BeginCombo(pLabel, strPreview.c_str()))
	{
		for (int32_t i = 0; i < static_cast<int32_t>(iCount); ++i)
		{
			// 현재 이 항목이 객체가 쓰고있는 항목인지 확인
			const bool_t bSelected = (i == iCurrentIIndex);

			// 클릭 가능한 Rect 생성
			// Selectable -> 클릭했을 때 true 반환
			// && !bSelected 조건을 사용하여 현재 사용하지 않는 항목인데 클릭했다면 선택되었다고 판단 -> pPicked
			if (ImGui::Selectable(pItems[i].pDisplayName, bSelected) && !bSelected)
				pPickedPath = pItems[i].pPath;

			// 콤보를 열었을 때 현재 항목으로 스크롤
			if (bSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	return pPickedPath;
}


NS_END
