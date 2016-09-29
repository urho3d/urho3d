//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IMUI/IMUI.h>
#include <Urho3D/IO/Log.h>
#include "HelloIMUI.h"

#include <imgui/imgui.h>
#include <Urho3D/IMUI/IMUISettings.h>

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(HelloIMUI)

HelloIMUI::HelloIMUI(Context* context) :
    Sample(context)

{
}

void HelloIMUI::Setup()
{
	// Modify engine startup parameters
	engineParameters_["WindowTitle"] = GetTypeName();
	engineParameters_["LogName"] = GetTypeName() + ".log";
	engineParameters_["FullScreen"] = false;
	engineParameters_["Headless"] = false;
	engineParameters_["Sound"] = false;
	engineParameters_["UseIMUI"] = true; // if false does not create IMUI subsystem, default true.
	engineParameters_["IMUIConfig"] = "ImUIConfig.xml"; // location of the IMUI config xml file.
}

void HelloIMUI::Start()
{
    // Execute base class startup
    Sample::Start();

    // Enable OS cursor
	GetSubsystem<Input>()->SetMouseVisible(true);
	// test touch
	// GetSubsystem<Input>()->SetTouchEmulation(true);

	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(HelloIMUI, HandleUpdate));
	
	IMUI* imui = GetSubsystem<IMUI>();

	/// create custom imgui settings.
	IMUISettings imuisettings;
	
	imuisettings.font("Fonts/Anonymous Pro.ttf",14, false);
	imuisettings.font("Fonts/fontawesome-webfont.ttf", 14, true);

	Vector<ImWchar> iconRanges;
	iconRanges.Push(0xf000);
	iconRanges.Push(0xf3ff);
	iconRanges.Push(0);
	// Basic Latin + Latin Supplement
	Vector<ImWchar> defaultranges; 
	defaultranges.Push(0x0020);
	defaultranges.Push(0x00FF);
	defaultranges.Push(0);

	imuisettings.fontGlyphRanges("fontawesome-webfont", iconRanges);
	imuisettings.fontConfig("fontawesome-webfont", true, true, true, 1, 1);
	imuisettings.fontGlyphRanges("Anonymous Pro", defaultranges);
	imuisettings.fontConfig("Anonymous Pro", false, false, false,3, 1);

	imui->SetSettings(imuisettings);

	/// Load xml imgui style.
//	ResourceCache* cache = GetSubsystem<ResourceCache>();
//	XMLFile* xmlfile = cache->GetResource<XMLFile>("Data/ImGuiStyle.xml");
//	imui->LoadStyleXML(xmlfile->GetRoot());
}

void HelloIMUI::Stop()
{
	/// save xml imgui style.
//	IMUI* imui = GetSubsystem<IMUI>();
//	ResourceCache* cache = GetSubsystem<ResourceCache>();
//	File styleSaveFile(context_, cache->GetResourceFileName("ImGuiStyle.xml"),FILE_WRITE);
//	imui->SaveStyleXML(styleSaveFile);
}

void HelloIMUI::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
	IMUI* imui = GetSubsystem<IMUI>();
	
	// check if window "hello" is collapsed, double click on the header/title
	if (ImGui::Begin("Hello"))
	{
		// normal text
		ImGui::Text("Hello world! ...");
		// if font icons are loaded, use u8"" to place them.
		
		// ImGui::Text("\uF04B"); isn't correct it is 16-bit unicode whereas ImGui takes UTF-8.
		// so use in c++11 use u8"\uf016" or
		ImGui::Text("\xef\x80\x96" " File"); // use string literal concatenation, ouputs a file icon and File as a string
		ImGui::Button("test", ImVec2(100.0f, 20.0f));
	}
	// if Begin was called, the corresponding End must be called too !!
	ImGui::End();

	// ImGui has some tests implemented. 
	ImGui::ShowTestWindow();

	// hijack Test Window and add addons
	if (ImGui::Begin("ImGui Demo"))
	{
		/// addons from https://github.com/Flix01/imgui but not all implemented
		if(ImGui::CollapsingHeader("Addons"))
		{
			ImGui::Indent();
			if (ImGui::CollapsingHeader("Color"))
			{
				static bool colorchooser = false;
				static ImVec4 color;

				ImGui::Checkbox("Color Chooser", &colorchooser);
				ImGui::ColorChooser(&colorchooser, &color);
				ImGui::ColorCombo("Color Combo", &color);
			}

			if (ImGui::CollapsingHeader("Multiline Text"))
			{
				static char buffer[1024] = "Code posted by Roflraging to the ImGui Issue Section (https://github.com/ocornut/imgui/issues/383).";
				const float height = 60;
				ImGui::Text("InputTextMultiline with horizontal scrolling:");
				ImGui::PushID(buffer);
				ImGui::InputTextMultilineWithHorizontalScrolling("ITMWHS", buffer, 1024, height);   // Note that now the label is not displayed ATM
				ImGui::PopID();

				ImGui::Spacing();
				ImGui::Text("Same as above with a context-menu that should work (more or less):");
				static char buffer2[1024] = "Code posted by Roflraging to the ImGui Issue Section (https://github.com/ocornut/imgui/issues/383).";
				ImGui::PushID(buffer2);
				static bool popup_open = false; static int threeStaticInts[3] = { 0,0,0 };
				ImGui::InputTextMultilineWithHorizontalScrollingAndCopyCutPasteMenu("ITMWHS2", buffer2, 1024, height, popup_open, threeStaticInts);
				ImGui::PopID();
			}

			if (ImGui::CollapsingHeader("Tabs"))
			{
				// Based on the code by krys-spectralpixel (https://github.com/krys-spectralpixel), posted here: https://github.com/ocornut/imgui/issues/261			
				ImGui::Text("TabLabels (based on the code by krys-spectralpixel):");
				static const char* tabNames[] = { "Render","Layers","Scene","World","Object","Constraints","Modifiers","Data","Material","Texture","Particle","Physics" };
				static const int numTabs = sizeof(tabNames) / sizeof(tabNames[0]);
				static const char* tabTooltips[numTabs] = { "Render Tab Tooltip","This tab cannot be closed with MMB","Scene Tab Tooltip","","Object Tab Tooltip","","","","","Tired to add tooltips...","" };
				static int tabItemOrdering[numTabs] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
				static int selectedTab = 0;
				static int optionalHoveredTab = 0;
				static bool allowTabLabelDragAndDrop = true; static bool tabLabelWrapMode = true; static bool allowClosingTabsWithMMB = true;
				int justClosedTabIndex = -1, justClosedTabIndexInsideTabItemOrdering = -1, oldSelectedTab = selectedTab;

				ImGui::Checkbox("Wrap Mode##TabLabelWrapMode", &tabLabelWrapMode);
				ImGui::SameLine(); ImGui::Checkbox("Drag And Drop##TabLabelDragAndDrop", &allowTabLabelDragAndDrop);
				ImGui::SameLine(); ImGui::Checkbox("MMB closes tabs##TabLabelMMBClosing", &allowClosingTabsWithMMB);
				ImGui::SameLine(); if (ImGui::SmallButton("Reset Tabs")) { for (int i = 0; i<numTabs; i++) tabItemOrdering[i] = i; }
				//if (optionalHoveredTab>=0) ImGui::Text("Mouse is hovering Tab Label: \"%s\".\n\n",tabNames[optionalHoveredTab]);

				/*const bool tabSelectedChanged =*/ ImGui::TabLabels(numTabs, tabNames, selectedTab, tabTooltips, tabLabelWrapMode, &optionalHoveredTab, &tabItemOrdering[0], allowTabLabelDragAndDrop, allowClosingTabsWithMMB, &justClosedTabIndex, &justClosedTabIndexInsideTabItemOrdering);
				// Optional stuff
				if (justClosedTabIndex == 1) {
					tabItemOrdering[justClosedTabIndexInsideTabItemOrdering] = justClosedTabIndex;   // Prevent the user from closing Tab "Layers"
					selectedTab = oldSelectedTab;   // This is safer, in case we had closed the selected tab
				}

				// Draw tab page
				// tablabels uses ImGuiCol_Button for the tabs, use same color
				ImGui::Separator(3.0f, ImGuiCol_Button); 
				ImGui::PushID(tabNames[selectedTab]);
				ImGui::BeginChild(tabNames[selectedTab],ImVec2(0.0f,0.0f),true);
				ImGui::Text("Tab Page For Tab: \"%s\" here.", tabNames[selectedTab]);
				ImGui::EndChild();
				ImGui::PopID();
			}

			if (ImGui::CollapsingHeader("Curve Editor"))
			{
				ImGui::Text("Curve Editor (based on the code by https://github.com/nem0/LumixEngine):");
				ImVec2 editor_size;
				ImGui::CurveEditor editor = ImGui::BeginCurveEditor("Curve Editor Child");
				if (editor.valid)
				{
					editor_size = ImVec2(ImGui::CalcItemWidth(), ImGui::GetItemRectSize().y);
					static ImVec2 point1[3] = {ImVec2(0.10f, 0.0f), ImVec2(0.0f, 0.0f), ImVec2(.0f, .10f)};
					static ImVec2 point2[3] = {ImVec2(0.0f, 0.0f), ImVec2(0.0f, 0.0f), ImVec2(.0f, .10f)};
					static ImVec2 point3[3] = {ImVec2(0.0f, 0.0f), ImVec2(0.0f, 0.0f), ImVec2(.0f, .0f)};
					static ImVec2 point4[3] = {ImVec2(0.10f, 0.0f), ImVec2(0.0f, 0.0f), ImVec2(.0f, .10f)};
					if (ImGui::CurvePoint(point1, editor))
					{
					//	changed = true;
					}
					ImGui::CurvePoint(point2, editor);
					ImGui::CurvePoint(point3, editor);
					ImGui::CurvePoint(point4, editor);
					ImGui::EndCurveEditor(editor);
				}
			}

			/// https://github.com/ocornut/imgui/issues/434
			if (ImGui::CollapsingHeader("Pie Popup Menu"))
			{
				static const char* test_data = "Menu";
				const char* items[] = { "Orange", "Blue", "Purple", "Gray", "Yellow", "Las Vegas" };
				int items_count = sizeof(items) / sizeof(*items);
				static int mouse = 0;
				static int selected = -1;

				ImGui::Button(selected >= 0 ? items[selected] : "Menu", ImVec2(50, 50));

				/// usage with button/item pressed
				if (ImGui::IsItemActive())          // Don't wait for button release to activate the pie menu
				{
					mouse = 0;
					ImGui::OpenPopup("##piepopup");
				}
					
				/// usage for right mouse click and not over window (or check for specifc window ... )
				if (!ImGui::IsMouseHoveringAnyWindow() && ImGui::IsMouseClicked(1))
				{
					mouse = 1;
					ImGui::OpenPopup("##piepopup");
				}
					
				ImVec2 pie_menu_center = ImGui::GetIO().MouseClickedPos[mouse];
				ImGui::PiePopupSelectMenu(pie_menu_center, "##piepopup", items, items_count, &selected);
				
			}	
			ImGui::Unindent();
		}
	}
	ImGui::End();
}
