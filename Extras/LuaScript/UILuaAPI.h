//
// Copyright (c) 2008-2013 the Urho3D project.
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

#pragma once

#include "BorderImage.h"
#include "Button.h"
#include "CheckBox.h"
#include "Context.h"
#include "Cursor.h"
#include "DropDownList.h"
#include "FileSelector.h"
#include "Font.h"
#include "LineEdit.h"
#include "ListView.h"
#include "LuaScript.h"
#include "Menu.h"
#include "ScrollBar.h"
#include "ScrollView.h"
#include "Slider.h"
#include "Sprite.h"
#include "Text.h"
#include "Text3D.h"
#include "UI.h"
#include "UIElement.h"
#include "Window.h"


namespace Urho3D
{
    BorderImage* NewBorderImage()
	{
		return new BorderImage(GetLuaScriptContext());
	}
	
	Button* NewButton()
	{
		return new Button(GetLuaScriptContext());
	}

	CheckBox* NewCheckBox()
	{
		return new CheckBox(GetLuaScriptContext());
	}
	
	Cursor* NewCursor()
	{
		return new Cursor(GetLuaScriptContext());
	}
	
	DropDownList* NewDropDownList()
	{
		return new DropDownList(GetLuaScriptContext());
	}
	
	FileSelector* NewFileSelector()
	{
		return new FileSelector(GetLuaScriptContext());
	}
	
	Font* NewFont()
	{
		return new Font(GetLuaScriptContext());
	}
	
	LineEdit* NewLineEdit()
	{
		return new LineEdit(GetLuaScriptContext());
	}
	
	ListView* NewListView()
	{
		return new ListView(GetLuaScriptContext());
	}
	
	Menu* NewMenu()
	{
		return new Menu(GetLuaScriptContext());
	}
	
	ScrollBar* NewScrollBar()
	{
		return new ScrollBar(GetLuaScriptContext());
	}
	
	ScrollView* NewScrollView()
	{
		return new ScrollView(GetLuaScriptContext());
	}
	
	Slider* NewSlider()
	{
		return new Slider(GetLuaScriptContext());
	}

	Sprite* NewSprite()
	{
		return new Sprite(GetLuaScriptContext());
	}
	
	Text* NewText()
	{
		return new Text(GetLuaScriptContext());
	}
	
	Text3D* NewText3D()
	{
		return new Text3D(GetLuaScriptContext());
	}

	UI* GetUI()
	{
		return GetLuaScriptContext()->GetSubsystem<UI>();
	}
	
	UIElement* NewUIElement()
	{
		return new UIElement(GetLuaScriptContext());
	}
	
	Window* NewWindow()
	{
		return new Window(GetLuaScriptContext());
	}
}