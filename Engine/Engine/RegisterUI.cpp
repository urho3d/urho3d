//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "Button.h"
#include "CheckBox.h"
#include "Cursor.h"
#include "Engine.h"
#include "Font.h"
#include "RegisterTemplates.h"
#include "Text.h"
#include "UI.h"
#include "Window.h"

static void registerFont(asIScriptEngine* engine)
{
    registerResource<Font>(engine, "Font");
    registerRefCasts<Resource, Font>(engine, "Resource", "Font");
}

void UIElementLoadParameters(XMLFile* file, const std::string& elementName, UIElement* ptr)
{
    try
    {
        ptr->loadParameters(file, elementName, getEngine()->getResourceCache());
    }
    catch (Exception& e)
    {
        SAFE_RETHROW(e);
    }
}

static void registerUIElement(asIScriptEngine* engine)
{
    engine->RegisterEnum("HorizontalAlignment");
    engine->RegisterEnumValue("HorizontalAlignment", "HA_LEFT", HA_LEFT);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_CENTER", HA_CENTER);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_RIGHT", HA_RIGHT);
    
    engine->RegisterEnum("VerticalAlignment");
    engine->RegisterEnumValue("VerticalAlignment", "VA_TOP", VA_TOP);
    engine->RegisterEnumValue("VerticalAlignment", "VA_CENTER", VA_CENTER);
    engine->RegisterEnumValue("VerticalAlignment", "VA_BOTTOM", VA_BOTTOM);
    
    engine->RegisterEnum("UIElementCorner");
    engine->RegisterEnumValue("UIElementCorner", "C_TOPLEFT", C_TOPLEFT);
    engine->RegisterEnumValue("UIElementCorner", "C_TOPRIGHT", C_TOPRIGHT);
    engine->RegisterEnumValue("UIElementCorner", "C_BOTTOMLEFT", C_BOTTOMLEFT);
    engine->RegisterEnumValue("UIElementCorner", "C_BOTTOMRIGHT", C_BOTTOMRIGHT);
    
    registerUIElement<UIElement>(engine, "UIElement");
    engine->RegisterObjectMethod("UIElement", "void loadParameters(XMLFile@+, const string& in)", asFUNCTION(UIElementLoadParameters), asCALL_CDECL_OBJLAST);
    
    // Register Variant getPtr() for UIElement
    engine->RegisterObjectMethod("Variant", "UIElement@+ getUIElement() const", asFUNCTION(getVariantPtr<UIElement>), asCALL_CDECL_OBJLAST);
}

static void registerText(asIScriptEngine* engine)
{
    registerUIElement<Text>(engine, "Text");
    engine->RegisterObjectMethod("Text", "void loadParameters(XMLFile@+, const string& in)", asFUNCTION(UIElementLoadParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Text", "bool setFont(Font@+, int)", asMETHOD(Text, setFont), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void setMaxWidth(int)", asMETHOD(Text, setMaxWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void setText(const string& in)", asMETHOD(Text, setText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void setTextAlignment(HorizontalAlignment)", asMETHOD(Text, setTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void setTextSpacing(float)", asMETHOD(Text, setTextSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Font@+ getFont() const", asMETHOD(Text, getFont), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int getFontSize() const", asMETHOD(Text, getFontSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int getMaxWidth() const", asMETHOD(Text, getMaxWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const string& getText() const", asMETHOD(Text, getText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "HorizontalAlignment getTextAlignment() const", asMETHOD(Text, getTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float getTextSpacing() const", asMETHOD(Text, getTextSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint getNumRows() const", asMETHOD(Text, getNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int getRowHeight() const", asMETHOD(Text, getRowHeight), asCALL_THISCALL);
    registerRefCasts<UIElement, Text>(engine, "UIElement", "Text");
}

static void registerBorderImage(asIScriptEngine* engine)
{
    registerBorderImage<BorderImage>(engine, "BorderImage");
    engine->RegisterObjectMethod("BorderImage", "void loadParameters(XMLFile@+, const string& in)", asFUNCTION(UIElementLoadParameters), asCALL_CDECL_OBJLAST);
    registerRefCasts<UIElement, BorderImage>(engine, "UIElement", "BorderImage");
}

static void registerCursor(asIScriptEngine* engine)
{
    registerBorderImage<Cursor>(engine, "Cursor");
    engine->RegisterObjectMethod("Cursor", "void loadParameters(XMLFile@+, const string& in)", asFUNCTION(UIElementLoadParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Cursor", "void setHotspot(const IntVector2& in)", asMETHODPR(Cursor, setHotspot, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void setHotspot(int, int)", asMETHODPR(Cursor, setHotspot, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const IntVector2& getHotspot() const", asMETHOD(Cursor, getHotspot), asCALL_THISCALL);
    registerRefCasts<UIElement, Cursor>(engine, "UIElement", "Cursor");
}

static void registerButton(asIScriptEngine* engine)
{
    registerBorderImage<Button>(engine, "Button");
    engine->RegisterObjectMethod("Button", "void loadParameters(XMLFile@+, const string& in)", asFUNCTION(UIElementLoadParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Button", "void setInactiveRect(const IntRect& in)", asMETHODPR(Button, setInactiveRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void setInactiveRect(int, int, int, int)", asMETHODPR(Button, setInactiveRect, (int, int, int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void setPressedRect(const IntRect& in)", asMETHODPR(Button, setPressedRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void setPressedRect(int, int, int, int)", asMETHODPR(Button, setPressedRect, (int, int, int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void setLabel(UIElement@+)", asMETHOD(Button, setLabel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void setLabelOffset(const IntVector2& in)", asMETHODPR(Button, setLabelOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void setLabelOffset(int, int)", asMETHODPR(Button, setLabelOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& getInactiveRect() const", asMETHOD(Button, getInactiveRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& getPressedRect() const", asMETHOD(Button, getPressedRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "UIElement@+ getLabel() const", asMETHOD(Button, getLabel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& getLabelOffset() const", asMETHOD(Button, getLabelOffset), asCALL_THISCALL);
    registerRefCasts<UIElement, Button>(engine, "UIElement", "Button");
}

static void registerCheckBox(asIScriptEngine* engine)
{
    registerBorderImage<CheckBox>(engine, "CheckBox");
    engine->RegisterObjectMethod("CheckBox", "void loadParameters(XMLFile@+, const string& in)", asFUNCTION(UIElementLoadParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CheckBox", "void setChecked(bool)", asMETHOD(CheckBox, setChecked), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void setUncheckedRect(const IntRect& in)", asMETHODPR(CheckBox, setUncheckedRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void setUncheckedRect(int, int, int, int)", asMETHODPR(CheckBox, setUncheckedRect, (int, int, int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void setCheckedRect(const IntRect& in)", asMETHODPR(CheckBox, setCheckedRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void setCheckedRect(int, int, int, int)", asMETHODPR(CheckBox, setCheckedRect, (int, int, int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool isChecked() const", asMETHOD(CheckBox, isChecked), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& getUncheckedRect() const", asMETHOD(CheckBox, getUncheckedRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& getCheckedRect() const", asMETHOD(CheckBox, getCheckedRect), asCALL_THISCALL);
    registerRefCasts<UIElement, CheckBox>(engine, "UIElement", "CheckBox");
}

static void registerWindow(asIScriptEngine* engine)
{
    registerBorderImage<Window>(engine, "Window");
    engine->RegisterObjectMethod("Window", "void loadParameters(XMLFile@+, const string& in)", asFUNCTION(UIElementLoadParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Window", "void setMovable(bool)", asMETHOD(Window, setMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void setResizable(bool)", asMETHOD(Window, setResizable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void setMinSize(const IntVector2& in)", asMETHODPR(Window, setMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void setMinSize(int, int)", asMETHODPR(Window, setMinSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void setMaxSize(const IntVector2& in)", asMETHODPR(Window, setMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void setMaxSize(int, int)", asMETHODPR(Window, setMaxSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void setResizeBorder(const IntRect& in)", asMETHODPR(Window, setResizeBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void setResizeBorder(int, int, int, int)", asMETHODPR(Window, setResizeBorder, (int, int, int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool isMovable() const", asMETHOD(Window, isMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool isResizable() const", asMETHOD(Window, isResizable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& getMinSize() const", asMETHOD(Window, getMinSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& getMaxSize() const", asMETHOD(Window, getMaxSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& getResizeBorder() const", asMETHOD(Window, getResizeBorder), asCALL_THISCALL);
    registerRefCasts<UIElement, Window>(engine, "UIElement", "Window");
}

static UI* GetUI()
{
    return getEngine()->getUI();
}

static UIElement* GetUIRoot()
{
    return getEngine()->getUIRoot();
}

static Cursor* GetUICursor()
{
    return getEngine()->getUICursor();
}

static void registerUI(asIScriptEngine* engine)
{
    engine->RegisterObjectType("UI", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("UI", asBEHAVE_ADDREF, "void f()", asMETHOD(UI, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("UI", asBEHAVE_RELEASE, "void f()", asMETHOD(UI, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void setCursor(Cursor@+)", asMETHOD(UI, setCursor), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void setFocusElement(UIElement@+)", asMETHOD(UI, setFocusElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void bringToFront(UIElement@+)", asMETHOD(UI, bringToFront), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ getRootElement() const", asMETHOD(UI, getRootElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "Cursor@+ getCursor() const", asMETHOD(UI, getCursor), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ getElementAt(const IntVector2& in, bool)", asMETHODPR(UI, getElementAt, (const IntVector2&, bool), UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ getElementAt(int, int, bool)", asMETHODPR(UI, getElementAt, (int, int, bool), UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ getFocusElement()", asMETHOD(UI, getFocusElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "IntVector2 getCursorPosition()", asMETHOD(UI, getCursorPosition), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("UI@+ getUI()", asFUNCTION(GetUI), asCALL_CDECL);
    engine->RegisterGlobalFunction("UI@+ get_ui()", asFUNCTION(GetUI), asCALL_CDECL);
    engine->RegisterGlobalFunction("UIElement@+ getUIRoot()", asFUNCTION(GetUIRoot), asCALL_CDECL);
    engine->RegisterGlobalFunction("UIElement@+ get_uiRoot()", asFUNCTION(GetUIRoot), asCALL_CDECL);
    engine->RegisterGlobalFunction("Cursor@+ getUICursor()", asFUNCTION(GetUICursor), asCALL_CDECL);
    engine->RegisterGlobalFunction("Cursor@+ get_uiCursor()", asFUNCTION(GetUICursor), asCALL_CDECL);
}

void registerUILibrary(asIScriptEngine* engine)
{
    registerFont(engine);
    registerUIElement(engine);
    registerText(engine);
    registerBorderImage(engine);
    registerButton(engine);
    registerCheckBox(engine);
    registerCursor(engine);
    registerWindow(engine);
    registerUI(engine);
}
