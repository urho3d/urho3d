// requires:
// defining IMGUI_INCLUDE_IMGUI_USER_H and IMGUI_INCLUDE_IMGUI_USER_INL
// at the project level

#pragma once
#ifndef IMGUI_USER_H_
#define IMGUI_USER_H_

namespace ImGui {
	
	/// addons from https://github.com/Flix01/imgui

	// Single column popup menu without icon support. It disappears when the mouse goes away.
	// Returns -1 when no entries has been selected.
	// Optional scrollUpEntryText returns index of -2,scrollDownEntryText -3 (but they must be manually handled by the user)
	IMGUI_API int PopupMenuSimple(bool& open, const char** pEntries, int numEntries, const char* optionalTitle = NULL, int* pOptionalHoveredEntryOut = NULL, int startIndex = 0, int endIndex = -1, bool reverseItems = false, const char* scrollUpEntryText = NULL, const char* scrollDownEntryText = NULL);

	// Based on the code from: https://github.com/benoitjacquier/imgui
	IMGUI_API bool ColorChooser(bool* open, ImVec4* pColorOut = NULL, bool supportsAlpha = true);
	
	// Based on the code from: https://github.com/benoitjacquier/imgui
	IMGUI_API bool ColorCombo(const char* label, ImVec4 *pColorOut = NULL, bool supportsAlpha = false, float width = 0.f, bool closeWhenMouseLeavesIt = true);
	
	// Based on the code from: https://github.com/Roflraging (see https://github.com/ocornut/imgui/issues/383)
	/*
	*pOptionalCursorPosOut;      // Out
	*pOptionalSelectionStartOut; // Out (== to SelectionEnd when no selection)
	*pOptionalSelectionEndOut;   // Out
	*/
	IMGUI_API bool InputTextMultilineWithHorizontalScrolling(const char* label, char* buf, size_t buf_size, float height, ImGuiInputTextFlags flags = 0, bool* pOptionalIsHoveredOut = NULL, int* pOptionalCursorPosOut = NULL, int* pOptionalSelectionStartOut = NULL, int* pOptionalSelectionEndOut = NULL, float SCROLL_WIDTH = 2000.f);

	// Based on the code from: https://github.com/Roflraging (see https://github.com/ocornut/imgui/issues/383)
	/*
	staticBoolVar is true if the popup_menu is open
	The three integers represent the cursorPos, the selectionStart and the selectionEnd position.
	Must be static and be in an array.
	*/
	IMGUI_API bool InputTextMultilineWithHorizontalScrollingAndCopyCutPasteMenu(const char* label, char* buf, int buf_size, float height, bool& staticBoolVar, int* staticArrayOfThreeIntegersHere, ImGuiInputTextFlags flags = 0, bool*pOptionalHoveredOut = NULL, float SCROLL_WIDTH = 2000.f, const char* copyName = NULL, const char* cutName = NULL, const char *pasteName = NULL);

	// Based on the code by krys-spectralpixel (https://github.com/krys-spectralpixel), posted here: https://github.com/ocornut/imgui/issues/261
	/* pOptionalHoveredIndex: a ptr to an optional int that is set to -1 if no tab label is hovered by the mouse.
	* pOptionalItemOrdering: an optional static array of unique integers from 0 to numTabs-1 that maps the tab label order. If one of the numbers is replaced by -1 the tab label is not visible (closed). It can be read/modified at runtime.
	* allowTabReorder (requires pOptionalItemOrdering): allows tab reordering through drag and drop (it modifies pOptionalItemOrdering).
	*                  However it seems to work only when dragging tabs from the left (top) to the right (bottom) and not vice-versa (this is bad, but can't lock the tab order in any way).
	* allowTabClosingThroughMMB (requires pOptionalItemOrdering): closes the tabs when MMB is clicked on them, by setting the tab value in pOptionalItemOrdering to -1.
	* pOptionalClosedTabIndex (requires allowTabClosingThroughMMB): out variable (int pointer) that returns the index of the closed tab in last call or -1.
	*/
	IMGUI_API bool TabLabels(int numTabs, const char** tabLabels, int& selectedIndex, const char** tabLabelTooltips = NULL, bool wrapMode = true, int* pOptionalHoveredIndex = NULL, int* pOptionalItemOrdering = NULL, bool allowTabReorder = true, bool allowTabClosingThroughMMB = true, int* pOptionalClosedTabIndex = NULL, int* pOptionalClosedTabIndexInsideItemOrdering = NULL);
	
	IMGUI_API void Separator(float height , ImGuiCol idx = ImGuiCol_Border,bool startatWindow = false, bool endatWindow = false);
	
	IMGUI_API void Separator(float height, const ImVec4& color , bool startatWindow = false, bool endatWindow = false);

	/// from https://github.com/nem0/LumixEngine/blob/master/src/studio/imgui_user.h

	IMGUI_API ImVec2 GetWindowSizeContents();

	IMGUI_API void BringToFront();

	IMGUI_API void ResetActiveID();

	IMGUI_API int PlotHistogramEx(const char* label,
		float(*values_getter)(void* data, int idx),
		void* data,
		int values_count,
		int values_offset,
		const char* overlay_text,
		float scale_min,
		float scale_max,
		ImVec2 graph_size,
		int selected_index);

	IMGUI_API bool ListBox(const char* label,
		int* current_item,
		int scroll_to_item,
		bool(*items_getter)(void*, int, const char**),
		void* data,
		int items_count,
		int height_in_items);


	IMGUI_API void BeginNode(ImGuiID id, ImVec2 screen_pos);
	IMGUI_API void EndNode(ImVec2& pos);
	IMGUI_API bool NodePin(ImGuiID id, ImVec2 screen_pos);
	IMGUI_API void NodeLink(ImVec2 from, ImVec2 to);
	IMGUI_API ImVec2 GetNodeInputPos(ImGuiID node_id, int input);
	IMGUI_API ImVec2 GetNodeOutputPos(ImGuiID node_id, int output);
	IMGUI_API void NodeSlots(int count, bool input);


	struct IMGUI_API CurveEditor
	{
		bool valid;
		ImVec2 beg_pos;
		ImVec2 prev_point;
		ImVec2 prev_tangent;
		int point_idx;
	};

	IMGUI_API CurveEditor BeginCurveEditor(const char* label);
	IMGUI_API bool CurvePoint(ImVec2* point, CurveEditor& editor);
	IMGUI_API void EndCurveEditor(const CurveEditor& editor);

	IMGUI_API int PiePopupSelectMenu(const ImVec2& center, const char* popup_id, const char** items, int items_count, int* p_selected);
}

#endif //IMGUI_USER_H_

