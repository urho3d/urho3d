//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../Input/Input.h"
#include "../UI/CheckBox.h"
#include "../UI/DropDownList.h"
#include "../UI/FileSelector.h"
#include "../UI/Font.h"
#include "../UI/LineEdit.h"
#include "../UI/ListView.h"
#include "../UI/MessageBox.h"
#include "../UI/ScrollBar.h"
#include "../UI/Slider.h"
#include "../UI/Sprite.h"
#include "../UI/Text.h"
#include "../UI/Text3D.h"
#include "../UI/ToolTip.h"
#include "../UI/UI.h"
#include "../UI/View3D.h"

#include "../DebugNew.h"

namespace Urho3D
{

static bool FontSaveXMLVectorBuffer(VectorBuffer& buffer, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr)
{
    return ptr->SaveXML(buffer, pointSize, usedGlyphs, indentation);
}

static bool FontSaveXML(const String& fileName, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr)
{
    if (fileName.Empty())
        return false;

    File file(ptr->GetContext(), fileName, FILE_WRITE);
    return ptr->SaveXML(file, pointSize, usedGlyphs, indentation);
}

static void RegisterFont(asIScriptEngine* engine)
{
    RegisterResource<Font>(engine, "Font");
    engine->RegisterObjectMethod("Font", "bool SaveXML(File@+, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", asMETHOD(Font, SaveXML), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "bool SaveXML(VectorBuffer&, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", asFUNCTION(FontSaveXMLVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Font", "bool SaveXML(const String&in, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", asFUNCTION(FontSaveXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Font", "IntVector2 GetTotalGlyphOffset(int) const", asMETHOD(Font, GetTotalGlyphOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_absoluteGlyphOffset(const IntVector2&)", asMETHOD(Font, SetAbsoluteGlyphOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const IntVector2& get_absoluteGlyphOffset() const", asMETHOD(Font, GetAbsoluteGlyphOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "void set_scaledGlyphOffset(const Vector2&)", asMETHOD(Font, SetScaledGlyphOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Font", "const Vector2& get_scaledGlyphOffset() const", asMETHOD(Font, GetScaledGlyphOffset), asCALL_THISCALL);
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

    engine->RegisterEnum("TraversalMode");
    engine->RegisterEnumValue("TraversalMode", "TM_BREADTH_FIRST", TM_BREADTH_FIRST);
    engine->RegisterEnumValue("TraversalMode", "TM_DEPTH_FIRST", TM_DEPTH_FIRST);

    engine->RegisterGlobalProperty("const uint DD_DISABLED", (void*)&DD_DISABLED);
    engine->RegisterGlobalProperty("const uint DD_SOURCE", (void*)&DD_SOURCE);
    engine->RegisterGlobalProperty("const uint DD_TARGET", (void*)&DD_TARGET);
    engine->RegisterGlobalProperty("const uint DD_SOURCE_AND_TARGET", (void*)&DD_SOURCE_AND_TARGET);

    RegisterUIElement<UIElement>(engine, "UIElement");

    // Register TouchState touchedElement property now
    engine->RegisterObjectMethod("TouchState", "UIElement@+ get_touchedElement()", asMETHOD(TouchState, GetTouchedElement), asCALL_THISCALL);
}

static void RegisterBorderImage(asIScriptEngine* engine)
{
    RegisterBorderImage<BorderImage>(engine, "BorderImage");
}

static void RegisterSprite(asIScriptEngine* engine)
{
    RegisterUIElement<Sprite>(engine, "Sprite", true);
    engine->RegisterObjectMethod("Sprite", "void SetPosition(float, float)", asMETHODPR(Sprite, SetPosition, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void SetHotSpot(int, int)", asMETHODPR(Sprite, SetHotSpot, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void SetScale(float, float)", asMETHODPR(Sprite, SetScale, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void SetScale(float)", asMETHODPR(Sprite, SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void SetFullImageRect()", asMETHOD(Sprite, SetFullImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_position(const Vector2&)", asMETHODPR(Sprite, SetPosition, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_position() const", asMETHODPR(Sprite, GetPosition, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_hotSpot(const IntVector2&)", asMETHODPR(Sprite, SetHotSpot, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_hotSpot() const", asMETHOD(Sprite, GetHotSpot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_scale(const Vector2&)", asMETHODPR(Sprite, SetScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_scale() const", asMETHOD(Sprite, GetScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_rotation(float)", asMETHOD(Sprite, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "float get_rotation() const", asMETHOD(Sprite, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_texture(Texture@+)", asMETHOD(Sprite, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "Texture@+ get_texture() const", asMETHOD(Sprite, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_imageRect(const IntRect&in)", asMETHODPR(Sprite, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntRect& get_imageRect() const", asMETHOD(Sprite, GetImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_blendMode(BlendMode)", asMETHOD(Sprite, SetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "BlendMode get_blendMode() const", asMETHOD(Sprite, GetBlendMode), asCALL_THISCALL);
}

static void RegisterCursor(asIScriptEngine* engine)
{
    engine->RegisterEnum("CursorShape");
    engine->RegisterEnumValue("CursorShape", "CS_NORMAL", CS_NORMAL);
    engine->RegisterEnumValue("CursorShape", "CS_IBEAM", CS_IBEAM);
    engine->RegisterEnumValue("CursorShape", "CS_CROSS", CS_CROSS);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEVERTICAL", CS_RESIZEVERTICAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPRIGHT", CS_RESIZEDIAGONAL_TOPRIGHT);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEHORIZONTAL", CS_RESIZEHORIZONTAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPLEFT", CS_RESIZEDIAGONAL_TOPLEFT);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZE_ALL", CS_RESIZE_ALL);
    engine->RegisterEnumValue("CursorShape", "CS_ACCEPTDROP", CS_ACCEPTDROP);
    engine->RegisterEnumValue("CursorShape", "CS_REJECTDROP", CS_REJECTDROP);
    engine->RegisterEnumValue("CursorShape", "CS_BUSY", CS_BUSY);
    engine->RegisterEnumValue("CursorShape", "CS_BUSY_ARROW", CS_BUSY_ARROW);

    RegisterBorderImage<Cursor>(engine, "Cursor");
    engine->RegisterObjectMethod("Cursor", "void DefineShape(const String&in, Texture@+, const IntRect&in, const IntVector2&in)", asMETHODPR(Cursor, DefineShape, (CursorShape, Image*, const IntRect&, const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void DefineShape(CursorShape, Texture@+, const IntRect&in, const IntVector2&in)", asMETHODPR(Cursor, DefineShape, (const String&, Image*, const IntRect&, const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void SetShape(const String&in)", asMETHODPR(Cursor, SetShape, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void SetShape(CursorShape)", asMETHODPR(Cursor, SetShape, (CursorShape), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_shape(const String&in)", asMETHODPR(Cursor, SetShape, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "const String& get_shape() const", asMETHOD(Cursor, GetShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "void set_useSystemShapes(bool)", asMETHOD(Cursor, SetUseSystemShapes), asCALL_THISCALL);
    engine->RegisterObjectMethod("Cursor", "bool get_useSystemShapes() const", asMETHOD(Cursor, GetUseSystemShapes), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Slider", "void set_repeatRate(float)", asMETHOD(Slider, SetRepeatRate), asCALL_THISCALL);
    engine->RegisterObjectMethod("Slider", "float get_repeatRate() const", asMETHOD(Slider, GetRepeatRate), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ScrollView", "void set_scrollBarsAutoVisible(bool)", asMETHOD(ScrollView, SetScrollBarsAutoVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_scrollBarsAutoVisible() const", asMETHOD(ScrollView, GetScrollBarsAutoVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollDeceleration(float)", asMETHOD(ScrollView, SetScrollDeceleration), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollDeceleration() const", asMETHOD(ScrollView, GetScrollDeceleration), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_scrollSnapEpsilon(float)", asMETHOD(ScrollView, SetScrollSnapEpsilon), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_scrollSnapEpsilon() const", asMETHOD(ScrollView, GetScrollSnapEpsilon), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_autoDisableChildren(bool)", asMETHOD(ScrollView, SetAutoDisableChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "bool get_autoDisableChildren() const", asMETHOD(ScrollView, GetAutoDisableChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "void set_autoDisableThreshold(float)", asMETHOD(ScrollView, SetAutoDisableThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("ScrollView", "float get_autoDisableThreshold() const", asMETHOD(ScrollView, GetAutoDisableThreshold), asCALL_THISCALL);
}

void ListViewSetSelections(CScriptArray* selections, ListView* ptr)
{
    unsigned numItems = selections->GetSize();
    PODVector<unsigned> dest;
    dest.Reserve(numItems);

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
    engine->RegisterObjectMethod("ListView", "void InsertItem(uint, UIElement@+, UIElement@+ arg2 = null)", asMETHOD(ListView, InsertItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveItem(UIElement@+, uint index = 0)", asMETHODPR(ListView, RemoveItem, (UIElement*, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveItem(uint)", asMETHODPR(ListView, RemoveItem, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveAllItems()", asMETHOD(ListView, RemoveAllItems), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void AddSelection(uint)", asMETHOD(ListView, AddSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void RemoveSelection(uint)", asMETHOD(ListView, RemoveSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void ToggleSelection(uint)", asMETHOD(ListView, ToggleSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void ChangeSelection(int, bool)", asMETHOD(ListView, ChangeSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void SetSelections(Array<uint>@+)", asFUNCTION(ListViewSetSelections), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ListView", "void ClearSelection()", asMETHOD(ListView, ClearSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void CopySelectedItemsToClipboard()", asMETHOD(ListView, CopySelectedItemsToClipboard), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void Expand(uint, bool, bool arg2 = false)", asMETHOD(ListView, Expand), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void ToggleExpand(uint, bool arg1 = false)", asMETHOD(ListView, ToggleExpand), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool IsSelected(uint) const", asMETHOD(ListView, IsSelected), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool IsExpanded(uint) const", asMETHOD(ListView, IsExpanded), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetItems() const", asFUNCTION(ListViewGetItems), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ListView", "uint FindItem(UIElement@+)", asMETHOD(ListView, FindItem), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_viewPosition(const IntVector2&in)", asMETHODPR(ListView, SetViewPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_viewPosition() const", asMETHOD(ListView, GetViewPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_contentElement() const", asMETHOD(ListView, GetContentElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_horizontalScrollBar() const", asMETHOD(ListView, GetHorizontalScrollBar), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_verticalScrollBar() const", asMETHOD(ListView, GetVerticalScrollBar), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "BorderImage@+ get_scrollPanel() const", asMETHOD(ListView, GetScrollPanel), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollBarsAutoVisible(bool)", asMETHOD(ListView, SetScrollBarsAutoVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_scrollBarsAutoVisible() const", asMETHOD(ListView, GetScrollBarsAutoVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollStep(float)", asMETHOD(ListView, SetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollStep() const", asMETHOD(ListView, GetScrollStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_pageStep(float)", asMETHOD(ListView, SetPageStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_pageStep() const", asMETHOD(ListView, GetPageStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollDeceleration(float)", asMETHOD(ListView, SetScrollDeceleration), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollDeceleration() const", asMETHOD(ListView, GetScrollDeceleration), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollSnapEpsilon(float)", asMETHOD(ListView, SetScrollSnapEpsilon), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollSnapEpsilon() const", asMETHOD(ListView, GetScrollSnapEpsilon), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_autoDisableChildren(bool)", asMETHOD(ListView, SetAutoDisableChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_autoDisableChildren() const", asMETHOD(ListView, GetAutoDisableChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_autoDisableThreshold(float)", asMETHOD(ListView, SetAutoDisableThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_autoDisableThreshold() const", asMETHOD(ListView, GetAutoDisableThreshold), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ListView", "void set_baseIndent(int)", asMETHOD(ListView, SetBaseIndent), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_baseIndent() const", asMETHOD(ListView, GetBaseIndent), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clearSelectionOnDefocus(bool)", asMETHOD(ListView, SetClearSelectionOnDefocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_clearSelectionOnDefocus() const", asMETHOD(ListView, GetClearSelectionOnDefocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selectOnClickEnd(bool)", asMETHOD(ListView, SetSelectOnClickEnd), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_selectOnClickEnd() const", asMETHOD(ListView, GetSelectOnClickEnd), asCALL_THISCALL);
}

static void RegisterText(asIScriptEngine* engine)
{
    engine->RegisterEnum("TextEffect");
    engine->RegisterEnumValue("TextEffect", "TE_NONE", TE_NONE);
    engine->RegisterEnumValue("TextEffect", "TE_SHADOW", TE_SHADOW);
    engine->RegisterEnumValue("TextEffect", "TE_STROKE", TE_STROKE);

    RegisterUIElement<Text>(engine, "Text");
    engine->RegisterObjectMethod("Text", "bool SetFont(const String&in, int)", asMETHODPR(Text, SetFont, (const String&, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool SetFont(Font@+, int)", asMETHODPR(Text, SetFont, (Font*, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void SetSelection(uint, uint arg1 = M_MAX_UNSIGNED)", asMETHOD(Text, SetSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void ClearSelection()", asMETHOD(Text, ClearSelection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Font@+ get_font() const", asMETHOD(Text, GetFont), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_fontSize() const", asMETHOD(Text, GetFontSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_text(const String&in)", asMETHOD(Text, SetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_text() const", asMETHOD(Text, GetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_textAlignment(HorizontalAlignment)", asMETHOD(Text, SetTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "HorizontalAlignment get_textAlignment() const", asMETHOD(Text, GetTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_rowSpacing(float)", asMETHOD(Text, SetRowSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowSpacing() const", asMETHOD(Text, GetRowSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_wordwrap(bool)", asMETHOD(Text, SetWordwrap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_wordwrap() const", asMETHOD(Text, GetWordwrap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_autoLocalizable(bool)", asMETHOD(Text, SetAutoLocalizable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_autoLocalizable() const", asMETHOD(Text, GetAutoLocalizable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionStart() const", asMETHOD(Text, GetSelectionStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionLength() const", asMETHOD(Text, GetSelectionLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_selectionColor(const Color&in)", asMETHOD(Text, SetSelectionColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_selectionColor() const", asMETHOD(Text, GetSelectionColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_hoverColor(const Color&in)", asMETHOD(Text, SetHoverColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_hoverColor() const", asMETHOD(Text, GetHoverColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_textEffect(TextEffect)", asMETHOD(Text, SetTextEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "TextEffect get_textEffect() const", asMETHOD(Text, GetTextEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectColor(const Color&in)", asMETHOD(Text, SetEffectColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_effectColor() const", asMETHOD(Text, GetEffectColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numRows() const", asMETHOD(Text, GetNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numChars() const", asMETHOD(Text, GetNumChars), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_rowWidths(uint) const", asMETHOD(Text, GetRowWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "IntVector2 get_charPositions(uint)", asMETHOD(Text, GetCharPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "IntVector2 get_charSizes(uint)", asMETHOD(Text, GetCharSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_rowHeight() const", asMETHOD(Text, GetRowHeight), asCALL_THISCALL);
}

static void RegisterText3D(asIScriptEngine* engine)
{
    RegisterDrawable<Text3D>(engine, "Text3D");
    engine->RegisterObjectMethod("Text3D", "bool SetFont(const String&in, int)", asMETHODPR(Text3D, SetFont, (const String&, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool SetFont(Font@+, int)", asMETHODPR(Text3D, SetFont, (Font*, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHOD(Text3D, SetAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Font@+ get_font() const", asMETHOD(Text3D, GetFont), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_fontSize() const", asMETHOD(Text3D, GetFontSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_material(Material@+)", asMETHOD(Text3D, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Material@+ get_material() const", asMETHOD(Text3D, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_text(const String&in)", asMETHOD(Text3D, SetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const String& get_text() const", asMETHOD(Text3D, GetText), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_textAlignment(HorizontalAlignment)", asMETHOD(Text3D, SetTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment get_textAlignment() const", asMETHOD(Text3D, GetTextAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_horizontalAlignment(HorizontalAlignment)", asMETHOD(Text3D, SetHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment get_horizontalAlignment() const", asMETHOD(Text3D, GetHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_verticalAlignment(VerticalAlignment)", asMETHOD(Text3D, SetVerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "VerticalAlignment get_verticalAlignment() const", asMETHOD(Text3D, GetVerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_rowSpacing(float)", asMETHOD(Text3D, SetRowSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_rowSpacing() const", asMETHOD(Text3D, GetRowSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_wordwrap(bool)", asMETHOD(Text3D, SetWordwrap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_wordwrap() const", asMETHOD(Text3D, GetWordwrap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_textEffect(TextEffect)", asMETHOD(Text3D, SetTextEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "TextEffect get_textEffect() const", asMETHOD(Text3D, GetTextEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectColor(const Color&in)", asMETHOD(Text3D, SetEffectColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Color& get_effectColor() const", asMETHOD(Text3D, GetEffectColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectDepthBias(float)", asMETHOD(Text3D, SetEffectDepthBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_effectDepthBias() const", asMETHOD(Text3D, GetEffectDepthBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_width(int)", asMETHOD(Text3D, SetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_width() const", asMETHOD(Text3D, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_color(const Color&in)", asMETHODPR(Text3D, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_colors(Corner, const Color&in)", asMETHODPR(Text3D, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Color& get_colors(Corner) const", asMETHOD(Text3D, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_opacity(float)", asMETHOD(Text3D, SetOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_opacity() const", asMETHOD(Text3D, GetOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_faceCameraMode(FaceCameraMode)", asMETHOD(Text3D, SetFaceCameraMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "FaceCameraMode get_faceCameraMode() const", asMETHOD(Text3D, GetFaceCameraMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numRows() const", asMETHOD(Text3D, GetNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numChars() const", asMETHOD(Text3D, GetNumChars), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_rowWidths(uint) const", asMETHOD(Text3D, GetRowWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "IntVector2 get_charPositions(uint)", asMETHOD(Text3D, GetCharPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "IntVector2 get_charSizes(uint)", asMETHOD(Text3D, GetCharSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_rowHeight() const", asMETHOD(Text3D, GetRowHeight), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("LineEdit", "void set_echoCharacter(uint)", asMETHOD(LineEdit, SetEchoCharacter), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_echoCharacter() const", asMETHOD(LineEdit, GetEchoCharacter), asCALL_THISCALL);
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

static MessageBox* ConstructMessageBox(const String& messageString, const String& titleString, XMLFile* layoutFile, XMLFile* styleFile)
{
    SharedPtr<MessageBox> messageBox(new MessageBox(GetScriptContext(), messageString, titleString, layoutFile, styleFile));
    if (messageBox)
        messageBox->AddRef();
    return messageBox.Get();
}

static void RegisterMessageBox(asIScriptEngine* engine)
{
    RegisterObject<MessageBox>(engine, "MessageBox");
    engine->RegisterObjectBehaviour("MessageBox", asBEHAVE_FACTORY, "MessageBox@+ f(const String&in messageString = String(), const String&in titleString = String(), XMLFile@+ layoutFile = null, XMLFile@+ styleFile = null)", asFUNCTION(ConstructMessageBox), asCALL_CDECL);
    engine->RegisterObjectMethod("MessageBox", "void set_title(const String&in)", asMETHOD(MessageBox, SetTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_title() const", asMETHOD(MessageBox, GetTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "void set_message(const String&in)", asMETHOD(MessageBox, SetMessage), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "const String& get_message() const", asMETHOD(MessageBox, GetMessage), asCALL_THISCALL);
    engine->RegisterObjectMethod("MessageBox", "UIElement@+ get_window() const", asMETHOD(MessageBox, GetWindow), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("DropDownList", "void set_placeholderText(const String&in)", asMETHOD(DropDownList, SetPlaceholderText), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_placeholderText() const", asMETHOD(DropDownList, GetPlaceholderText), asCALL_THISCALL);
}

static void RegisterWindow(asIScriptEngine* engine)
{
    RegisterWindow<Window>(engine, "Window");
}

static void RegisterView3D(asIScriptEngine* engine)
{
    RegisterWindow<View3D>(engine, "View3D");
    engine->RegisterObjectMethod("View3D", "void SetView(Scene@+, Camera@+, bool ownScene=true)", asMETHOD(View3D, SetView), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void QueueUpdate()", asMETHOD(View3D, QueueUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_format(uint)", asMETHOD(View3D, SetFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "uint get_format() const", asMETHOD(View3D, GetFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "void set_autoUpdate(bool)", asMETHOD(View3D, SetAutoUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "bool get_autoUpdate() const", asMETHOD(View3D, GetAutoUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture2D@+ get_renderTexture() const", asMETHOD(View3D, GetRenderTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Texture2D@+ get_depthTexture() const", asMETHOD(View3D, GetDepthTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Viewport@+ get_viewport() const", asMETHOD(View3D, GetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Scene@+ get_scene() const", asMETHOD(View3D, GetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("View3D", "Node@+ get_cameraNode() const", asMETHOD(View3D, GetCameraNode), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("FileSelector", "void set_defaultStyle(XMLFile@+)", asMETHOD(FileSelector, SetDefaultStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "XMLFile@+ get_defaultStyle() const", asMETHOD(FileSelector, GetDefaultStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Window@+ get_window() const", asMETHOD(FileSelector, GetWindow), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Text@+ get_titleText() const", asMETHOD(FileSelector, GetTitleText), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "ListView@+ get_fileList() const", asMETHOD(FileSelector, GetFileList), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_pathEdit() const", asMETHOD(FileSelector, GetPathEdit), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "LineEdit@+ get_fileNameEdit() const", asMETHOD(FileSelector, GetFileNameEdit), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "DropDownList@+ get_filterList() const", asMETHOD(FileSelector, GetFilterList), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_okButton() const", asMETHOD(FileSelector, GetOKButton), asCALL_THISCALL);
    engine->RegisterObjectMethod("FileSelector", "Button@+ get_cancelButton() const", asMETHOD(FileSelector, GetCancelButton), asCALL_THISCALL);
}

static void RegisterToolTip(asIScriptEngine* engine)
{
    RegisterUIElement<ToolTip>(engine, "ToolTip");
    engine->RegisterObjectMethod("ToolTip", "void set_delay(float)", asMETHOD(ToolTip, SetDelay), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "float get_delay() const", asMETHOD(ToolTip, GetDelay), asCALL_THISCALL);
}

static UI* GetUI()
{
    return GetScriptContext()->GetSubsystem<UI>();
}

static UIElement* UILoadLayoutFromFile(File* file, UI* ptr)
{
    if (file)
    {
        SharedPtr<UIElement> root = ptr->LoadLayout(*file);
        if (root)
            root->AddRef();
        return root.Get();
    }
    else
        return 0;
}

static UIElement* UILoadLayoutFromVectorBuffer(VectorBuffer& buffer, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer);
    if (root)
        root->AddRef();
    return root.Get();
}

static UIElement* UILoadLayoutFromFileWithStyle(File* file, XMLFile* styleFile, UI* ptr)
{
    if (file)
    {
        SharedPtr<UIElement> root = ptr->LoadLayout(*file, styleFile);
        if (root)
            root->AddRef();
        return root.Get();
    }
    else
        return 0;
}

static UIElement* UILoadLayoutFromVectorBufferWithStyle(VectorBuffer& buffer, XMLFile* styleFile, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer, styleFile);
    if (root)
        root->AddRef();
    return root.Get();
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

static bool UISaveLayout(File* file, UIElement* element, UI* ptr)
{
    return file && ptr->SaveLayout(*file, element);
}

static bool UISaveLayoutVectorBuffer(VectorBuffer& buffer, UIElement* element, UI* ptr)
{
    return ptr->SaveLayout(buffer, element);
}

static void UISetFocusElement(UIElement* element, UI* ptr)
{
    ptr->SetFocusElement(element);
}

static CScriptArray* UIGetDragElements(UI* ptr)
{
    return VectorToHandleArray(ptr->GetDragElements(), "const Array<UIElement@>@");
}

static void RegisterUI(asIScriptEngine* engine)
{
    RegisterObject<UI>(engine, "UI");
    engine->RegisterObjectMethod("UI", "void Clear()", asMETHOD(UI, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void DebugDraw(UIElement@+)", asMETHOD(UI, DebugDraw), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(File@+)", asFUNCTION(UILoadLayoutFromFile), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(File@+, XMLFile@+)", asFUNCTION(UILoadLayoutFromFileWithStyle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(VectorBuffer&)", asFUNCTION(UILoadLayoutFromVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(VectorBuffer&, XMLFile@+)", asFUNCTION(UILoadLayoutFromVectorBufferWithStyle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(XMLFile@+)", asFUNCTION(UILoadLayout), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@ LoadLayout(XMLFile@+, XMLFile@+)", asFUNCTION(UILoadLayoutWithStyle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "bool SaveLayout(File@+, UIElement@+)", asFUNCTION(UISaveLayout), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "bool SaveLayout(VectorBuffer&, UIElement@+)", asFUNCTION(UISaveLayoutVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "void SetFocusElement(UIElement@+, bool byKey = false)", asMETHOD(UI, SetFocusElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void SetWidth(float value)", asMETHOD(UI, SetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void SetHeight(float value)", asMETHOD(UI, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(const IntVector2&in, bool activeOnly = true)", asMETHODPR(UI, GetElementAt, (const IntVector2&, bool), UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(int, int, bool activeOnly = true)", asMETHODPR(UI, GetElementAt, (int, int, bool), UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool HasModalElement() const", asMETHOD(UI, HasModalElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_cursor(Cursor@+)", asMETHOD(UI, SetCursor), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "Cursor@+ get_cursor() const", asMETHOD(UI, GetCursor), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "IntVector2 get_cursorPosition() const", asMETHOD(UI, GetCursorPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_focusElement(UIElement@+)", asFUNCTION(UISetFocusElement), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_focusElement() const", asMETHOD(UI, GetFocusElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_frontElement() const", asMETHOD(UI, GetFrontElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const Array<UIElement@>@ GetDragElements()", asFUNCTION(UIGetDragElements), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("UI", "bool IsDragging() const", asMETHOD(UI, IsDragging), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_root() const", asMETHOD(UI, GetRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_modalRoot() const", asMETHOD(UI, GetRootModalElement), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_clipBoardText(const String&in)", asMETHOD(UI, SetClipboardText), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const String& get_clipBoardText() const", asMETHOD(UI, GetClipboardText), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_doubleClickInterval(float)", asMETHOD(UI, SetDoubleClickInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_doubleClickInterval() const", asMETHOD(UI, GetDoubleClickInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_dragBeginInterval(float)", asMETHOD(UI, SetDragBeginInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_dragBeginInterval() const", asMETHOD(UI, GetDragBeginInterval), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_dragBeginDistance(int)", asMETHOD(UI, SetDragBeginDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_dragBeginDistance() const", asMETHOD(UI, GetDragBeginDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_defaultToolTipDelay(float)", asMETHOD(UI, SetDefaultToolTipDelay), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_defaultToolTipDelay() const", asMETHOD(UI, GetDefaultToolTipDelay), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_maxFontTextureSize(int)", asMETHOD(UI, SetMaxFontTextureSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_maxFontTextureSize() const", asMETHOD(UI, GetMaxFontTextureSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_nonFocusedMouseWheel(bool)", asMETHOD(UI, SetNonFocusedMouseWheel), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_nonFocusedMouseWheel() const", asMETHOD(UI, IsNonFocusedMouseWheel), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useSystemClipboard(bool)", asMETHOD(UI, SetUseSystemClipboard), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useSystemClipboard() const", asMETHOD(UI, GetUseSystemClipboard), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useScreenKeyboard(bool)", asMETHOD(UI, SetUseScreenKeyboard), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useScreenKeyboard() const", asMETHOD(UI, GetUseScreenKeyboard), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useMutableGlyphs(bool)", asMETHOD(UI, SetUseMutableGlyphs), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useMutableGlyphs() const", asMETHOD(UI, GetUseMutableGlyphs), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_forceAutoHint(bool)", asMETHOD(UI, SetForceAutoHint), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_forceAutoHint() const", asMETHOD(UI, GetForceAutoHint), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_scale(float value)", asMETHOD(UI, SetScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_scale() const", asMETHOD(UI, GetScale), asCALL_THISCALL);
    engine->RegisterGlobalFunction("UI@+ get_ui()", asFUNCTION(GetUI), asCALL_CDECL);
}

void RegisterUIAPI(asIScriptEngine* engine)
{
    RegisterFont(engine);
    RegisterUIElement(engine);
    RegisterBorderImage(engine);
    RegisterSprite(engine);
    RegisterButton(engine);
    RegisterCheckBox(engine);
    RegisterCursor(engine);
    RegisterSlider(engine);
    RegisterScrollBar(engine);
    RegisterScrollView(engine);
    RegisterListView(engine);
    RegisterText(engine);
    RegisterText3D(engine);
    RegisterLineEdit(engine);
    RegisterMenu(engine);
    RegisterMessageBox(engine);
    RegisterDropDownList(engine);
    RegisterWindow(engine);
    RegisterView3D(engine);
    RegisterFileSelector(engine);
    RegisterToolTip(engine);
    RegisterUI(engine);
}

}
