//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "APITemplates.h"
#include "CheckBox.h"
#include "Cursor.h"
#include "DropDownList.h"
#include "FileSelector.h"
#include "Font.h"
#include "LineEdit.h"
#include "ListView.h"
#include "ScrollBar.h"
#include "Slider.h"
#include "Text.h"
#include "UI.h"
#include "Window.h"

static void RegisterFont(asIScriptEngine* engine)
{
    RegisterResource<Font>(engine, "Font");
}

static void RegisterUIElement(asIScriptEngine* engine)
{
    engine->RegisterEnum("HorizontalAlignment");
    engine->RegisterEnumValue("HorizontalAlignment", "HA_LEFT", HA_LEFT);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_CENTER", HA_CENTER);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_RIGHT", HA_RIGHT);
    
    engine->RegisterEnum("VerticalAlignment");
    engine->RegisterEnumValue("VerticalAlignment", "VA_TOP", VA_TOP);
    engine->RegisterEnumValue("VerticalAlignment", "VA_CENTER", VA_CENTER);
    engine->RegisterEnumValue("VerticalAlignment", "VA_BOTTOM", VA_BOTTOM);
    
    engine->RegisterEnum("Corner");
    engine->RegisterEnumValue("Corner", "C_TOPLEFT", C_TOPLEFT);
    engine->RegisterEnumValue("Corner", "C_TOPRIGHT", C_TOPRIGHT);
    engine->RegisterEnumValue("Corner", "C_BOTTOMLEFT", C_BOTTOMLEFT);
    engine->RegisterEnumValue("Corner", "C_BOTTOMRIGHT", C_BOTTOMRIGHT);
    
    engine->RegisterEnum("Orientation");
    engine->RegisterEnumValue("Orientation", "O_HORIZONTAL", O_HORIZONTAL);
    engine->RegisterEnumValue("Orientation", "O_VERTICAL", O_VERTICAL);
    
    engine->RegisterEnum("FocusMode");
    engine->RegisterEnumValue("FocusMode", "FM_NOTFOCUSABLE", FM_NOTFOCUSABLE);
    engine->RegisterEnumValue("FocusMode", "FM_RESETFOCUS", FM_RESETFOCUS);
    engine->RegisterEnumValue("FocusMode", "FM_FOCUSABLE", FM_FOCUSABLE);
    engine->RegisterEnumValue("FocusMode", "FM_FOCUSABLE_DEFOCUSABLE", FM_FOCUSABLE_DEFOCUSABLE);
    
    engine->RegisterEnum("LayoutMode");
    engine->RegisterEnumValue("LayoutMode", "LM_FREE", LM_FREE);
    engine->RegisterEnumValue("LayoutMode", "LM_HORIZONTAL", LM_HORIZONTAL);
    engine->RegisterEnumValue("LayoutMode", "LM_VERTICAL", LM_VERTICAL);
    
    engine->RegisterGlobalProperty("const uint DD_DISABLED", (void*)&DD_DISABLED);
    engine->RegisterGlobalProperty("const uint DD_SOURCE", (void*)&DD_SOURCE);
    engine->RegisterGlobalProperty("const uint DD_TARGET", (void*)&DD_TARGET);
    engine->RegisterGlobalProperty("const uint DD_SOURCE_AND_TARGET", (void*)&DD_SOURCE_AND_TARGET);
    
    RegisterUIElement<UIElement>(engine, "UIElement");
    
    // Register Variant GetPtr() for UIElement
    engine->RegisterObjectMethod("Variant", "UIElement@+ GetUIElement() const", asFUNCTION(GetVariantPtr<UIElement>), asCALL_CDECL_OBJLAST);
}

static void RegisterBorderImage(asIScriptEngine* engine)
{
    RegisterBorderImage<BorderImage>(engine, "BorderImage");
}

static void RegisterCursor(asIScriptEngine* engine)
{
    engine->RegisterEnum("CursorShape");
    engine->RegisterEnumValue("CursorShape", "CS_NORMAL", CS_NORMAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEVERTICAL", CS_RESIZEVERTICAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPRIGHT", CS_RESIZEDIAGONAL_TOPRIGHT);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEHORIZONTAL", CS_RESIZEHORIZONTAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPLEFT", CS_RESIZEDIAGONAL_TOPLEFT);
    engine->RegisterEnumValue("CursorShape", "CS_ACCEPTDROP", CS_ACCEPTDROP);
    engine->RegisterEnumValue("CursorShape", "CS_REJECTDROP", CS_REJECTDROP);
    
    RegisterBorderImage<Cursor>(engine, "Cursor");
    engine->RegisterObjectMethod("Cursor", "void DefineShape(CursorShape, Texture@+, const IntRect&in, const IntVector2&in)", asMETHOD(Cursor, DefineShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_shape(CursorShape)", asMETHOD(Cursor, SetShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "CursorShape get_shape() const", asMETHOD(Cursor, GetShape), asCALL_THISCALL);
}

static void RegisterButton(asIScriptEngine* engine)
{
    RegisterButton<Button>(engine, "Button");
}

static void RegisterCheckBox(asIScriptEngine* engine)
{
    RegisterBorderImage<CheckBox>(engine, "CheckBox");
    engine->RegisterObjectMethod("CheckBox", "void SetCheckedOffset(int, int)", asMETHODPR(CheckBox, SetCheckedOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_checked(bool)", asMETHOD(CheckBox, SetChecked), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_checked() const", asMETHOD(CheckBox, IsChecked), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_checkedOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetCheckedOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_checkedOffset() const", asMETHOD(CheckBox, GetCheckedOffset), asCALL_THISCALL);
}

static void RegisterSlider(asIScriptEngine* engine)
{
    RegisterBorderImage<Slider>(engine, "Slider");
    engine->RegisterObjectMethod("Slider", "void ChangeValue(float)", asMETHOD(Slider, ChangeValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_orientation(Orientation)", asMETHOD(Slider, SetOrientation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "Orientation get_orientation() const", asMETHOD(Slider, GetOrientation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_range(float)", asMETHOD(Slider, SetRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_range() const", asMETHOD(Slider, GetRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "void set_value(float)", asMETHOD(Slider, SetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_value() const", asMETHOD(Slider, GetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "BorderImage@+ get_knob() const", asMETHOD(Slider, GetKnob), asCALL_THISCALL);
}

static void RegisterScrollBar(asIScriptEngine* engine)
{
    RegisterUIElement<ScrollBar>(engine, "ScrollBar");
    engine->RegisterObjectMethod("ScrollBar", "void ChangeValue(float)", asMETHOD(ScrollBar, ChangeValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void StepBack()", asMETHOD(ScrollBar, StepBack), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void StepForward()", asMETHOD(ScrollBar, StepForward), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_orientation(Orientation)", asMETHOD(ScrollBar, SetOrientation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Orientation get_orientation() const", asMETHOD(ScrollBar, GetOrientation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_range(float)", asMETHOD(ScrollBar, SetRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_range() const", asMETHOD(ScrollBar, GetRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_value(float)", asMETHOD(ScrollBar, SetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_value() const", asMETHOD(ScrollBar, GetValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_scrollStep(float)", asMETHOD(ScrollBar, SetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_scrollStep() const", asMETHOD(ScrollBar, GetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "void set_stepFactor(bool)", asMETHOD(ScrollBar, SetStepFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_stepFactor() const", asMETHOD(ScrollBar, GetStepFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "float get_effectiveScrollStep() const", asMETHOD(ScrollBar, GetEffectiveScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Button@+ get_backButton() const", asMETHOD(ScrollBar, GetBackButton), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Button@+ get_forwardButton() const", asMETHOD(ScrollBar, GetForwardButton), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollBar", "Slider@+ get_slider() const", asMETHOD(ScrollBar, GetSlider), asCALL_THISCALL);
}

static void RegisterScrollView(asIScriptEngine* engine)
{
    RegisterUIElement<ScrollView>(engine, "ScrollView");
    engine->RegisterObjectMethod("ScrollView", "void SetViewPosition(int, int)", asMETHODPR(ScrollView, SetViewPosition, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void SetScrollBarsVisible(bool, bool)", asMETHOD(ScrollView, SetScrollBarsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_contentElement(UIElement@+)", asMETHOD(ScrollView, SetContentElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "UIElement@+ get_contentElement() const", asMETHOD(ScrollView, GetContentElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_viewPosition(const IntVector2&in)", asMETHODPR(ScrollView, SetViewPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "const IntVector2& get_viewPosition() const", asMETHOD(ScrollView, GetViewPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollStep(float)", asMETHOD(ScrollView, SetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollStep() const", asMETHOD(ScrollView, GetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_pageStep(float)", asMETHOD(ScrollView, SetPageStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_pageStep() const", asMETHOD(ScrollView, GetPageStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ get_horizontalScrollBar() const", asMETHOD(ScrollView, GetHorizontalScrollBar), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "ScrollBar@+ get_verticalScrollBar() const", asMETHOD(ScrollView, GetVerticalScrollBar), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "BorderImage@+ get_scrollPanel() const", asMETHOD(ScrollView, GetScrollPanel), asCALL_THISCALL);
}

void ListViewSetSelections(CScriptArray* selections, ListView* ptr)
{
    unsigned numItems = selections->GetSize();
    PODVector<unsigned> dest;
    
    for (unsigned i = 0; i < numItems; ++i)
        dest.Push(*((unsigned*)selections->At(i)));
    
    ptr->SetSelections(dest);
}

static CScriptArray* ListViewGetSelections(ListView* ptr)
{
    return VectorToArray<unsigned>(ptr->GetSelections(), "Array<uint>");
}

static CScriptArray* ListViewGetItems(ListView* ptr)
{
    PODVector<UIElement*> result = ptr->GetItems();
    return VectorToHandleArray<UIElement>(result, "Array<UIElement@>");
}

static CScriptArray* ListViewGetSelectedItems(ListView* ptr)
{
    PODVector<UIElement*> result = ptr->GetSelectedItems();
    return VectorToHandleArray<UIElement>(result, "Array<UIElement@>");
}

static void RegisterListView(asIScriptEngine* engine)
{
    engine->RegisterEnum("HighlightMode");
    engine->RegisterEnumValue("HighlightMode", "HM_NEVER", HM_NEVER);
    engine->RegisterEnumValue("HighlightMode", "HM_FOCUS", HM_FOCUS);
    engine->RegisterEnumValue("HighlightMode", "HM_ALWAYS", HM_ALWAYS);
    
    RegisterUIElement<ListView>(engine, "ListView");
    engine->RegisterObjectMethod("ListView", "void SetViewPosition(int, int)", asMETHODPR(ListView, SetViewPosition, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void SetScrollBarsVisible(bool, bool)", asMETHOD(ListView, SetScrollBarsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void AddItem(UIElement@+)", asMETHOD(ListView, AddItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void InsertItem(uint, UIElement@+)", asMETHOD(ListView, InsertItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveItem(UIElement@+)", asMETHODPR(ListView, RemoveItem, (UIElement*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveItem(uint)", asMETHODPR(ListView, RemoveItem, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveAllItems()", asMETHOD(ListView, RemoveAllItems), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void AddSelection(uint)", asMETHOD(ListView, AddSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveSelection(uint)", asMETHOD(ListView, RemoveSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void ToggleSelection(uint)", asMETHOD(ListView, ToggleSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void ChangeSelection(int, bool)", asMETHOD(ListView, ChangeSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void SetSelections(Array<uint>@+)", asFUNCTION(ListViewSetSelections), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ListView", "void ClearSelection()", asMETHOD(ListView, ClearSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void SetChildItemsVisible(uint, bool)", asMETHODPR(ListView, SetChildItemsVisible, (unsigned, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void SetChildItemsVisible(bool)", asMETHODPR(ListView, SetChildItemsVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void ToggleChildItemsVisible(uint)", asMETHOD(ListView, ToggleChildItemsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool IsSelected(uint) const", asMETHOD(ListView, IsSelected), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetItems() const", asFUNCTION(ListViewGetItems), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ListView", "void set_viewPosition(const IntVector2&in)", asMETHODPR(ListView, SetViewPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_viewPosition() const", asMETHOD(ListView, GetViewPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_contentElement() const", asMETHOD(ListView, GetContentElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_horizontalScrollBar() const", asMETHOD(ListView, GetHorizontalScrollBar), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_verticalScrollBar() const", asMETHOD(ListView, GetVerticalScrollBar), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "BorderImage@+ get_scrollPanel() const", asMETHOD(ListView, GetScrollPanel), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollStep(float)", asMETHOD(ListView, SetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollStep() const", asMETHOD(ListView, GetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_pageStep(float)", asMETHOD(ListView, SetPageStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_pageStep() const", asMETHOD(ListView, GetPageStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_numItems() const", asMETHOD(ListView, GetNumItems), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_items(uint) const", asMETHOD(ListView, GetItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selection(uint)", asMETHOD(ListView, SetSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_selection() const", asMETHOD(ListView, GetSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Array<uint>@ get_selections() const", asFUNCTION(ListViewGetSelections), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_selectedItem() const", asMETHOD(ListView, GetSelectedItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ get_selectedItems() const", asFUNCTION(ListViewGetSelectedItems), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ListView", "void set_highlightMode(HighlightMode)", asMETHOD(ListView, SetHighlightMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "HighlightMode get_highlightMode() const", asMETHOD(ListView, GetHighlightMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_multiselect(bool)", asMETHOD(ListView, SetMultiselect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_multiselect() const", asMETHOD(ListView, GetMultiselect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_hierarchyMode(bool)", asMETHOD(ListView, SetHierarchyMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_hierarchyMode() const", asMETHOD(ListView, GetHierarchyMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clearSelectionOnDefocus(bool)", asMETHOD(ListView, SetClearSelectionOnDefocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_clearSelectionOnDefocus() const", asMETHOD(ListView, GetClearSelectionOnDefocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_doubleClickInterval(float)", asMETHOD(ListView, SetDoubleClickInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_doubleClickInterval() const", asMETHOD(ListView, GetDoubleClickInterval), asCALL_THISCALL);
}

static void RegisterText(asIScriptEngine* engine)
{
    RegisterUIElement<Text>(engine, "Text");
    engine->RegisterObjectMethod("Text", "bool SetFont(const String&in, int)", asMETHODPR(Text, SetFont, (const String&, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool SetFont(Font@+, int)", asMETHODPR(Text, SetFont, (Font*, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void SetSelection(uint, uint)", asMETHOD(Text, SetSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void ClearSelection()", asMETHOD(Text, ClearSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Font@+ get_font() const", asMETHOD(Text, GetFont), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_fontSize() const", asMETHOD(Text, GetFontSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_maxWidth() const", asMETHOD(Text, GetMaxWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_text(const String&in)", asMETHOD(Text, SetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_text() const", asMETHOD(Text, GetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_textAlignment(HorizontalAlignment)", asMETHOD(Text, SetTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "HorizontalAlignment get_textAlignment() const", asMETHOD(Text, GetTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_rowSpacing(float)", asMETHOD(Text, SetRowSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowSpacing() const", asMETHOD(Text, GetRowSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_wordwrap(bool)", asMETHOD(Text, SetWordwrap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_wordwrap() const", asMETHOD(Text, GetWordwrap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionStart() const", asMETHOD(Text, GetSelectionStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionLength() const", asMETHOD(Text, GetSelectionLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_selectionColor(const Color&in)", asMETHOD(Text, SetSelectionColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_selectionColor() const", asMETHOD(Text, GetSelectionColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_hoverColor(const Color&in)", asMETHOD(Text, SetHoverColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_hoverColor() const", asMETHOD(Text, GetHoverColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numRows() const", asMETHOD(Text, GetNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_rowHeight() const", asMETHOD(Text, GetRowHeight), asCALL_THISCALL);
}

static void RegisterLineEdit(asIScriptEngine* engine)
{
    RegisterBorderImage<LineEdit>(engine, "LineEdit");
    engine->RegisterObjectMethod("LineEdit", "void set_text(const String&in)", asMETHOD(LineEdit, SetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_text() const", asMETHOD(LineEdit, GetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorPosition(uint)", asMETHOD(LineEdit, SetCursorPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_cursorPosition() const", asMETHOD(LineEdit, GetCursorPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorBlinkRate(float)", asMETHOD(LineEdit, SetCursorBlinkRate), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "float get_cursorBlinkRate() const", asMETHOD(LineEdit, GetCursorBlinkRate), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxLength(uint)", asMETHOD(LineEdit, SetMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_maxLength() const", asMETHOD(LineEdit, GetMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_echoCharacter(uint8)", asMETHOD(LineEdit, SetEchoCharacter), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint8 get_echoCharacter() const", asMETHOD(LineEdit, GetEchoCharacter), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorMovable(bool)", asMETHOD(LineEdit, SetCursorMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_cursorMovable() const", asMETHOD(LineEdit, IsCursorMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_textSelectable(bool)", asMETHOD(LineEdit, SetTextSelectable), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_textSelectable() const", asMETHOD(LineEdit, IsTextSelectable), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_textCopyable(bool)", asMETHOD(LineEdit, SetTextCopyable), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_textCopyable() const", asMETHOD(LineEdit, IsTextCopyable), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Text@+ get_textElement() const", asMETHOD(LineEdit, GetTextElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "BorderImage@+ get_cursor() const", asMETHOD(LineEdit, GetCursor), asCALL_THISCALL);
}

static void RegisterMenu(asIScriptEngine* engine)
{
    RegisterButton<Menu>(engine, "Menu");
    engine->RegisterObjectMethod("Menu", "void SetPopupOffset(int, int)", asMETHODPR(Menu, SetPopupOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void SetAccelerator(int, int)", asMETHOD(Menu, SetAccelerator), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_popup(UIElement@+)", asMETHOD(Menu, SetPopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "UIElement@+ get_popup() const", asMETHOD(Menu, GetPopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_popupOffset(const IntVector2&in)", asMETHODPR(Menu, SetPopupOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "const IntVector2& get_popupOffset() const", asMETHOD(Menu, GetPopupOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "void set_showPopup(bool)", asMETHOD(Menu, ShowPopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "bool get_showPopup() const", asMETHOD(Menu, GetShowPopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_acceleratorKey() const", asMETHOD(Menu, GetAcceleratorKey), asCALL_THISCALL);
    engine->RegisterObjectMethod("Menu", "int get_acceleratorQualifiers() const", asMETHOD(Menu, GetAcceleratorQualifiers), asCALL_THISCALL);
}

static CScriptArray* DropDownListGetItems(DropDownList* ptr)
{
    PODVector<UIElement*> result = ptr->GetItems();
    return VectorToHandleArray<UIElement>(result, "Array<UIElement@>");
}

static void RegisterDropDownList(asIScriptEngine* engine)
{
    RegisterButton<DropDownList>(engine, "DropDownList");
    engine->RegisterObjectMethod("DropDownList", "void SetAccelerator(int, int)", asMETHOD(DropDownList, SetAccelerator), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void AddItem(UIElement@+)", asMETHOD(DropDownList, AddItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void InsertItem(uint, UIElement@+)", asMETHOD(DropDownList, InsertItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void RemoveItem(UIElement@+)", asMETHODPR(DropDownList, RemoveItem, (UIElement*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void RemoveItem(uint)", asMETHODPR(DropDownList, RemoveItem, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void RemoveAllItems()", asMETHOD(DropDownList, RemoveAllItems), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetItems() const", asFUNCTION(DropDownListGetItems), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("DropDownList", "void set_showPopup(bool)", asMETHOD(DropDownList, ShowPopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_showPopup() const", asMETHOD(DropDownList, GetShowPopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_selection(uint)", asMETHOD(DropDownList, SetSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_selection() const", asMETHOD(DropDownList, GetSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_resizePopup(bool)", asMETHOD(DropDownList, SetResizePopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_resizePopup() const", asMETHOD(DropDownList, GetResizePopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ getPopup() const", asMETHOD(DropDownList, GetPopup), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_acceleratorKey() const", asMETHOD(DropDownList, GetAcceleratorKey), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_acceleratorQualifiers() const", asMETHOD(DropDownList, GetAcceleratorQualifiers), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_numItems() const", asMETHOD(DropDownList, GetNumItems), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_items(uint) const", asMETHOD(DropDownList, GetItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_selectedItem() const", asMETHOD(DropDownList, GetSelectedItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "ListView@+ get_listView() const", asMETHOD(DropDownList, GetListView), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_placeholder() const", asMETHOD(DropDownList, GetPlaceholder), asCALL_THISCALL);
}

static void RegisterWindow(asIScriptEngine* engine)
{
    RegisterBorderImage<Window>(engine, "Window");
    engine->RegisterObjectMethod("Window", "void set_movable(bool)", asMETHOD(Window, SetMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_movable() const", asMETHOD(Window, IsMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_resizable(bool)", asMETHOD(Window, SetResizable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_resizable() const", asMETHOD(Window, IsResizable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_resizeBorder(const IntRect&in)", asMETHODPR(Window, SetResizeBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_resizeBorder() const", asMETHOD(Window, GetResizeBorder), asCALL_THISCALL);
}

static void FileSelectorSetFilters(CScriptArray* filters, unsigned defaultIndex, FileSelector* ptr)
{
    if (!filters)
        return;
    
    unsigned numFilters = filters->GetSize();
    Vector<String> destFilters(numFilters);
    
    for (unsigned i = 0; i < numFilters; ++i)
        destFilters[i] = *(static_cast<String*>(filters->At(i)));
    
    ptr->SetFilters(destFilters, defaultIndex);
}

static void RegisterFileSelector(asIScriptEngine* engine)
{
    RegisterObject<FileSelector>(engine, "FileSelector");
    RegisterObjectConstructor<FileSelector>(engine, "FileSelector");
    engine->RegisterObjectMethod("FileSelector", "void SetButtonTexts(const String&in, const String&in)", asMETHOD(FileSelector, SetButtonTexts), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void SetFilters(Array<String>@+, uint)", asFUNCTION(FileSelectorSetFilters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("FileSelector", "void UpdateElements()", asMETHOD(FileSelector, UpdateElements), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_title(const String&in)", asMETHOD(FileSelector, SetTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_title() const", asMETHOD(FileSelector, GetTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_path(const String&in)", asMETHOD(FileSelector, SetPath), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_path() const", asMETHOD(FileSelector, GetPath), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_fileName(const String&in)", asMETHOD(FileSelector, SetFileName), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_fileName() const", asMETHOD(FileSelector, GetFileName), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_directoryMode(bool)", asMETHOD(FileSelector, SetDirectoryMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "bool get_directoryMode() const", asMETHOD(FileSelector, GetDirectoryMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "const String& get_filter() const", asMETHOD(FileSelector, GetFilter), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "uint get_filterIndex() const", asMETHOD(FileSelector, GetFilterIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "void set_style(XMLFile@+)", asMETHOD(FileSelector, SetStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "XMLFile@+ get_style() const", asMETHOD(FileSelector, GetStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Window@+ get_window() const", asMETHOD(FileSelector, GetWindow), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Text@+ get_titleText() const", asMETHOD(FileSelector, GetTitleText), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "ListView@+ get_fileList() const", asMETHOD(FileSelector, GetFileList), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_pathEdit() const", asMETHOD(FileSelector, GetPathEdit), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_fileNameEdit() const", asMETHOD(FileSelector, GetFileNameEdit), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "DropDownList@+ get_filterList() const", asMETHOD(FileSelector, GetFilterList), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_okButton() const", asMETHOD(FileSelector, GetOKButton), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_cancelButton() const", asMETHOD(FileSelector, GetCancelButton), asCALL_THISCALL);
}

static UI* GetUI()
{
    return GetScriptContext()->GetSubsystem<UI>();
}

static UIElement* UILoadLayout(XMLFile* file, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(file);
    if (root)
        root->AddRef();
    return root.Get();
}

static UIElement* UILoadLayoutWithStyle(XMLFile* file, XMLFile* styleFile, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(file, styleFile);
    if (root)
        root->AddRef();
    return root.Get();
}

static void RegisterUI(asIScriptEngine* engine)
{
    RegisterObject<UI>(engine, "UI");
    engine->RegisterObjectMethod("UI", "void Clear()", asMETHOD(UI, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(XMLFile@+)", asFUNCTION(UILoadLayout), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(XMLFile@+, XMLFile@+)", asFUNCTION(UILoadLayoutWithStyle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(const IntVector2&in, bool activeOnly = true)", asMETHODPR(UI, GetElementAt, (const IntVector2&, bool), UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(int, int, bool activeOnly = true)", asMETHODPR(UI, GetElementAt, (int, int, bool), UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_cursor(Cursor@+)", asMETHOD(UI, SetCursor), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "Cursor@+ get_cursor() const", asMETHOD(UI, GetCursor), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "IntVector2 get_cursorPosition()", asMETHOD(UI, GetCursorPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_focusElement(UIElement@+)", asMETHOD(UI, SetFocusElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_focusElement() const", asMETHOD(UI, GetFocusElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_frontElement() const", asMETHOD(UI, GetFrontElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_root() const", asMETHOD(UI, GetRoot), asCALL_THISCALL);
    engine->RegisterGlobalFunction("UI@+ get_ui()", asFUNCTION(GetUI), asCALL_CDECL);
}

void RegisterUIAPI(asIScriptEngine* engine)
{
    RegisterFont(engine);
    RegisterUIElement(engine);
    RegisterBorderImage(engine);
    RegisterButton(engine);
    RegisterCheckBox(engine);
    RegisterCursor(engine);
    RegisterSlider(engine);
    RegisterScrollBar(engine);
    RegisterScrollView(engine);
    RegisterListView(engine);
    RegisterText(engine);
    RegisterLineEdit(engine);
    RegisterMenu(engine);
    RegisterDropDownList(engine);
    RegisterWindow(engine);
    RegisterFileSelector(engine);
    RegisterUI(engine);
}
