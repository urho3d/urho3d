// requires:
// defining IMGUI_INCLUDE_IMGUI_USER_H and IMGUI_INCLUDE_IMGUI_USER_INL
// at the project level

#pragma once
#ifndef IMGUI_USER_INL_
#define IMGUI_USER_INL_
namespace ImGui {

	static const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);
	static const float NODE_SLOT_RADIUS = 4.0f;

	int PopupMenuSimple(bool &open, const char **pEntries, int numEntries, const char *optionalTitle, int *pOptionalHoveredEntryOut, int startIndex, int endIndex, bool reverseItems, const char *scrollUpEntryText, const char *scrollDownEntryText) {
		int selectedEntry = -1;
		if (pOptionalHoveredEntryOut) *pOptionalHoveredEntryOut = -1;
		if (!open) return selectedEntry;
		if (numEntries == 0 || !pEntries) {
			open = false;
			return selectedEntry;
		}

		float fs = 1.f;
#   ifdef IMGUI_INCLUDE_IMGUI_USER_INL
		fs = ImGui::GetWindowFontScale();   // Internal to <imgui.cpp>
#   endif //   IMGUI_INCLUDE_IMGUI_USER_INL

		if (!open) return selectedEntry;
		ImGui::PushID(&open);   // or pEntries ??
								//ImGui::BeginPopup(&open);
		ImGui::OpenPopup("MyOwnPopupSimpleMenu");
		if (ImGui::BeginPopup("MyOwnPopupSimpleMenu")) {
			if (optionalTitle) { ImGui::Text("%s", optionalTitle); ImGui::Separator(); }
			if (startIndex<0) startIndex = 0;
			if (endIndex<0) endIndex = numEntries - 1;
			if (endIndex >= numEntries) endIndex = numEntries - 1;
			const bool needsScrolling = (endIndex - startIndex + 1)<numEntries;
			if (scrollUpEntryText && needsScrolling) {
				ImGui::SetWindowFontScale(fs*0.75f);
				if (reverseItems ? (endIndex + 1<numEntries) : (startIndex>0)) {
					const int entryIndex = reverseItems ? -3 : -2;
					if (ImGui::Selectable(scrollUpEntryText, false)) {
						selectedEntry = entryIndex;//open = false;    // Hide menu
					}
					else if (pOptionalHoveredEntryOut && ImGui::IsItemHovered()) *pOptionalHoveredEntryOut = entryIndex;
				}
				else ImGui::Text(" ");
				ImGui::SetWindowFontScale(fs);
			}
			if (!reverseItems) {
				for (int i = startIndex; i <= endIndex; i++) {
					const char* entry = pEntries[i];
					if (!entry || strlen(entry) == 0) ImGui::Separator();
					else {
						if (ImGui::Selectable(entry, false)) {
							selectedEntry = i; open = false;    // Hide menu
						}
						else if (pOptionalHoveredEntryOut && ImGui::IsItemHovered()) *pOptionalHoveredEntryOut = i;
					}
				}
			}
			else {
				for (int i = endIndex; i >= startIndex; i--) {
					const char* entry = pEntries[i];
					if (!entry || strlen(entry) == 0) ImGui::Separator();
					else {
						if (ImGui::Selectable(entry, false)) {
							selectedEntry = i; open = false;    // Hide menu
						}
						else if (pOptionalHoveredEntryOut && ImGui::IsItemHovered()) *pOptionalHoveredEntryOut = i;
					}

				}
			}
			if (scrollDownEntryText && needsScrolling) {
				const float fs = ImGui::GetWindowFontScale();      // Internal to <imgui.cpp>
				ImGui::SetWindowFontScale(fs*0.75f);
				if (reverseItems ? (startIndex>0) : (endIndex + 1<numEntries)) {
					const int entryIndex = reverseItems ? -2 : -3;
					if (ImGui::Selectable(scrollDownEntryText, false)) {
						selectedEntry = entryIndex;//open = false;    // Hide menu
					}
					else if (pOptionalHoveredEntryOut && ImGui::IsItemHovered()) *pOptionalHoveredEntryOut = entryIndex;
				}
				else ImGui::Text(" ");
				ImGui::SetWindowFontScale(fs);
			}
			if (open)   // close menu when mouse goes away
			{
				const float d = 10;
				ImVec2 pos = ImGui::GetWindowPos(); pos.x -= d; pos.y -= d;
				ImVec2 size = ImGui::GetWindowSize(); size.x += 2.f*d; size.y += 2.f*d;
				const ImVec2& mousePos = ImGui::GetIO().MousePos;
				if (mousePos.x<pos.x || mousePos.y<pos.y || mousePos.x>pos.x + size.x || mousePos.y>pos.y + size.y) open = false;
			}
		}
		ImGui::EndPopup();
		ImGui::PopID();

		return selectedEntry;
	}


	// Based on the code from: https://github.com/benoitjacquier/imgui
	inline static bool ColorChooserInternal(ImVec4 *pColorOut, bool supportsAlpha, bool showSliders, ImGuiWindowFlags extra_flags = 0, bool* pisAnyItemActive = NULL, float windowWidth = 180) {
		bool colorSelected = false;
		if (pisAnyItemActive) *pisAnyItemActive = false;
		const bool isCombo = (extra_flags&ImGuiWindowFlags_ComboBox);

		ImVec4 color = pColorOut ? *pColorOut : ImVec4(0, 0, 0, 1);
		if (!supportsAlpha) color.w = 1.f;

		ImGuiState& g = *GImGui;
		const float smallWidth = windowWidth / 9.f;

		static const ImU32 black = ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1));
		static const ImU32 white = ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1));
		static float hue, sat, val;

		ImGui::ColorConvertRGBtoHSV(color.x, color.y, color.z, hue, sat, val);


		ImGuiWindow* colorWindow = GetCurrentWindow();

		const float quadSize = windowWidth - smallWidth - colorWindow->WindowPadding.x * 2;
		if (isCombo) ImGui::SetCursorPosX(ImGui::GetCursorPos().x + colorWindow->WindowPadding.x);
		// Hue Saturation Value
		if (ImGui::BeginChild("ValueSaturationQuad##ValueSaturationQuadColorChooser", ImVec2(quadSize, quadSize), false, extra_flags))
			//ImGui::BeginGroup();
		{
			const int step = 5;
			ImVec2 pos = ImVec2(0, 0);
			ImGuiWindow* window = GetCurrentWindow();

			ImVec4 c00(1, 1, 1, 1);
			ImVec4 c10(1, 1, 1, 1);
			ImVec4 c01(1, 1, 1, 1);
			ImVec4 c11(1, 1, 1, 1);
			for (int y = 0; y < step; y++) {
				for (int x = 0; x < step; x++) {
					float s0 = (float)x / (float)step;
					float s1 = (float)(x + 1) / (float)step;
					float v0 = 1.0f - (float)(y) / (float)step;
					float v1 = 1.0f - (float)(y + 1) / (float)step;


					ImGui::ColorConvertHSVtoRGB(hue, s0, v0, c00.x, c00.y, c00.z);
					ImGui::ColorConvertHSVtoRGB(hue, s1, v0, c10.x, c10.y, c10.z);
					ImGui::ColorConvertHSVtoRGB(hue, s0, v1, c01.x, c01.y, c01.z);
					ImGui::ColorConvertHSVtoRGB(hue, s1, v1, c11.x, c11.y, c11.z);

					window->DrawList->AddRectFilledMultiColor(window->Pos + pos, window->Pos + pos + ImVec2(quadSize / step, quadSize / step),
						ImGui::ColorConvertFloat4ToU32(c00),
						ImGui::ColorConvertFloat4ToU32(c10),
						ImGui::ColorConvertFloat4ToU32(c11),
						ImGui::ColorConvertFloat4ToU32(c01));

					pos.x += quadSize / step;
				}
				pos.x = 0;
				pos.y += quadSize / step;
			}

			window->DrawList->AddCircle(window->Pos + ImVec2(sat, 1 - val)*quadSize, 4, val<0.5f ? white : black, 4);

			const ImGuiID id = window->GetID("ValueSaturationQuad");
			ImRect bb(window->Pos, window->Pos + window->Size);
			bool hovered, held;
			/*bool pressed = */ImGui::ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_NoKeyModifiers);///*false,*/ false);
			if (hovered) ImGui::SetMouseCursor(ImGuiMouseCursor_Move);
			if (held) {
				ImVec2 pos = g.IO.MousePos - window->Pos;
				sat = ImSaturate(pos.x / (float)quadSize);
				val = 1 - ImSaturate(pos.y / (float)quadSize);
				ImGui::ColorConvertHSVtoRGB(hue, sat, val, color.x, color.y, color.z);
				colorSelected = true;
			}

		}
		ImGui::EndChild();	// ValueSaturationQuad
							//ImGui::EndGroup();

		ImGui::SameLine();

		if (isCombo) ImGui::SetCursorPosX(ImGui::GetCursorPos().x + colorWindow->WindowPadding.x + quadSize);

		//Vertical tint
		if (ImGui::BeginChild("Tint##TintColorChooser", ImVec2(smallWidth, quadSize), false, extra_flags))
			//ImGui::BeginGroup();
		{
			const int step = 8;
			const int width = (int)smallWidth;
			ImGuiWindow* window = GetCurrentWindow();
			ImVec2 pos(0, 0);
			ImVec4 c0(1, 1, 1, 1);
			ImVec4 c1(1, 1, 1, 1);
			for (int y = 0; y < step; y++) {
				float tint0 = (float)(y) / (float)step;
				float tint1 = (float)(y + 1) / (float)step;
				ImGui::ColorConvertHSVtoRGB(tint0, 1.0, 1.0, c0.x, c0.y, c0.z);
				ImGui::ColorConvertHSVtoRGB(tint1, 1.0, 1.0, c1.x, c1.y, c1.z);

				window->DrawList->AddRectFilledMultiColor(window->Pos + pos, window->Pos + pos + ImVec2(width, quadSize / step),
					ColorConvertFloat4ToU32(c0),
					ColorConvertFloat4ToU32(c0),
					ColorConvertFloat4ToU32(c1),
					ColorConvertFloat4ToU32(c1));

				pos.y += quadSize / step;
			}

			window->DrawList->AddCircle(window->Pos + ImVec2(smallWidth*0.5f, hue*quadSize), 4, black, 4);
			//window->DrawList->AddLine(window->Pos + ImVec2(0, hue*quadSize), window->Pos + ImVec2(width, hue*quadSize), ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)));
			bool hovered, held;
			const ImGuiID id = window->GetID("Tint");
			ImRect bb(window->Pos, window->Pos + window->Size);
			/*bool pressed = */ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_NoKeyModifiers);// /*false,*/ false);
			if (hovered) ImGui::SetMouseCursor(ImGuiMouseCursor_Move);
			if (held)
			{

				ImVec2 pos = g.IO.MousePos - window->Pos;
				hue = ImClamp(pos.y / (float)quadSize, 0.0f, 1.0f);
				ImGui::ColorConvertHSVtoRGB(hue, sat, val, color.x, color.y, color.z);
				colorSelected = true;
			}

		}
		ImGui::EndChild(); // "Tint"
						   //ImGui::EndGroup();

		if (showSliders)
		{
			//Sliders
			//ImGui::PushItemHeight();
			if (isCombo) ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + colorWindow->WindowPadding.x, ImGui::GetCursorPos().y + colorWindow->WindowPadding.y + quadSize));
			ImGui::AlignFirstTextHeightToWidgets();
			ImGui::Text("Sliders");
			static bool useHsvSliders = false;
			static const char* btnNames[2] = { "to HSV","to RGB" };
			const int index = useHsvSliders ? 1 : 0;
			ImGui::SameLine();
			if (ImGui::SmallButton(btnNames[index])) useHsvSliders = !useHsvSliders;

			ImGui::Separator();
			const ImVec2 sliderSize = isCombo ? ImVec2(-1, quadSize) : ImVec2(-1, -1);
			if (ImGui::BeginChild("Sliders##SliderColorChooser", sliderSize, false, extra_flags))
			{


				{
					int r = ImSaturate(useHsvSliders ? hue : color.x)*255.f;
					int g = ImSaturate(useHsvSliders ? sat : color.y)*255.f;
					int b = ImSaturate(useHsvSliders ? val : color.z)*255.f;
					int a = ImSaturate(color.w)*255.f;

					static const char* names[2][3] = { { "R","G","B" },{ "H","S","V" } };
					bool sliderMoved = false;
					sliderMoved |= ImGui::SliderInt(names[index][0], &r, 0, 255);
					sliderMoved |= ImGui::SliderInt(names[index][1], &g, 0, 255);
					sliderMoved |= ImGui::SliderInt(names[index][2], &b, 0, 255);
					sliderMoved |= (supportsAlpha && ImGui::SliderInt("A", &a, 0, 255));
					if (sliderMoved)
					{
						colorSelected = true;
						color.x = (float)r / 255.f;
						color.y = (float)g / 255.f;
						color.z = (float)b / 255.f;
						if (useHsvSliders)  ImGui::ColorConvertHSVtoRGB(color.x, color.y, color.z, color.x, color.y, color.z);
						if (supportsAlpha) color.w = (float)a / 255.f;
					}
					//ColorConvertRGBtoHSV(s_color.x, s_color.y, s_color.z, tint, sat, val);*/
					if (pisAnyItemActive) *pisAnyItemActive |= sliderMoved;
				}


			}
			ImGui::EndChild();
		}

		if (colorSelected && pColorOut) *pColorOut = color;

		return colorSelected;
	}

	// Based on the code from: https://github.com/benoitjacquier/imgui
	bool ColorChooser(bool* open, ImVec4 *pColorOut, bool supportsAlpha) {
		static bool lastOpen = false;
		static const ImVec2 windowSize(175, 285);

		if (open && !*open) { lastOpen = false; return false; }
		if (open && *open && *open != lastOpen) {
			ImGui::SetNextWindowPos(ImGui::GetCursorScreenPos());
			ImGui::SetNextWindowSize(windowSize);
			lastOpen = *open;
		}

		//ImGui::OpenPopup("Color Chooser##myColorChoserPrivate");

		bool colorSelected = false;

		ImGuiWindowFlags WindowFlags = 0;
		//WindowFlags |= ImGuiWindowFlags_NoTitleBar;
		WindowFlags |= ImGuiWindowFlags_NoResize;
		//WindowFlags |= ImGuiWindowFlags_NoMove;
		WindowFlags |= ImGuiWindowFlags_NoScrollbar;
		WindowFlags |= ImGuiWindowFlags_NoCollapse;
		WindowFlags |= ImGuiWindowFlags_NoScrollWithMouse;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 2));

		if (open) ImGui::SetNextWindowFocus();
		//if (ImGui::BeginPopupModal("Color Chooser##myColorChoserPrivate",open,WindowFlags))
		if (ImGui::Begin("Color Chooser##myColorChoserPrivate", open, windowSize, -1.f, WindowFlags))
		{
			colorSelected = ColorChooserInternal(pColorOut, supportsAlpha, true);

			//ImGui::EndPopup();
		}
		ImGui::End();

		ImGui::PopStyleVar(2);

		return colorSelected;

	}

	// Based on the code from: https://github.com/benoitjacquier/imgui
	bool ColorCombo(const char* label, ImVec4 *pColorOut, bool supportsAlpha, float width, bool closeWhenMouseLeavesIt) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems) return false;

		ImGuiState& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		const float itemWidth = width >= 0 ? width : ImGui::CalcItemWidth();
		const ImVec2 label_size = ImGui::CalcTextSize(label);
		const float color_quad_size = (g.FontSize + style.FramePadding.x);
		const float arrow_size = (g.FontSize + style.FramePadding.x * 2.0f);
		ImVec2 totalSize = ImVec2(label_size.x + color_quad_size + arrow_size, label_size.y) + style.FramePadding*2.0f;
		if (totalSize.x < itemWidth) totalSize.x = itemWidth;
		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + totalSize);
		const ImRect total_bb(frame_bb.Min, frame_bb.Max);// + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
		ItemSize(total_bb, style.FramePadding.y);
		if (!ItemAdd(total_bb, &id)) return false;
		const float windowWidth = frame_bb.Max.x - frame_bb.Min.x - style.FramePadding.x;


		ImVec4 color = pColorOut ? *pColorOut : ImVec4(0, 0, 0, 1);
		if (!supportsAlpha) color.w = 1.f;

		const bool hovered = IsHovered(frame_bb, id);

		const ImRect value_bb(frame_bb.Min, frame_bb.Max - ImVec2(arrow_size, 0.0f));
		RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
		RenderFrame(frame_bb.Min, ImVec2(frame_bb.Min.x + color_quad_size, frame_bb.Max.y), ImColor(style.Colors[ImGuiCol_Text]), true, style.FrameRounding);
		RenderFrame(ImVec2(frame_bb.Min.x + 1, frame_bb.Min.y + 1), ImVec2(frame_bb.Min.x + color_quad_size - 1, frame_bb.Max.y - 1), ImColor(color), true, style.FrameRounding);

		RenderFrame(ImVec2(frame_bb.Max.x - arrow_size, frame_bb.Min.y), frame_bb.Max, GetColorU32(hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button), true, style.FrameRounding); // FIXME-ROUNDING
		RenderCollapseTriangle(ImVec2(frame_bb.Max.x - arrow_size, frame_bb.Min.y) + style.FramePadding, true);

		RenderTextClipped(ImVec2(frame_bb.Min.x + color_quad_size, frame_bb.Min.y) + style.FramePadding, value_bb.Max, label, NULL, NULL);

		if (hovered)
		{
			SetHoveredID(id);
			if (g.IO.MouseClicked[0])
			{
				SetActiveID(0, NULL);
				if (IsPopupOpen(id))
				{
					ClosePopup(id);
				}
				else
				{
					FocusWindow(window);
					ImGui::OpenPopup(label);
				}
			}
			static ImVec4 copiedColor(1, 1, 1, 1);
			static const ImVec4* pCopiedColor = NULL;
			if (g.IO.MouseClicked[1]) { // right-click (copy color)
				copiedColor = color;
				pCopiedColor = &copiedColor;
				//fprintf(stderr,"Copied\n");
			}
			else if (g.IO.MouseClicked[2] && pCopiedColor && pColorOut) { // middle-click (paste color)
				pColorOut->x = pCopiedColor->x;
				pColorOut->y = pCopiedColor->y;
				pColorOut->z = pCopiedColor->z;
				if (supportsAlpha) pColorOut->w = pCopiedColor->w;
				color = *pColorOut;
				//fprintf(stderr,"Pasted\n");
			}
		}

		bool value_changed = false;
		if (IsPopupOpen(id))
		{
			ImRect popup_rect(ImVec2(frame_bb.Min.x, frame_bb.Max.y), ImVec2(frame_bb.Max.x, frame_bb.Max.y));
			//popup_rect.Max.y = ImMin(popup_rect.Max.y, g.IO.DisplaySize.y - style.DisplaySafeAreaPadding.y); // Adhoc height limit for Combo. Ideally should be handled in Begin() along with other popups size, we want to have the possibility of moving the popup above as well.
			ImGui::SetNextWindowPos(popup_rect.Min);
			ImGui::SetNextWindowSize(ImVec2(windowWidth, -1));//popup_rect.GetSize());
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, style.FramePadding);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 2));

			bool mustCloseCombo = false;
			const ImGuiWindowFlags flags = ImGuiWindowFlags_ComboBox;
			if (BeginPopupEx(label, flags))
			{
				bool comboItemActive = false;
				value_changed = ColorChooserInternal(pColorOut, supportsAlpha, false, flags, &comboItemActive, windowWidth);
				if (closeWhenMouseLeavesIt && !comboItemActive)
				{
					const float distance = g.FontSize*1.75f;//1.3334f;//24;
															//fprintf(stderr,"%1.f",distance);
					ImVec2 pos = ImGui::GetWindowPos(); pos.x -= distance; pos.y -= distance;
					ImVec2 size = ImGui::GetWindowSize();
					size.x += 2.f*distance;
					size.y += 2.f*distance + windowWidth*8.f / 9.f;   // problem: is seems that ImGuiWindowFlags_ComboBox does not return the full window height
					const ImVec2& mousePos = ImGui::GetIO().MousePos;
					if (mousePos.x<pos.x || mousePos.y<pos.y || mousePos.x>pos.x + size.x || mousePos.y>pos.y + size.y) {
						mustCloseCombo = true;
						//fprintf(stderr,"Leaving ColorCombo: pos(%1f,%1f) size(%1f,%1f)\n",pos.x,pos.y,size.x,size.y);
					}
				}
				ImGui::EndPopup();
			}
			if (mustCloseCombo && IsPopupOpen(id)) ClosePopup(id);
			ImGui::PopStyleVar(3);
		}
		return value_changed;
	}


	// Based on the code from: https://github.com/Roflraging (see https://github.com/ocornut/imgui/issues/383)
	struct MultilineScrollState {
		// Input.
		float scrollRegionX;
		float scrollX;
		ImGuiStorage *storage;
		const char* textToPasteInto;
		int actionToPerformCopyCutSelectAllFrom1To3;

		// Output.
		bool newScrollPositionAvailable;
		float newScrollX;
		int CursorPos;
		int SelectionStart; //                                      // Read (== to SelectionEnd when no selection)
		int SelectionEnd;   //                                      // Read
	};
	// Based on the code from: https://github.com/Roflraging (see https://github.com/ocornut/imgui/issues/383)
	static int MultilineScrollCallback(ImGuiTextEditCallbackData *data) {
		//static int cnt=0;fprintf(stderr,"MultilineScrollCallback (%d)\n",++cnt);
		MultilineScrollState *scrollState = (MultilineScrollState *)data->UserData;

		ImGuiID cursorId = ImGui::GetID("cursor");
		int oldCursorIndex = scrollState->storage->GetInt(cursorId, 0);

		if (oldCursorIndex != data->CursorPos) {
			int begin = data->CursorPos;

			while ((begin > 0) && (data->Buf[begin - 1] != '\n')) {
				--begin;
			}

			float cursorOffset = ImGui::CalcTextSize(data->Buf + begin, data->Buf + data->CursorPos).x;
			float SCROLL_INCREMENT = scrollState->scrollRegionX * 0.25f;

			if (cursorOffset < scrollState->scrollX) {
				scrollState->newScrollPositionAvailable = true;
				scrollState->newScrollX = cursorOffset - SCROLL_INCREMENT; if (scrollState->newScrollX<0) scrollState->newScrollX = 0;
			}
			else if ((cursorOffset - scrollState->scrollRegionX) >= scrollState->scrollX) {
				scrollState->newScrollPositionAvailable = true;
				scrollState->newScrollX = cursorOffset - scrollState->scrollRegionX + SCROLL_INCREMENT;
			}
		}

		scrollState->storage->SetInt(cursorId, data->CursorPos);

		scrollState->CursorPos = data->CursorPos;
		if (data->SelectionStart <= data->SelectionEnd) { scrollState->SelectionStart = data->SelectionStart; scrollState->SelectionEnd = data->SelectionEnd; }
		else { scrollState->SelectionStart = data->SelectionEnd; scrollState->SelectionEnd = data->SelectionStart; }

		return 0;
	}
	// Based on the code from: https://github.com/Roflraging (see https://github.com/ocornut/imgui/issues/383)
	bool InputTextMultilineWithHorizontalScrolling(const char* label, char* buf, size_t buf_size, float height, ImGuiInputTextFlags flags, bool* pOptionalIsHoveredOut, int *pOptionalCursorPosOut, int *pOptionalSelectionStartOut, int *pOptionalSelectionEndOut, float SCROLL_WIDTH) {
		float scrollbarSize = ImGui::GetStyle().ScrollbarSize;
		//float labelWidth = ImGui::CalcTextSize(label).x + scrollbarSize;
		MultilineScrollState scrollState = {};

		// Set up child region for horizontal scrolling of the text box.
		ImGui::BeginChild(label, ImVec2(0/*-labelWidth*/, height), false, ImGuiWindowFlags_HorizontalScrollbar);
		scrollState.scrollRegionX = ImGui::GetWindowWidth() - scrollbarSize; if (scrollState.scrollRegionX<0) scrollState.scrollRegionX = 0;
		scrollState.scrollX = ImGui::GetScrollX();
		scrollState.storage = ImGui::GetStateStorage();
		bool changed = ImGui::InputTextMultiline(label, buf, buf_size, ImVec2(SCROLL_WIDTH - scrollbarSize, (height - scrollbarSize)>0 ? (height - scrollbarSize) : 0),
			flags | ImGuiInputTextFlags_CallbackAlways, MultilineScrollCallback, &scrollState);
		if (pOptionalIsHoveredOut) *pOptionalIsHoveredOut = ImGui::IsItemHovered();

		if (scrollState.newScrollPositionAvailable) {
			ImGui::SetScrollX(scrollState.newScrollX);
		}

		ImGui::EndChild();
		//ImGui::SameLine();
		//ImGui::Text("%s",label);

		if (pOptionalCursorPosOut) *pOptionalCursorPosOut = scrollState.CursorPos;
		if (pOptionalSelectionStartOut) *pOptionalSelectionStartOut = scrollState.SelectionStart;
		if (pOptionalSelectionEndOut)   *pOptionalSelectionEndOut = scrollState.SelectionEnd;

		return changed;
	}

	// Based on the code from: https://github.com/Roflraging (see https://github.com/ocornut/imgui/issues/383)
	bool InputTextMultilineWithHorizontalScrollingAndCopyCutPasteMenu(const char *label, char *buf, int buf_size, float height, bool& staticBoolVar, int *staticArrayOfThreeIntegersHere, ImGuiInputTextFlags flags, bool *pOptionalHoveredOut, float SCROLL_WIDTH, const char *copyName, const char *cutName, const char* pasteName) {
		bool isHovered = false;
		int& cursorPos = staticArrayOfThreeIntegersHere[0];
		int& selectionStart = staticArrayOfThreeIntegersHere[1];
		int& selectionEnd = staticArrayOfThreeIntegersHere[2];
		bool& popup_open = staticBoolVar;
		const bool changed = InputTextMultilineWithHorizontalScrolling(label, buf, (size_t)buf_size, height, flags, &isHovered, popup_open ? NULL : &cursorPos, popup_open ? NULL : &selectionStart, popup_open ? NULL : &selectionEnd, SCROLL_WIDTH);
		if (pOptionalHoveredOut) *pOptionalHoveredOut = isHovered;
		// Popup Menu ------------------------------------------

		const bool readOnly = flags&ImGuiInputTextFlags_ReadOnly;       // "Cut","","Paste" not available
		const bool hasSelectedText = selectionStart != selectionEnd;	// "Copy","Cut" available

		if (hasSelectedText || !readOnly) {
			const bool onlyPaste = !readOnly && !hasSelectedText;
			const char* clipboardText = ImGui::GetIO().GetClipboardTextFn();
			const bool canPaste = clipboardText && strlen(clipboardText)>0;
			if (onlyPaste && !canPaste) popup_open = false;
			else {
				static const char* entries[] = { "Copy","Cut","","Paste" };   // "" is separator
				const char* pEntries[4] = { copyName ? copyName : entries[0],cutName ? cutName : entries[1],entries[2],pasteName ? pasteName : entries[3] };
				popup_open |= ImGui::GetIO().MouseClicked[1] && isHovered; // RIGHT CLICK
				int sel = ImGui::PopupMenuSimple(popup_open, onlyPaste ? &pEntries[3] : pEntries, (readOnly || onlyPaste) ? 1 : canPaste ? 4 : 2);
				if (sel == 3) sel = 2; // Normally separator takes out one space
				const bool mustCopy = sel == 0 && !onlyPaste;
				const bool mustCut = !mustCopy && sel == 1;
				const bool mustPaste = !mustCopy && !mustCut && (sel == 2 || (sel == 0 && onlyPaste));
				if (mustCopy || mustCut || (mustPaste && (selectionStart<selectionEnd))) {
					// Copy to clipboard
					if (!mustPaste) {
						const char tmp = buf[selectionEnd]; buf[selectionEnd] = '\0';
						ImGui::GetIO().SetClipboardTextFn(&buf[selectionStart]);
						buf[selectionEnd] = tmp;
					}
					// Delete chars
					if (!mustCopy) {
						//if (mustPaste) {fprintf(stderr,"Deleting before pasting: %d  %d.\n",selectionStart,selectionEnd);}
						strncpy(&buf[selectionStart], &buf[selectionEnd], buf_size - selectionEnd);
						for (int i = selectionStart + buf_size - selectionEnd; i<buf_size; i++) buf[i] = '\0';
					}
					popup_open = false;
				}
				if (mustPaste) {
					// This is VERY HARD to make it work as expected...
					const int cursorPosition = (selectionStart<selectionEnd) ? selectionStart : cursorPos;
					const int clipboardTextSize = strlen(clipboardText);
					int buf_len = strlen(buf); if (buf_len>buf_size) buf_len = buf_size;

					// Step 1- Shift [cursorPosition] to [cursorPosition+clipboardTextSize]
					const int numCharsToShiftRight = buf_len - cursorPosition;
					//fprintf(stderr,"Pasting: \"%s\"(%d) at %d. buf_len=%d buf_size=%d numCharsToShiftRight=%d\n",clipboardText,clipboardTextSize,cursorPosition,buf_len,buf_size,numCharsToShiftRight);

					for (int i = cursorPosition + numCharsToShiftRight>buf_size ? buf_size - 1 : cursorPosition + numCharsToShiftRight - 1; i >= cursorPosition; i--) {
						if (i + clipboardTextSize<buf_size) {
							//fprintf(stderr,"moving to the right char (%d): '%c' (%d)\n",i,buf[i],(int)buf[i]);
							buf[i + clipboardTextSize] = buf[i];
						}
					}
					// Step 2- Overwrite [cursorPosition] o [cursorPosition+clipboardTextSize]
					for (int i = cursorPosition, isz = cursorPosition + clipboardTextSize >= buf_size ? buf_size : cursorPosition + clipboardTextSize; i<isz; i++) buf[i] = clipboardText[i - cursorPosition];

					popup_open = false;
				}
			}
		}
		else popup_open = false;
		//------------------------------------------------------------------
		return changed;
	}



	// Based on the code by krys-spectralpixel (https://github.com/krys-spectralpixel), posted here: https://github.com/ocornut/imgui/issues/261
	bool TabLabels(int numTabs, const char** tabLabels, int& selectedIndex, const char** tabLabelTooltips, bool wrapMode, int *pOptionalHoveredIndex, int* pOptionalItemOrdering, bool allowTabReorder, bool allowTabClosingThroughMMB, int *pOptionalClosedTabIndex, int *pOptionalClosedTabIndexInsideItemOrdering) {
		ImGuiStyle& style = ImGui::GetStyle();

		const ImVec2 itemSpacing = style.ItemSpacing;
		const ImVec4 color = style.Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		const ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
		const ImVec4 colorText = style.Colors[ImGuiCol_Text];
		style.ItemSpacing.x = 1;
		style.ItemSpacing.y = 1;

		const ImVec4 colorSelectedTab(color.x, color.y, color.z, color.w*0.5f);
		const ImVec4 colorSelectedTabHovered(colorHover.x, colorHover.y, colorHover.z, colorHover.w*0.5f);
		const ImVec4 colorSelectedTabText(colorText.x*0.8f, colorText.y*0.8f, colorText.z*0.8f, colorText.w*0.8f);
		//ImGui::ClampColor(colorSelectedTabText);

		if (numTabs>0 && (selectedIndex<0 || selectedIndex >= numTabs)) {
			if (!pOptionalItemOrdering)  selectedIndex = 0;
			else selectedIndex = -1;
		}
		if (pOptionalHoveredIndex) *pOptionalHoveredIndex = -1;
		if (pOptionalClosedTabIndex) *pOptionalClosedTabIndex = -1;
		if (pOptionalClosedTabIndexInsideItemOrdering) *pOptionalClosedTabIndexInsideItemOrdering = -1;

		float windowWidth = 0.f, sumX = 0.f;
		if (wrapMode) windowWidth = ImGui::GetWindowWidth() - style.WindowPadding.x - (ImGui::GetScrollMaxY()>0 ? style.ScrollbarSize : 0.f);

		static int draggingTabIndex = -1; int draggingTabTargetIndex = -1;   // These are indices inside pOptionalItemOrdering
		static ImVec2 draggingTabSize(0, 0);
		static ImVec2 draggingTabOffset(0, 0);

		const bool isMMBreleased = ImGui::IsMouseReleased(2);
		const bool isMouseDragging = ImGui::IsMouseDragging(0, 2.f);
		int justClosedTabIndex = -1, newSelectedIndex = selectedIndex;


		bool selection_changed = false; bool noButtonDrawn = true;
		for (int j = 0, i; j < numTabs; j++)
		{
			i = pOptionalItemOrdering ? pOptionalItemOrdering[j] : j;
			if (i == -1) continue;

			if (!wrapMode) { if (!noButtonDrawn) ImGui::SameLine(); }
			else if (sumX > 0.f) {
				sumX += style.ItemSpacing.x;   // Maybe we can skip it if we use SameLine(0,0) below
				sumX += ImGui::CalcTextSize(tabLabels[i]).x + 2.f*style.FramePadding.x;
				if (sumX>windowWidth) sumX = 0.f;
				else ImGui::SameLine();
			}

			if (i != selectedIndex) {
				// Push the style
				style.Colors[ImGuiCol_Button] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonActive] = colorSelectedTabHovered;
				style.Colors[ImGuiCol_ButtonHovered] = colorSelectedTabHovered;
				style.Colors[ImGuiCol_Text] = colorSelectedTabText;
			}
			// Draw the button
			ImGui::PushID(i);   // otherwise two tabs with the same name would clash.
			if (ImGui::Button(tabLabels[i])) { selection_changed = (selectedIndex != i); newSelectedIndex = i; }
			ImGui::PopID();
			if (i != selectedIndex) {
				// Reset the style
				style.Colors[ImGuiCol_Button] = color;
				style.Colors[ImGuiCol_ButtonActive] = colorActive;
				style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				style.Colors[ImGuiCol_Text] = colorText;
			}
			
			noButtonDrawn = false;

			if (wrapMode) {
				if (sumX == 0.f) sumX = style.WindowPadding.x + ImGui::GetItemRectSize().x; // First element of a line
			}
			else if (isMouseDragging && allowTabReorder && pOptionalItemOrdering) {
				// We still need sumX
				if (sumX == 0.f) sumX = style.WindowPadding.x + ImGui::GetItemRectSize().x; // First element of a line
				else sumX += style.ItemSpacing.x + ImGui::GetItemRectSize().x;

			}

			if (ImGui::IsItemHoveredRect()) {
				if (pOptionalHoveredIndex) *pOptionalHoveredIndex = i;
				if (tabLabelTooltips && tabLabelTooltips[i] && strlen(tabLabelTooltips[i])>0)  ImGui::SetTooltip("%s", tabLabelTooltips[i]);

				if (pOptionalItemOrdering) {
					if (allowTabReorder) {
						if (isMouseDragging) {
							if (draggingTabIndex == -1) {
								draggingTabIndex = j;
								draggingTabSize = ImGui::GetItemRectSize();
								const ImVec2& mp = ImGui::GetIO().MousePos;
								const ImVec2 draggingTabCursorPos = ImGui::GetCursorPos();
								draggingTabOffset = ImVec2(
									mp.x + draggingTabSize.x*0.5f - sumX + ImGui::GetScrollX(),
									mp.y + draggingTabSize.y*0.5f - draggingTabCursorPos.y + ImGui::GetScrollY()
									);

							}
						}
						else if (draggingTabIndex >= 0 && draggingTabIndex<numTabs && draggingTabIndex != j) {
							draggingTabTargetIndex = j; // For some odd reasons this seems to get called only when draggingTabIndex < i ! (Probably during mouse dragging ImGui owns the mouse someway and sometimes ImGui::IsItemHovered() is not getting called)
						}
					}
					if (allowTabClosingThroughMMB) {
						if (isMMBreleased) {
							justClosedTabIndex = i;
							if (pOptionalClosedTabIndex) *pOptionalClosedTabIndex = i;
							if (pOptionalClosedTabIndexInsideItemOrdering) *pOptionalClosedTabIndexInsideItemOrdering = j;
							pOptionalItemOrdering[j] = -1;
						}
					}
				}
			}

		}

		selectedIndex = newSelectedIndex;

		// Draw tab label while mouse drags it
		if (draggingTabIndex >= 0 && draggingTabIndex<numTabs) {
			const ImVec2& mp = ImGui::GetIO().MousePos;
			const ImVec2 wp = ImGui::GetWindowPos();
			ImVec2 start(wp.x + mp.x - draggingTabOffset.x - draggingTabSize.x*0.5f, wp.y + mp.y - draggingTabOffset.y - draggingTabSize.y*0.5f);
			const ImVec2 end(start.x + draggingTabSize.x, start.y + draggingTabSize.y);
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			const float draggedBtnAlpha = 0.65f;
			const ImVec4& btnColor = style.Colors[ImGuiCol_Button];
			drawList->AddRectFilled(start, end, ImColor(btnColor.x, btnColor.y, btnColor.z, btnColor.w*draggedBtnAlpha), style.FrameRounding);
			start.x += style.FramePadding.x; start.y += style.FramePadding.y;
			const ImVec4& txtColor = style.Colors[ImGuiCol_Text];
			drawList->AddText(start, ImColor(txtColor.x, txtColor.y, txtColor.z, txtColor.w*draggedBtnAlpha), tabLabels[pOptionalItemOrdering[draggingTabIndex]]);

			ImGui::SetMouseCursor(ImGuiMouseCursor_Move);
		}

		// Drop tab label
		if (draggingTabTargetIndex != -1) {
			// swap draggingTabIndex and draggingTabTargetIndex in pOptionalItemOrdering
			const int tmp = pOptionalItemOrdering[draggingTabTargetIndex];
			pOptionalItemOrdering[draggingTabTargetIndex] = pOptionalItemOrdering[draggingTabIndex];
			pOptionalItemOrdering[draggingTabIndex] = tmp;
			//fprintf(stderr,"%d %d\n",draggingTabIndex,draggingTabTargetIndex);
			draggingTabTargetIndex = draggingTabIndex = -1;
		}

		// Reset draggingTabIndex if necessary
		if (!isMouseDragging) draggingTabIndex = -1;

		// Change selected tab when user closes the selected tab
		if (selectedIndex == justClosedTabIndex && selectedIndex >= 0) {
			selectedIndex = -1;
			for (int j = 0, i; j < numTabs; j++) {
				i = pOptionalItemOrdering ? pOptionalItemOrdering[j] : j;
				if (i == -1) continue;
				selectedIndex = i;
				break;
			}
		}

		// Restore the style
		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		style.Colors[ImGuiCol_Text] = colorText;
		style.ItemSpacing = itemSpacing;

		return selection_changed;
	}
	void Separator(float height, ImGuiCol idx, bool startatWindow, bool endatWindow)
	{
		ImGuiState& g = *GImGui;
		Separator(height, g.Style.Colors[idx], startatWindow, endatWindow);
	}

	void Separator(float height ,const ImVec4& color, bool startatWindow,bool endatWindow)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return;

		if (window->DC.ColumnsCount > 1)
			PopClipRect();

		float x1 = 0.0f; 
		float x2 = 0.0f; 
		float x3 = endatWindow ? window->Size.x : GetContentRegionAvail().x;
		if(!startatWindow)
		{
			x1 = window->DC.CursorPos.x;
			x2 = window->DC.CursorPos.x + x3;
		}
		else
		{
			x1 =  window->Pos.x;
			x2 =  window->Pos.x + x3;
		}

		if (!window->DC.GroupStack.empty())
			x1 += window->DC.IndentX;

		const ImRect bb(ImVec2(x1, window->DC.CursorPos.y), ImVec2(x2, window->DC.CursorPos.y));
		ImGuiState& g = *GImGui;
	

		float temp =	g.Style.ItemSpacing.y;
		g.Style.ItemSpacing.y = 0.f;

		ItemSize(ImVec2(0.0f, height-1.0f)); // NB: we don't provide our width so that it doesn't get feed back into AutoFit   // FIXME: Height should be 1.0f not 0.0f ?
		if (!ItemAdd(bb, NULL))
		{
			if (window->DC.ColumnsCount > 1)
				PushColumnClipRect();
			g.Style.ItemSpacing.y = temp;
			return;
		}
		g.Style.ItemSpacing.y = temp;
		window->DrawList->AddLine(bb.Min, bb.Max, GetColorU32(color),height);

		if (g.LogEnabled)
			ImGui::LogText(IM_NEWLINE "--------------------------------");

		if (window->DC.ColumnsCount > 1)
		{
			PushColumnClipRect();
			window->DC.ColumnsCellMinY = window->DC.CursorPos.y;
		}	
	}


	void BringToFront()
	{
		ImGuiState& g = *GImGui;

		ImGuiWindow* window = GImGui->CurrentWindow;

		if ((window->Flags & ImGuiWindowFlags_NoBringToFrontOnFocus) || g.Windows.back() == window)
		{
			return;
		}
		for (int i = 0; i < g.Windows.Size; i++)
		{
			if (g.Windows[i] == window)
			{
				g.Windows.erase(g.Windows.begin() + i);
				break;
			}
		}
		g.Windows.push_back(window);
	}


	ImVec2 GetWindowSizeContents()
	{
		ImGuiWindow* window = GetCurrentWindowRead();
		return window->SizeContents;
	}

	void ResetActiveID()
	{
		SetActiveID(0);
	}

	int PlotHistogramEx(const char* label,
		float(*values_getter)(void* data, int idx),
		void* data,
		int values_count,
		int values_offset,
		const char* overlay_text,
		float scale_min,
		float scale_max,
		ImVec2 graph_size,
		int selected_index)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems) return -1;

		ImGuiState& g = *GImGui;
		const ImGuiStyle& style = g.Style;

		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		if (graph_size.x == 0.0f) graph_size.x = CalcItemWidth() + (style.FramePadding.x * 2);
		if (graph_size.y == 0.0f) graph_size.y = label_size.y + (style.FramePadding.y * 2);

		const ImRect frame_bb(
			window->DC.CursorPos, window->DC.CursorPos + ImVec2(graph_size.x, graph_size.y));
		const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
		const ImRect total_bb(frame_bb.Min,
			frame_bb.Max +
			ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0));
		ItemSize(total_bb, style.FramePadding.y);
		if (!ItemAdd(total_bb, NULL)) return -1;

		// Determine scale from values if not specified
		if (scale_min == FLT_MAX || scale_max == FLT_MAX)
		{
			float v_min = FLT_MAX;
			float v_max = -FLT_MAX;
			for (int i = 0; i < values_count; i++)
			{
				const float v = values_getter(data, i);
				v_min = ImMin(v_min, v);
				v_max = ImMax(v_max, v);
			}
			if (scale_min == FLT_MAX) scale_min = v_min;
			if (scale_max == FLT_MAX) scale_max = v_max;
		}

		RenderFrame(
			frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

		int res_w = ImMin((int)graph_size.x, values_count);

		// Tooltip on hover
		int v_hovered = -1;
		if (IsHovered(inner_bb, 0))
		{
			const float t = ImClamp(
				(g.IO.MousePos.x - inner_bb.Min.x) / (inner_bb.Max.x - inner_bb.Min.x), 0.0f, 0.9999f);
			const int v_idx = (int)(t * (values_count + 0));
			IM_ASSERT(v_idx >= 0 && v_idx < values_count);

			const float v0 = values_getter(data, (v_idx + values_offset) % values_count);
			ImGui::SetTooltip("%d: %8.4g", v_idx, v0);
			v_hovered = v_idx;
		}

		const float t_step = 1.0f / (float)res_w;

		float v0 = values_getter(data, (0 + values_offset) % values_count);
		float t0 = 0.0f;
		ImVec2 p0 = ImVec2(t0, 1.0f - ImSaturate((v0 - scale_min) / (scale_max - scale_min)));

		const ImU32 col_base = GetColorU32(ImGuiCol_PlotHistogram);
		const ImU32 col_hovered = GetColorU32(ImGuiCol_PlotHistogramHovered);

		for (int n = 0; n < res_w; n++)
		{
			const float t1 = t0 + t_step;
			const int v_idx = (int)(t0 * values_count + 0.5f);
			IM_ASSERT(v_idx >= 0 && v_idx < values_count);
			const float v1 = values_getter(data, (v_idx + values_offset + 1) % values_count);
			const ImVec2 p1 = ImVec2(t1, 1.0f - ImSaturate((v1 - scale_min) / (scale_max - scale_min)));

			window->DrawList->AddRectFilled(ImLerp(inner_bb.Min, inner_bb.Max, p0),
				ImLerp(inner_bb.Min, inner_bb.Max, ImVec2(p1.x, 1.0f)) + ImVec2(-1, 0),
				selected_index == v_idx ? col_hovered : col_base);

			t0 = t1;
			p0 = p1;
		}

		if (overlay_text)
		{
			RenderTextClipped(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y),
				frame_bb.Max,
				overlay_text,
				NULL,
				NULL,
				ImGuiAlign_Center);
		}

		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, inner_bb.Min.y), label);

		if (v_hovered >= 0 && IsMouseClicked(0))
		{
			return v_hovered;
		}
		return -1;
	}


	bool ListBox(const char* label,
		int* current_item,
		int scroll_to_item,
		bool(*items_getter)(void*, int, const char**),
		void* data,
		int items_count,
		int height_in_items)
	{
		if (!ImGui::ListBoxHeader(label, items_count, height_in_items))
			return false;

		// Assume all items have even height (= 1 line of text). If you need items of different or variable sizes you can create a custom version of ListBox() in your code without using the clipper.
		bool value_changed = false;
		if (scroll_to_item != -1)
		{
			ImGui::SetScrollY(scroll_to_item * ImGui::GetTextLineHeightWithSpacing());
		}
		ImGuiListClipper clipper(items_count, ImGui::GetTextLineHeightWithSpacing());
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			const bool item_selected = (i == *current_item);
			const char* item_text;
			if (!items_getter(data, i, &item_text))
				item_text = "*Unknown item*";

			ImGui::PushID(i);
			if (ImGui::Selectable(item_text, item_selected))
			{
				*current_item = i;
				value_changed = true;
			}
			ImGui::PopID();
		}
		clipper.End();
		ImGui::ListBoxFooter();
		return value_changed;
	}



	static ImVec2 node_pos;
	static ImGuiID last_node_id;


	void BeginNode(ImGuiID id, ImVec2 screen_pos)
	{
		PushID(id);
		last_node_id = id;
		node_pos = screen_pos;
		ImGui::SetCursorScreenPos(screen_pos + ImGui::GetStyle().WindowPadding);
		ImGui::PushItemWidth(200);
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->ChannelsSplit(2);
		draw_list->ChannelsSetCurrent(1);
		ImGui::BeginGroup();
	}


	void EndNode(ImVec2& pos)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		ImGui::EndGroup();
		ImGui::PopItemWidth();

		float height = ImGui::GetCursorScreenPos().y - node_pos.y;
		ImVec2 size(200, height + ImGui::GetStyle().WindowPadding.y);
		ImGui::SetCursorScreenPos(node_pos);

		ImGui::SetNextWindowPos(node_pos);
		ImGui::SetNextWindowSize(size);
		ImGui::BeginChild((ImGuiID)last_node_id, size, false, ImGuiWindowFlags_NoInputs);
		ImGui::EndChild();

		ImGui::SetCursorScreenPos(node_pos);
		ImGui::InvisibleButton("bg", size);
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
		{
			pos += ImGui::GetIO().MouseDelta;
		}

		draw_list->ChannelsSetCurrent(0);
		draw_list->AddRectFilled(node_pos, node_pos + size, ImColor(60, 60, 60), 4.0f);
		draw_list->AddRect(node_pos, node_pos + size, ImColor(100, 100, 100), 4.0f);

		PopID();
		draw_list->ChannelsMerge();
	}


	ImVec2 GetNodeInputPos(ImGuiID id, int input)
	{
		ImGui::PushID(id);

		ImGuiWindow* parent_win = ImGui::GetCurrentWindow();
		char title[256];
		ImFormatString(title, IM_ARRAYSIZE(title), "%s.child_%08x", parent_win->Name, id);
		ImGuiWindow* win = FindWindowByName(title);
		if (!win)
		{
			ImGui::PopID();
			return ImVec2(0, 0);
		}

		ImVec2 pos = win->Pos;
		pos.x -= NODE_SLOT_RADIUS;
		ImGuiStyle& style = ImGui::GetStyle();
		pos.y += (ImGui::GetTextLineHeight() + style.ItemSpacing.y) * input;
		pos.y += style.WindowPadding.y + ImGui::GetTextLineHeight() * 0.5f;


		ImGui::PopID();
		return pos;
	}


	ImVec2 GetNodeOutputPos(ImGuiID id, int output)
	{
		ImGui::PushID(id);

		ImGuiWindow* parent_win = ImGui::GetCurrentWindow();
		char title[256];
		ImFormatString(title, IM_ARRAYSIZE(title), "%s.child_%08x", parent_win->Name, id);
		ImGuiWindow* win = FindWindowByName(title);
		if (!win)
		{
			ImGui::PopID();
			return ImVec2(0, 0);
		}

		ImVec2 pos = win->Pos;
		pos.x += win->Size.x + NODE_SLOT_RADIUS;
		ImGuiStyle& style = ImGui::GetStyle();
		pos.y += (ImGui::GetTextLineHeight() + style.ItemSpacing.y) * output;
		pos.y += style.WindowPadding.y + ImGui::GetTextLineHeight() * 0.5f;

		ImGui::PopID();
		return pos;
	}


	bool NodePin(ImGuiID id, ImVec2 screen_pos)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImGui::SetCursorScreenPos(screen_pos - ImVec2(NODE_SLOT_RADIUS, NODE_SLOT_RADIUS));
		ImGui::PushID(id);
		ImGui::InvisibleButton("", ImVec2(2 * NODE_SLOT_RADIUS, 2 * NODE_SLOT_RADIUS));
		bool hovered = ImGui::IsItemHovered();
		ImGui::PopID();
		draw_list->AddCircleFilled(screen_pos,
			NODE_SLOT_RADIUS,
			hovered ? ImColor(0, 150, 0, 150) : ImColor(150, 150, 150, 150));
		return hovered;
	}


	void NodeLink(ImVec2 from, ImVec2 to)
	{
		ImVec2 p1 = from;
		ImVec2 t1 = ImVec2(+80.0f, 0.0f);
		ImVec2 p2 = to;
		ImVec2 t2 = ImVec2(+80.0f, 0.0f);
		const int STEPS = 12;
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		for (int step = 0; step <= STEPS; step++)
		{
			float t = (float)step / (float)STEPS;
			float h1 = +2 * t*t*t - 3 * t*t + 1.0f;
			float h2 = -2 * t*t*t + 3 * t*t;
			float h3 = t*t*t - 2 * t*t + t;
			float h4 = t*t*t - t*t;
			draw_list->PathLineTo(ImVec2(h1*p1.x + h2*p2.x + h3*t1.x + h4*t2.x, h1*p1.y + h2*p2.y + h3*t1.y + h4*t2.y));
		}
		draw_list->PathStroke(ImColor(200, 200, 100), false, 3.0f);
	}


	ImVec2 operator *(float f, const ImVec2& v)
	{
		return ImVec2(f * v.x, f * v.y);
	}


	CurveEditor BeginCurveEditor(const char* label)
	{
		CurveEditor editor;
		editor.valid = false;

		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems) return editor;

		ImGuiState& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();

		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 graph_size;
		graph_size.x = CalcItemWidth() + (style.FramePadding.x * 2);
		graph_size.y = 100; // label_size.y + (style.FramePadding.y * 2);

		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(graph_size.x, graph_size.y));
		const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
		const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0));

		ItemSize(total_bb, style.FramePadding.y);
		if (!ItemAdd(total_bb, NULL))
			return editor;

		editor.valid = true;
		ImGui::PushID(label);

		RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, inner_bb.Min.y), label);

		editor.beg_pos = cursor_pos;
		ImGui::SetCursorScreenPos(cursor_pos);

		editor.point_idx = -1;

		return editor;
	}


	void EndCurveEditor(const CurveEditor& editor)
	{
		ImGui::SetCursorScreenPos(editor.beg_pos);

		InvisibleButton("bg", ImVec2(ImGui::CalcItemWidth(), 100));
		ImGui::PopID();
	}


	bool CurvePoint(ImVec2* points, CurveEditor& editor)
	{
		ImGuiWindow* window = GetCurrentWindow();
		ImGuiState& g = *GImGui;
		const ImGuiStyle& style = g.Style;

		ImVec2 cursor_pos_backup = ImGui::GetCursorScreenPos();

		ImVec2 graph_size;
		graph_size.x = CalcItemWidth() + (style.FramePadding.x * 2);
		graph_size.y = 100; // label_size.y + (style.FramePadding.y * 2);

		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + graph_size);
		const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
		const ImU32 col_base = GetColorU32(ImGuiCol_PlotLines);
		const ImU32 col_hovered = GetColorU32(ImGuiCol_PlotLinesHovered);

		ImVec2 left_tangent = points[0];
		ImVec2 right_tangent = points[2];
		ImVec2 p = points[1];
#define transform(p) ImVec2(inner_bb.Min.x * (1 - (p).x) + inner_bb.Max.x * (p).x, inner_bb.Min.y * (p).y + inner_bb.Max.y * (1 - (p).y))

//		auto transform = [inner_bb](const ImVec2& p) -> ImVec2
//		{
//			return ImVec2(inner_bb.Min.x * (1 - p.x) + inner_bb.Max.x * p.x,
//				inner_bb.Min.y * p.y + inner_bb.Max.y * (1 - p.y));
//		};

		ImVec2 pos = transform(p);
		if (editor.point_idx >= 0)
		{
			window->DrawList->AddBezierCurve(pos,
				transform(p + left_tangent),
				transform(editor.prev_point + editor.prev_tangent),
				transform(editor.prev_point),
				col_base,
				1.0f, 20);
		}
#undef transform
		editor.prev_point = p;
		editor.prev_tangent = right_tangent;

		static const float SIZE = 3;
		ImGui::SetCursorScreenPos(pos - ImVec2(SIZE, SIZE));
		ImGui::PushID(editor.point_idx);
		++editor.point_idx;
		ImGui::InvisibleButton("", ImVec2(2 * NODE_SLOT_RADIUS, 2 * NODE_SLOT_RADIUS));

		ImU32 col = ImGui::IsItemHovered() ? col_hovered : col_base;

		window->DrawList->AddLine(pos + ImVec2(-SIZE, 0), pos + ImVec2(0, SIZE), col);
		window->DrawList->AddLine(pos + ImVec2(SIZE, 0), pos + ImVec2(0, SIZE), col);
		window->DrawList->AddLine(pos + ImVec2(SIZE, 0), pos + ImVec2(0, -SIZE), col);
		window->DrawList->AddLine(pos + ImVec2(-SIZE, 0), pos + ImVec2(0, -SIZE), col);

		bool changed = false;
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
		{
			pos += ImGui::GetIO().MouseDelta;
			ImVec2 v;
			v.x = (pos.x - inner_bb.Min.x) / (inner_bb.Max.x - inner_bb.Min.x);
			v.y = (inner_bb.Max.y - pos.y) / (inner_bb.Max.y - inner_bb.Min.y);

			v = ImClamp(v, ImVec2(0, 0), ImVec2(1, 1));
			points[1] = v;
			changed = true;
		}
		ImGui::PopID();

		ImGui::SetCursorScreenPos(cursor_pos_backup);
		return changed;
	}


	// Return >= 0 on mouse release
	// Optional int* p_selected display and update a currently selected item
	int PiePopupSelectMenu(const ImVec2& center, const char* popup_id, const char** items, int items_count, int* p_selected)
	{
		int ret = -1;

		// FIXME: Missing a call to query if Popup is open so we can move the PushStyleColor inside the BeginPopupBlock (e.g. IsPopupOpen() in imgui.cpp)
		// FIXME: Our PathFill function only handle convex polygons, so we can't have items spanning an arc too large else inner concave edge artifact is too visible, hence the ImMax(7,items_count)
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
		if (ImGui::BeginPopup(popup_id))
		{
			const ImVec2 drag_delta = ImVec2(ImGui::GetIO().MousePos.x - center.x, ImGui::GetIO().MousePos.y - center.y);
			const float drag_dist2 = drag_delta.x*drag_delta.x + drag_delta.y*drag_delta.y;

			const ImGuiStyle& style = ImGui::GetStyle();
			const float RADIUS_MIN = 30.0f;
			const float RADIUS_MAX = 120.0f;
			const float RADIUS_INTERACT_MIN = 20.0f;
			const int ITEMS_MIN = 6;

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			//ImGuiWindow* window = ImGui::GetCurrentWindow();
			draw_list->PushClipRectFullScreen();
			draw_list->PathArcTo(center, (RADIUS_MIN + RADIUS_MAX)*0.5f, 0.0f, IM_PI*2.0f*0.99f, 32);   // FIXME: 0.99f look like full arc with closed thick stroke has a bug now
			draw_list->PathStroke(ImColor(0, 0, 0), true, RADIUS_MAX - RADIUS_MIN);

			const float item_arc_span = 2 * IM_PI / ImMax(ITEMS_MIN, items_count);
			float drag_angle = atan2f(drag_delta.y, drag_delta.x);
			if (drag_angle < -0.5f*item_arc_span)
				drag_angle += 2.0f*IM_PI;
			//ImGui::Text("%f", drag_angle);    // [Debug]

			int item_hovered = -1;
			for (int item_n = 0; item_n < items_count; item_n++)
			{
				const char* item_label = items[item_n];
				const float item_ang_min = item_arc_span * (item_n + 0.02f) - item_arc_span*0.5f; // FIXME: Could calculate padding angle based on how many pixels they'll take
				const float item_ang_max = item_arc_span * (item_n + 0.98f) - item_arc_span*0.5f;

				bool hovered = false;
				if (drag_dist2 >= RADIUS_INTERACT_MIN*RADIUS_INTERACT_MIN)
				{
					if (drag_angle >= item_ang_min && drag_angle < item_ang_max)
						hovered = true;
				}
				bool selected = p_selected && (*p_selected == item_n);

				int arc_segments = (int)(32 * item_arc_span / (2 * IM_PI)) + 1;
				draw_list->PathArcTo(center, RADIUS_MAX - style.ItemInnerSpacing.x, item_ang_min, item_ang_max, arc_segments);
				draw_list->PathArcTo(center, RADIUS_MIN + style.ItemInnerSpacing.x, item_ang_max, item_ang_min, arc_segments);
				//draw_list->PathFill(window->Color(hovered ? ImGuiCol_HeaderHovered : ImGuiCol_FrameBg));
				draw_list->PathFill(hovered ? ImColor(100, 100, 150) : selected ? ImColor(120, 120, 140) : ImColor(70, 70, 70));

				ImVec2 text_size = ImGui::GetWindowFont()->CalcTextSizeA(ImGui::GetWindowFontSize(), FLT_MAX, 0.0f, item_label);
				ImVec2 text_pos = ImVec2(
					center.x + cosf((item_ang_min + item_ang_max) * 0.5f) * (RADIUS_MIN + RADIUS_MAX) * 0.5f - text_size.x * 0.5f,
					center.y + sinf((item_ang_min + item_ang_max) * 0.5f) * (RADIUS_MIN + RADIUS_MAX) * 0.5f - text_size.y * 0.5f);
				draw_list->AddText(text_pos, ImColor(255, 255, 255), item_label);

				if (hovered)
					item_hovered = item_n;
			}
			draw_list->PopClipRect();

			if (ImGui::IsMouseReleased(0))
			{
				ImGui::CloseCurrentPopup();
				ret = item_hovered;
				if (p_selected)
					*p_selected = item_hovered;
			}
			ImGui::EndPopup();
		}
		ImGui::PopStyleColor(2);
		return ret;
	}
}

#endif //IMGUI_USER_INL_
