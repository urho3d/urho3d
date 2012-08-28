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

#pragma once

#include "Serializable.h"
#include "UIBatch.h"
#include "Vector2.h"
#include "XMLFile.h"

namespace Urho3D
{

/// %UI element horizontal alignment.
enum HorizontalAlignment
{
    HA_LEFT = 0,
    HA_CENTER,
    HA_RIGHT
};

/// %UI element vertical alignment.
enum VerticalAlignment
{
    VA_TOP = 0,
    VA_CENTER,
    VA_BOTTOM
};

/// %UI element corners.
enum Corner
{
    C_TOPLEFT = 0,
    C_TOPRIGHT,
    C_BOTTOMLEFT,
    C_BOTTOMRIGHT,
    MAX_UIELEMENT_CORNERS
};

/// %UI element orientation.
enum Orientation
{
    O_HORIZONTAL = 0,
    O_VERTICAL
};

/// %UI element focus mode.
enum FocusMode
{
    /// Is not focusable and does not affect existing focus.
    FM_NOTFOCUSABLE = 0,
    /// Resets focus when clicked.
    FM_RESETFOCUS,
    /// Is focusable.
    FM_FOCUSABLE,
    /// Is focusable and also defocusable by pressing ESC.
    FM_FOCUSABLE_DEFOCUSABLE
};

/// Layout operation mode.
enum LayoutMode
{
    /// No layout operations will be performed.
    LM_FREE = 0,
    /// Layout child elements horizontally and resize them to fit. Resize element if necessary.
    LM_HORIZONTAL,
    /// Layout child elements vertically and resize them to fit. Resize element if necessary.
    LM_VERTICAL
};

/// Drag and drop disabled.
static const unsigned DD_DISABLED = 0x0;
/// Drag and drop source flag.
static const unsigned DD_SOURCE = 0x1;
/// Drag and drop target flag.
static const unsigned DD_TARGET = 0x2;
/// Drag and drop source and target.
static const unsigned DD_SOURCE_AND_TARGET = 0x3;

class Cursor;
class ResourceCache;

/// Base class for %UI elements.
class UIElement : public Serializable
{
    OBJECT(UIElement);
    
public:
    /// Construct.
    UIElement(Context* context);
    /// Destruct.
    virtual ~UIElement();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Apply attribute changes that can not be applied immediately.
    virtual void ApplyAttributes();
    /// Load from XML data. Return true if successful.
    virtual bool LoadXML(const XMLElement& source);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest);
    /// Perform UI element update.
    virtual void Update(float timeStep);
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, const IntRect& currentScissor);
    
    /// React to mouse hover.
    virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse click.
    virtual void OnClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag begin.
    virtual void OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag motion.
    virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag end.
    virtual void OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, Cursor* cursor);
    /// React to drag and drop test. Return true to signal that the drop is acceptable.
    virtual bool OnDragDropTest(UIElement* source);
    /// React to drag and drop finish. Return true to signal that the drop was accepted.
    virtual bool OnDragDropFinish(UIElement* source);
    /// React to mouse wheel.
    virtual void OnWheel(int delta, int buttons, int qualifiers);
    /// React to a key press.
    virtual void OnKey(int key, int buttons, int qualifiers);
    /// React to a key press translated to a character.
    virtual void OnChar(unsigned c, int buttons, int qualifiers);
    /// React to resize.
    virtual void OnResize();
    
    /// Load from XML data with style. Return true if successful.
    bool LoadXML(const XMLElement& source, XMLFile* styleFile);
    /// Load from an XML file. Return true if successful.
    bool LoadXML(Deserializer& source);
    /// Save to an XML file. Return true if successful.
    bool SaveXML(Serializer& dest);
    
    /// Set name.
    void SetName(const String& name);
    /// Set position.
    void SetPosition(const IntVector2& position);
    /// Set position.
    void SetPosition(int x, int y);
    /// Set size.
    void SetSize(const IntVector2& size);
    /// Set size.
    void SetSize(int width, int height);
    /// Set width only.
    void SetWidth(int width);
    /// Set height only.
    void SetHeight(int height);
    /// Set minimum size.
    void SetMinSize(const IntVector2& minSize);
    /// Set minimum size.
    void SetMinSize(int width, int height);
    /// Set minimum width.
    void SetMinWidth(int width);
    /// Set minimum height.
    void SetMinHeight(int height);
    /// Set maximum size.
    void SetMaxSize(const IntVector2& maxSize);
    /// Set maximum size.
    void SetMaxSize(int width, int height);
    /// Set maximum width.
    void SetMaxWidth(int width);
    /// Set maximum height.
    void SetMaxHeight(int height);
    /// Set fixed size.
    void SetFixedSize(const IntVector2& size);
    /// Set fixed size.
    void SetFixedSize(int width, int height);
    /// Set fixed width.
    void SetFixedWidth(int width);
    /// Set fixed height.
    void SetFixedHeight(int height);
    /// Set horizontal and vertical alignment.
    void SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign);
    /// Set horizontal alignment.
    void SetHorizontalAlignment(HorizontalAlignment align);
    /// Set vertical alignment.
    void SetVerticalAlignment(VerticalAlignment align);
    /// Set child element clipping border.
    void SetClipBorder(const IntRect& rect);
    /// Set color on all corners.
    void SetColor(const Color& color);
    /// Set color on one corner.
    void SetColor(Corner corner, const Color& color);
    /// Set priority.
    void SetPriority(int priority);
    /// Set opacity.
    void SetOpacity(float opacity);
    /// Set whether should be brought to front when focused.
    void SetBringToFront(bool enable);
    /// Set whether should be put to background when another element is focused.
    void SetBringToBack(bool enable);
    /// Set whether should clip child elements. Default false.
    void SetClipChildren(bool enable);
    /// Set whether should sort child elements according to priority. Default true.
    void SetSortChildren(bool enable);
    /// Set whether reacts to input.
    void SetActive(bool enable);
    /// Set whether is focused. Only one element can be focused at a time.
    void SetFocus(bool enable);
    /// Set selected mode. Actual meaning is element dependent, for example constant hover or pressed effect.
    void SetSelected(bool enable);
    /// Set whether is visible.
    void SetVisible(bool enable);
    /// Set focus mode.
    void SetFocusMode(FocusMode mode);
    /// Set drag and drop flags.
    void SetDragDropMode(unsigned mode);
    /// Set style from an XML file. Find the style element by name.
    void SetStyle(XMLFile* file, const String& typeName);
    /// Set style from an XML element.
    void SetStyle(const XMLElement& element);
    /// Set style from an XML file. Find the style element automatically.
    void SetStyleAuto(XMLFile* file);
    /// Set layout.
    void SetLayout(LayoutMode mode, int spacing = 0, const IntRect& border = IntRect::ZERO);
    /// Set layout mode only.
    void SetLayoutMode(LayoutMode mode);
    /// Set layout spacing.
    void SetLayoutSpacing(int spacing);
    /// Set layout border.
    void SetLayoutBorder(const IntRect& border);
    /// Manually update layout. Should not be necessary in most cases, but is provided for completeness.
    void UpdateLayout();
    /// Disable automatic layout update. Should only be used if there are performance problems.
    void DisableLayoutUpdate();
    /// Enable automatic layout update.
    void EnableLayoutUpdate();
    /// Bring UI element to front.
    void BringToFront();
    /// Create and add a child element and return it.
    UIElement* CreateChild(ShortStringHash type, const String& name = String());
    /// Add a child element.
    void AddChild(UIElement* element);
    /// Insert a child element into a specific position in the child list.
    void InsertChild(unsigned index, UIElement* element);
    /// Remove a child element.
    void RemoveChild(UIElement* element);
    /// Remove all child elements.
    void RemoveAllChildren();
    /// Remove from the parent element. If no other shared pointer references exist, causes immediate deletion.
    void Remove();
    /// Set parent element. Same as parent->AddChild(this).
    void SetParent(UIElement* parent);
    /// Set a user variable.
    void SetVar(ShortStringHash key, const Variant& value);
    /// Mark as internally (programmatically) created. Used when an element composes itself out of child elements.
    void SetInternal(bool enable);
    /// Template version of creating a child element.
    template <class T> T* CreateChild(const String& name = String());
    
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return position.
    const IntVector2& GetPosition() const { return position_; }
    /// Return screen position.
    IntVector2 GetScreenPosition();
    /// Return size.
    const IntVector2& GetSize() const { return size_; }
    /// Return width.
    int GetWidth() const { return size_.x_; }
    /// Return height.
    int GetHeight() const { return size_.y_; }
    /// Return minimum size.
    const IntVector2& GetMinSize() const { return minSize_; }
    /// Return minimum width.
    int GetMinWidth() const { return minSize_.x_; }
    /// Return minimum height.
    int GetMinHeight() const { return minSize_.y_; }
    /// Return maximum size.
    const IntVector2& GetMaxSize() const { return maxSize_; }
    /// Return minimum width.
    int GetMaxWidth() const { return maxSize_.x_; }
    /// Return minimum height.
    int GetMaxHeight() const { return maxSize_.y_; }
    /// Return child element offset.
    const IntVector2& GetChildOffset() const { return childOffset_; }
    /// Return horizontal alignment.
    HorizontalAlignment GetHorizontalAlignment() const { return horizontalAlignment_; }
    /// Return vertical alignment.
    VerticalAlignment GetVerticalAlignment() const { return verticalAlignment_; }
    /// Return child element clipping border.
    const IntRect& GetClipBorder() const { return clipBorder_; }
    /// Return corner color.
    const Color& GetColor(Corner corner) const { return color_[corner]; }
    /// Return priority.
    int GetPriority() const { return priority_; }
    /// Return opacity.
    float GetOpacity() const { return opacity_; }
    /// Return derived opacity (affected by parent elements.)
    float GetDerivedOpacity();
    /// Return whether should be brought to front when focused.
    bool GetBringToFront() const { return bringToFront_; }
    /// Return whether should be put to background when another element is focused.
    bool GetBringToBack() const { return bringToBack_; }
    /// Return whether should clip child elements.
    bool GetClipChildren() const { return clipChildren_; }
    /// Return whether should sort child elements according to priority.
    bool GetSortChildren() const { return sortChildren_; }
    /// Return whether has focus.
    bool HasFocus() const;
    /// Return whether reacts to input.
    bool IsActive() const { return active_; }
    /// Return whether is selected. Actual meaning is element dependent.
    bool IsSelected() const { return selected_; }
    /// Return whether is visible.
    bool IsVisible() const { return visible_; }
    /// Return whether the cursor is hovering on this element.
    bool IsHovering() const { return hovering_; }
    /// Return whether is internally created.
    bool IsInternal() const { return internal_; }
    /// Return whether has different color in at least one corner.
    bool HasColorGradient() const { return colorGradient_; }
    /// Return focus mode.
    FocusMode GetFocusMode() const { return focusMode_; }
    /// Return drag and drop flags.
    unsigned GetDragDropMode() const { return dragDropMode_; }
    /// Return layout mode.
    LayoutMode GetLayoutMode() const { return layoutMode_; }
    /// Return layout spacing.
    int GetLayoutSpacing() const { return layoutSpacing_; }
    /// Return layout border.
    const IntRect& GetLayoutBorder() const { return layoutBorder_; }
    /// Return number of child elements.
    unsigned GetNumChildren(bool recursive = false) const;
    /// Return child element by index.
    UIElement* GetChild(unsigned index) const;
    /// Return child element by name.
    UIElement* GetChild(const String& name, bool recursive = false) const;
    /// Return immediate child elements.
    const Vector<SharedPtr<UIElement> >& GetChildren() const { return children_; }
    /// Return child elements either recursively or non-recursively.
    void GetChildren(PODVector<UIElement*>& dest, bool recursive = false) const;
    /// Return parent element.
    UIElement* GetParent() const { return parent_; }
    /// Return root element.
    UIElement* GetRoot() const;
    /// Return precalculated 32-bit color. Only valid when no gradient.
    unsigned GetUIntColor();
    /// Return a user variable.
    const Variant& GetVar(ShortStringHash key) const;
    /// Return all user variables.
    const VariantMap& GetVars() const { return vars_; }
    
    /// Convert screen coordinates to element coordinates.
    IntVector2 ScreenToElement(const IntVector2& screenPosition);
    /// Convert element coordinates to screen coordinates.
    IntVector2 ElementToScreen(const IntVector2& position);
    /// Return whether a point (either in element or screen coordinates) is inside the element.
    bool IsInside(IntVector2 position, bool isScreen);
    /// Return whether a point (either in element or screen coordinates) is inside the combined rect of the element and its children.
    bool IsInsideCombined(IntVector2 position, bool isScreen);
    /// Return combined screen coordinate rect of element and its children.
    IntRect GetCombinedScreenRect();
    /// Sort child elements if sorting enabled and order dirty. Called by UI.
    void SortChildren();
    /// Return minimum layout element size in the layout direction. Only valid after layout has been calculated.
    int GetLayoutMinSize() const { return layoutMinSize_; }
    
    /// Set child offset.
    void SetChildOffset(const IntVector2& offset);
    /// Set hovering state.
    void SetHovering(bool enable);
    /// Set temporary visibility status without updating layout or sending events. Used internally.
    void SetTempVisible(bool enable);
    /// Adjust scissor for rendering.
    void AdjustScissor(IntRect& currentScissor);
    /// Get UI rendering batches with a specified offset. Also recurses to child elements.
    void GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, IntRect
        currentScissor);
    
protected:
    /// Mark screen position as needing an update.
    void MarkDirty();
    
    /// Name.
    String name_;
    /// Child elements.
    Vector<SharedPtr<UIElement> > children_;
    /// Parent element.
    UIElement* parent_;
    /// Child element clipping border.
    IntRect clipBorder_;
    /// Colors.
    Color color_[MAX_UIELEMENT_CORNERS];
    /// User variables.
    VariantMap vars_;
    /// Priority.
    int priority_;
    /// Bring to front when focused flag.
    bool bringToFront_;
    /// Bring to back when defocused flag.
    bool bringToBack_;
    /// Clip children flag.
    bool clipChildren_;
    /// Sort childrenaccording to priority flag.
    bool sortChildren_;
    /// Input enabled flag.
    bool active_;
    /// Selected flag.
    bool selected_;
    /// Visible flag.
    bool visible_;
    /// Hovering flag.
    bool hovering_;
    /// Internally created flag.
    bool internal_;
    /// Focus mode.
    FocusMode focusMode_;
    /// Drag and drop flags.
    unsigned dragDropMode_;
    /// Layout mode.
    LayoutMode layoutMode_;
    /// Layout spacing.
    int layoutSpacing_;
    /// Layout borders.
    IntRect layoutBorder_;
    /// Resize nesting level to prevent multiple events and endless loop.
    unsigned resizeNestingLevel_;
    /// Layout update nesting level to prevent endless loop.
    unsigned layoutNestingLevel_;
    /// Layout element minimum size in layout direction.
    int layoutMinSize_;
    
private:
    /// Return child elements recursively.
    void GetChildrenRecursive(PODVector<UIElement*>& dest) const;
    /// Calculate layout width for resizing the parent element.
    int CalculateLayoutParentSize(const PODVector<int>& sizes, int begin, int end, int spacing);
    /// Calculate child widths/positions in the layout.
    void CalculateLayout(PODVector<int>& positions, PODVector<int>& sizes, const PODVector<int>& minSizes, const PODVector<int>& maxSizes, int targetWidth, int begin, int end, int spacing);
    /// Get child element constant position in a layout.
    IntVector2 GetLayoutChildPosition(UIElement* child);
    
    /// Position.
    IntVector2 position_;
    /// Screen position.
    IntVector2 screenPosition_;
    /// Size.
    IntVector2 size_;
    /// Minimum size.
    IntVector2 minSize_;
    /// Maximum size.
    IntVector2 maxSize_;
    /// Child elements' offset. Used internally.
    IntVector2 childOffset_;
    /// Horizontal alignment.
    HorizontalAlignment horizontalAlignment_;
    /// Vertical alignment.
    VerticalAlignment verticalAlignment_;
    /// Opacity.
    float opacity_;
    /// Derived opacity.
    float derivedOpacity_;
    /// Precalculated 32-bit color.
    unsigned uintColor_;
    /// Screen position dirty flag.
    bool positionDirty_;
    /// Derived opacity dirty flag.
    bool opacityDirty_;
    /// Derived color dirty flag (only used when no gradient.)
    bool derivedColorDirty_;
    /// Child priority sorting dirty flag.
    bool sortOrderDirty_;
    /// Has color gradient flag.
    bool colorGradient_;
};

template <class T> T* UIElement::CreateChild(const String& name) { return static_cast<T*>(CreateChild(T::GetTypeStatic(), name)); }

}

