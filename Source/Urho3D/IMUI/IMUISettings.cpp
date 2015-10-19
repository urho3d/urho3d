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

#include "IMUISettings.h"
#include "../IO/FileSystem.h"

namespace Urho3D
{

	void SetImVec2(ImVec2& dest ,const Vector2 & src)
	{
		dest.x = src.x_;
		dest.y = src.y_;
	}

	IMUISettings::IMUISettings():
	 mIniSavingRate(5.0f),            
	 mIniFilename("imgui.ini"),              
	 mLogFilename("imgui_log.txt"),             
	 mMouseDoubleClickTime(0.30f),    
	 mMouseDoubleClickMaxDist(6.0f),  
	 mMouseDragThreshold(6.0f),       
	 mKeyRepeatDelay(0.250f),          
	 mKeyRepeatRate(0.020f),            

	 mFontGlobalScale(1.0f),         
	 mFontAllowUserScaling(false),    
	 mDisplayFramebufferScale(1.0f,1.0f) , 
	 mDisplayVisibleMin(0.0f, 0.0f),       
	 mDisplayVisibleMax(0.0f, 0.0f)     
	{
		
	}

	IMUISettings& IMUISettings::IniSavingRate(float value)
	{
		mIniSavingRate = value;
		return *this;
	}

	IMUISettings& IMUISettings::IniFilename(const String& value)
	{
		mIniFilename = value;
		return *this;
	}

	IMUISettings& IMUISettings::LogFilename(const String& value)
	{
		mLogFilename = value;
		return *this;
	}

	IMUISettings& IMUISettings::MouseDoubleClickTime(float value)
	{
		mMouseDoubleClickTime = value;
		return *this;
	}

	IMUISettings& IMUISettings::MouseDoubleClickMaxDist(float value)
	{
		mMouseDoubleClickMaxDist = value;
		return *this;
	}

	IMUISettings& IMUISettings::MouseDragThreshold(float value)
	{
		mMouseDragThreshold = value;
		return *this;
	}

	IMUISettings& IMUISettings::KeyRepeatDelay(float value)
	{
		mKeyRepeatDelay = value;
		return *this;
	}

	IMUISettings& IMUISettings::KeyRepeatRate(float value)
	{
		mKeyRepeatRate = value;
		return *this;
	}

	IMUISettings& IMUISettings::FontGlobalScale(float value)
	{
		mFontGlobalScale = value;
		return *this;
	}

	IMUISettings& IMUISettings::FontAllowUserScaling(bool value)
	{
		mFontAllowUserScaling = value;
		return *this;
	}

	IMUISettings& IMUISettings::DisplayFramebufferScale(const Vector2& value)
	{
		mDisplayFramebufferScale.x = value.x_;
		mDisplayFramebufferScale.y = value.y_;
		return *this;
	}

	IMUISettings& IMUISettings::DisplayVisibleMin(const Vector2& value)
	{
		mDisplayVisibleMin.x = value.x_;
		mDisplayVisibleMin.y = value.y_;
		return *this;
	}

	IMUISettings& IMUISettings::DisplayVisibleMax(const Vector2& value)
	{
		mDisplayVisibleMax.x = value.x_;
		mDisplayVisibleMax.y = value.y_;
		return *this;
	}

	IMUISettings& IMUISettings::font(const String& fontPath, float size , bool MergeMode)
	{
		String name = GetFileName(fontPath);

		FontConfig& fconfig = mFonts[name];
		fconfig.filename_ = fontPath;
		fconfig.size_ = size;
		fconfig.config_.MergeMode = MergeMode;
		return *this;
	}

	IMUISettings& IMUISettings::fontConfig(const String& name, bool PixelSnapH, bool MergeMode, bool MergeGlyphCenterV, int OversampleH, int OversampleV)
	{
		FontConfig& fconfig = mFonts[name];
		fconfig.config_.PixelSnapH = PixelSnapH;
		fconfig.config_.MergeMode = MergeMode;
		fconfig.config_.MergeGlyphCenterV = MergeGlyphCenterV;
		fconfig.config_.OversampleH = OversampleH;
		fconfig.config_.OversampleV = OversampleV;
		return *this;
	}

	IMUISettings& IMUISettings::fontGlyphRanges(const String &name, const Vector<ImWchar> &glyphRanges)
	{
		FontConfig& fconfig = mFonts[name];
		fconfig.glyphRanges_ = glyphRanges;
		return *this;
	}
	IMUISettings& IMUISettings::alpha(float a)
	{
		mStyle.Alpha = a;
		return *this;
	}
	IMUISettings& IMUISettings::windowPadding(const Vector2 &padding)
	{
		SetImVec2(mStyle.WindowPadding, padding);
		return *this;
	}
	IMUISettings& IMUISettings::windowMinSize(const Vector2 &minSize)
	{
		SetImVec2(mStyle.WindowMinSize , minSize);
		return *this;
	}
	IMUISettings& IMUISettings::windowRounding(float rounding)
	{
		mStyle.WindowRounding = rounding;
		return *this;
	}
	IMUISettings& IMUISettings::windowTitleAlign(ImGuiAlign align)
	{
		mStyle.WindowTitleAlign = align;
		return *this;
	}
	IMUISettings& IMUISettings::childWindowRounding(float rounding)
	{
		mStyle.ChildWindowRounding = rounding;
		return *this;
	}

	IMUISettings& IMUISettings::framePadding(const Vector2 &padding)
	{
		SetImVec2(mStyle.FramePadding , padding);
		return *this;
	}
	IMUISettings& IMUISettings::frameRounding(float rounding)
	{
		mStyle.FrameRounding = rounding;
		return *this;
	}
	IMUISettings& IMUISettings::itemSpacing(const Vector2 &spacing)
	{
		SetImVec2(mStyle.ItemSpacing , spacing);
		return *this;
	}
	IMUISettings& IMUISettings::itemInnerSpacing(const Vector2 &spacing)
	{
		SetImVec2(mStyle.ItemInnerSpacing , spacing);
		return *this;
	}
	IMUISettings& IMUISettings::touchExtraPadding(const Vector2 &padding)
	{
		SetImVec2(mStyle.TouchExtraPadding, padding);
		return *this;
	}
	IMUISettings& IMUISettings::windowFillAlphaDefault(float defaultAlpha)
	{
		mStyle.WindowFillAlphaDefault = defaultAlpha;
		return *this;
	}
	IMUISettings& IMUISettings::indentSpacing(float spacing)
	{
		mStyle.IndentSpacing = spacing;
		return *this;
	}
	IMUISettings& IMUISettings::columnsMinSpacing(float minSpacing)
	{
		mStyle.ColumnsMinSpacing = minSpacing;
		return *this;
	}
	IMUISettings& IMUISettings::scrollBarSize(float size)
	{
		mStyle.ScrollbarSize = size;
		return *this;
	}
	IMUISettings& IMUISettings::scrollbarRounding(float rounding)
	{
		mStyle.ScrollbarRounding = rounding;
		return *this;
	}
	IMUISettings& IMUISettings::grabMinSize(float minSize)
	{
		mStyle.GrabMinSize = minSize;
		return *this;
	}
	IMUISettings& IMUISettings::grabRounding(float rounding)
	{
		mStyle.GrabRounding = rounding;
		return *this;
	}
	IMUISettings& IMUISettings::displayWindowPadding(const Vector2 &padding)
	{
		SetImVec2(mStyle.DisplayWindowPadding , padding);
		return *this;
	}
	IMUISettings& IMUISettings::displaySafeAreaPadding(const Vector2 &padding)
	{
		SetImVec2(mStyle.DisplaySafeAreaPadding , padding);
		return *this;
	}
	IMUISettings& IMUISettings::antiAliasedLines(bool antiAliasing)
	{
		mStyle.AntiAliasedLines = antiAliasing;
		return *this;
	}
	IMUISettings& IMUISettings::antiAliasedShapes(bool antiAliasing)
	{
		mStyle.AntiAliasedShapes = antiAliasing;
		return *this;
	}
	IMUISettings& IMUISettings::curveTessellationTol(float tessTolerance)
	{
		mStyle.CurveTessellationTol = tessTolerance;
		return *this;
	}

	IMUISettings& IMUISettings::defaultTheme()
	{
		mStyle = ImGuiStyle();
		return *this;
	}

	IMUISettings& IMUISettings::darkTheme()
	{
		mStyle.WindowMinSize = ImVec2(160, 20);
		mStyle.FramePadding = ImVec2(4, 2);
		mStyle.ItemSpacing = ImVec2(6, 2);
		mStyle.ItemInnerSpacing = ImVec2(6, 4);
		mStyle.Alpha = 0.95f;
		mStyle.WindowFillAlphaDefault = 1.0f;
		mStyle.WindowRounding = 4.0f;
		mStyle.FrameRounding = 2.0f;
		mStyle.IndentSpacing = 6.0f;
		mStyle.ItemInnerSpacing = ImVec2(2, 4);
		mStyle.ColumnsMinSpacing = 50.0f;
		mStyle.GrabMinSize = 14.0f;
		mStyle.GrabRounding = 16.0f;
		mStyle.ScrollbarSize = 12.0f;
		mStyle.ScrollbarRounding = 16.0f;

		ImGuiStyle& style = mStyle;
		style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.61f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.58f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.21f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.47f, 0.77f, 0.83f, 0.32f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.86f, 0.93f, 0.89f, 0.16f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.86f, 0.93f, 0.89f, 0.39f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
		style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.47f, 0.77f, 0.83f, 0.72f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);

		return *this;
	}


	IMUISettings& IMUISettings::color(ImGuiCol option, const Color &color)
	{
		mStyle.Colors[option].x = color.r_;
		mStyle.Colors[option].y = color.g_;
		mStyle.Colors[option].z = color.b_;
		mStyle.Colors[option].w = color.a_;
		return *this;
	}

}
