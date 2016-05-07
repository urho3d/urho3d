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

#pragma once

#include "../Math/Vector2.h"
#include "../Resource/XMLFile.h"
#include "../Scene/Animatable.h"
#include "../UI/UIBatch.h"

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

/// Traversal mode for rendering.
enum TraversalMode
{
    /// Traverse thru children having same priority first and recurse into their children before traversing children having higher priority.
    TM_BREADTH_FIRST = 0,
    /// Traverse thru each child and its children immediately after in sequence.
    TM_DEPTH_FIRST
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
class URHO3D_API UIElement : public Animatable
{
    URHO3D_OBJECT(UIElement, Animatable);

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
    virtual bool LoadXML(const XMLElement& source, bool setInstanceDefault = false);
    /// Load from XML data with style. Return true if successful.
    virtual bool LoadXML(const XMLElement& source, XMLFile* styleFile, bool setInstanceDefault = false);
    /// Create a child by loading from XML data with style. Return true if successful.
    virtual bool LoadChildXML(const XMLElement& childElem, XMLFile* styleFile = 0, bool setInstanceDefault = false);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest) const;

    /// Perform UI element update.
    virtual void Update(float timeStep);
    /// Return whether is visible and inside a scissor rectangle and should be rendered.
    virtual bool IsWithinScissor(const IntRect& currentScissor);
    /// Update and return screen position.
    virtual const IntVector2& GetScreenPosition() const;
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
    /// Return UI rendering batches for debug draw.
    virtual void GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
    /// React to mouse hover.
    virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse click begin.
    virtual void OnClickBegin
        (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) { }
    /// React to mouse click end.
    virtual void OnClickEnd
        (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor,
            UIElement* beginElement) { }
    /// React to double mouse click.
    virtual void OnDoubleClick
        (const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor) { }
    /// React to mouse drag begin.
    virtual void
        OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag motion.
    virtual void OnDragMove
        (const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers,
            Cursor* cursor);
    /// React to mouse drag end.
    virtual void
        OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int releaseButton, Cursor* cursor);
    /// React to a mouse drag cancel event (ie, when an extra button is pressed)
    virtual void OnDragCancel
        (const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int cancelButton, Cursor* cursor);
    /// React to drag and drop test. Return true to signal that the drop is acceptable.
    virtual bool OnDragDropTest(UIElement* source);
    /// React to drag and drop finish. Return true to signal that the drop was accepted.
    virtual bool OnDragDropFinish(UIElement* source);
    /// React to mouse wheel.
    virtual void OnWheel(int delta, int buttons, int qualifiers) { }
    /// React to a key press.
    virtual void OnKey(int key, int buttons, int qualifiers) { }
    /// React to text input event.
    virtual void OnTextInput(const String& text, int buttons, int qualifiers) { }

    /// React to resize.
    virtual void OnResize() { }

    /// React to position change.
    virtual void OnPositionSet() { }

    /// React to editable status change.
    virtual void OnSetEditable() { }

    /// React to indent change.
    virtual void OnIndentSet() { }

    /// Convert screen coordinates to element coordinates.
    virtual IntVector2 ScreenToElement(const IntVector2& screenPosition);
    /// Convert element coordinates to screen coordinates.
    virtual IntVector2 ElementToScreen(const IntVector2& position);

    /// Load from an XML file. Return true if successful.
    bool LoadXML(Deserializer& source);
    /// Save to an XML file. Return true if successful.
    bool SaveXML(Serializer& dest, const String& indentation = "\t") const;
    /// Filter attributes in serialization process.
    bool FilterAttributes(XMLElement& dest) const;

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
    /// Set whether parent elements' opacity affects opacity. Default true.
    void SetUseDerivedOpacity(bool enable);
    /// Set whether reacts to input. Default false, but is enabled by subclasses if applicable.
    void SetEnabled(bool enable);
    /// Set enabled state on self and child elements. Elements' own enabled state is remembered (IsEnabledSelf) and can be restored.
    void SetDeepEnabled(bool enable);
    /// Reset enabled state to the element's remembered state prior to calling SetDeepEnabled.
    void ResetDeepEnabled();
    /// Set enabled state on self and child elements. Unlike SetDeepEnabled this does not remember the elements' own enabled state, but overwrites it.
    void SetEnabledRecursive(bool enable);
    /// Set whether value is editable through input. Not applicable to all elements. Default true.
    void SetEditable(bool enable);
    /// Set whether is focused. Only one element can be focused at a time.
    void SetFocus(bool enable);
    /// Set selected mode. Actual meaning is element dependent, for example constant hover or pressed effect.
    void SetSelected(bool enable);
    /// Set whether is visible. Visibility propagates to child elements.
    void SetVisible(bool enable);
    /// Set focus mode.
    void SetFocusMode(FocusMode mode);
    /// Set drag and drop flags.
    void SetDragDropMode(unsigned mode);
    /// Set style from an XML file. Find the style element by name. If the style file is not explicitly provided, use the default style from parental chain. Return true if the style is applied successfully.
    bool SetStyle(const String& styleName, XMLFile* file = 0);
    /// Set style from an XML element. Return true if the style is applied successfully.
    bool SetStyle(const XMLElement& element);
    /// Set style from an XML file. Find the style element automatically. If the style file is not explicitly provided, use the default style from parental chain. Return true if the style is applied successfully.
    bool SetStyleAuto(XMLFile* file = 0);
    /// Set default style file for later use by children elements.
    void SetDefaultStyle(XMLFile* style);
    /// Set layout.
    void SetLayout(LayoutMode mode, int spacing = 0, const IntRect& border = IntRect::ZERO);
    /// Set layout mode only.
    void SetLayoutMode(LayoutMode mode);
    /// Set layout spacing.
    void SetLayoutSpacing(int spacing);
    /// Set layout border.
    void SetLayoutBorder(const IntRect& border);
    /// Set layout flex scale.
    void SetLayoutFlexScale(const Vector2& scale);
    /// Set horizontal indentation.
    void SetIndent(int indent);
    /// Set indent spacing (number of pixels per indentation level).
    void SetIndentSpacing(int indentSpacing);
    /// Manually update layout. Should not be necessary in most cases, but is provided for completeness.
    void UpdateLayout();
    /// Disable automatic layout update. Should only be used if there are performance problems.
    void DisableLayoutUpdate();
    /// Enable automatic layout update.
    void EnableLayoutUpdate();
    /// Bring UI element to front.
    void BringToFront();
    /// Create and add a child element and return it.
    UIElement* CreateChild(StringHash type, const String& name = String::EMPTY, unsigned index = M_MAX_UNSIGNED);
    /// Add a child element.
    void AddChild(UIElement* element);
    /// Insert a child element into a specific position in the child list.
    void InsertChild(unsigned index, UIElement* element);
    /// Remove a child element. Starting search at specified index if provided.
    void RemoveChild(UIElement* element, unsigned index = 0);
    /// Remove a child element at index.
    void RemoveChildAtIndex(unsigned index);
    /// Remove all child elements.
    void RemoveAllChildren();
    /// Remove from the parent element. If no other shared pointer references exist, causes immediate deletion.
    void Remove();
    /// Find child index. Return M_MAX_UNSIGNED if not found.
    unsigned FindChild(UIElement* element) const;
    /// Set parent element. Same as parent->InsertChild(index, this).
    void SetParent(UIElement* parent, unsigned index = M_MAX_UNSIGNED);
    /// Set a user variable.
    void SetVar(StringHash key, const Variant& value);
    /// Mark as internally (programmatically) created. Used when an element composes itself out of child elements.
    void SetInternal(bool enable);
    /// Set traversal mode for rendering. The default traversal mode is TM_BREADTH_FIRST for non-root element. Root element should be set to TM_DEPTH_FIRST to avoid artifacts during rendering.
    void SetTraversalMode(TraversalMode traversalMode);
    /// Set element event sender flag. When child element is added or deleted, the event would be sent using UIElement found in the parental chain having this flag set. If not set, the event is sent using UI's root as per normal.
    void SetElementEventSender(bool flag);

    /// Set tags. Old tags are overwritten.
    void SetTags(const StringVector& tags);
    /// Add a tag.
    void AddTag(const String& tag);
    /// Add tags with the specified separator, by default ;
    void AddTags(const String& tags, char separator = ';');
    /// Add tags.
    void AddTags(const StringVector& tags);
    // Remove specific tag. Return true if existed.
    bool RemoveTag(const String& tag);
    // Remove all tags.
    void RemoveAllTags();

    /// Template version of creating a child element.
    template <class T> T* CreateChild(const String& name = String::EMPTY, unsigned index = M_MAX_UNSIGNED);

    /// Return name.
    const String& GetName() const { return name_; }

    /// Return position.
    const IntVector2& GetPosition() const { return position_; }

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

    /// Return true if size is fixed.
    bool IsFixedSize() const { return minSize_ == maxSize_; }

    /// Return true if width is fixed.
    bool IsFixedWidth() const { return minSize_.x_ == maxSize_.x_; }

    /// Return true if height is fixed.
    bool IsFixedHeight() const { return minSize_.y_ == maxSize_.y_; }

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

    /// Return derived opacity (affected by parent elements.) If UseDerivedOpacity is false, returns same as element's own opacity.
    float GetDerivedOpacity() const;

    /// Return whether should be brought to front when focused.
    bool GetBringToFront() const { return bringToFront_; }

    /// Return whether should be put to background when another element is focused.
    bool GetBringToBack() const { return bringToBack_; }

    /// Return whether should clip child elements.
    bool GetClipChildren() const { return clipChildren_; }

    /// Return whether should sort child elements according to priority.
    bool GetSortChildren() const { return sortChildren_; }

    /// Return whether parent elements' opacity affects opacity.
    bool GetUseDerivedOpacity() const { return useDerivedOpacity_; }

    /// Return whether has focus.
    bool HasFocus() const;

    /// Return whether reacts to input.
    bool IsEnabled() const { return enabled_; }

    /// Returns the element's last own enabled state. May be different than the value returned by IsEnabled when SetDeepEnabled has been used.
    bool IsEnabledSelf() const { return enabledPrev_; }

    /// Return whether value is editable through input.
    bool IsEditable() const { return editable_; }

    /// Return whether is selected. Actual meaning is element dependent.
    bool IsSelected() const { return selected_; }

    /// Return whether element itself should be visible. Elements can be also hidden due to the parent being not visible, use IsVisibleEffective() to check.
    bool IsVisible() const { return visible_; }
    
    /// Return whether element is effectively visible (parent element chain is visible.)
    bool IsVisibleEffective() const;

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

    /// Return applied style name. Return an empty string when the applied style is an 'auto' style (i.e. style derived from instance's type).
    const String& GetAppliedStyle() const;
    /// Return default style.
    XMLFile* GetDefaultStyle(bool recursiveUp = true) const;

    /// Return layout mode.
    LayoutMode GetLayoutMode() const { return layoutMode_; }

    /// Return layout spacing.
    int GetLayoutSpacing() const { return layoutSpacing_; }

    /// Return layout border.
    const IntRect& GetLayoutBorder() const { return layoutBorder_; }

    /// Return layout flex scale.
    const Vector2& GetLayoutFlexScale() const { return layoutFlexScale_; }

    /// Return number of child elements.
    unsigned GetNumChildren(bool recursive = false) const;
    /// Return child element by index.
    UIElement* GetChild(unsigned index) const;
    /// Return child element by name.
    UIElement* GetChild(const String& name, bool recursive = false) const;
    /// Return child element by variable. If only key is provided, return the first child having the matching variable key. If value is also provided then the actual variable value would also be checked against.
    UIElement* GetChild(const StringHash& key, const Variant& value = Variant::EMPTY, bool recursive = false) const;

    /// Return immediate child elements.
    const Vector<SharedPtr<UIElement> >& GetChildren() const { return children_; }

    /// Return child elements either recursively or non-recursively.
    void GetChildren(PODVector<UIElement*>& dest, bool recursive = false) const;

    /// Return parent element.
    UIElement* GetParent() const { return parent_; }

    /// Return root element.
    UIElement* GetRoot() const;
    /// Return derived color. Only valid when no gradient.
    const Color& GetDerivedColor() const;
    /// Return a user variable.
    const Variant& GetVar(const StringHash& key) const;

    /// Return all user variables.
    const VariantMap& GetVars() const { return vars_; }

    /// Return whether element is tagged by a specific tag.
    bool HasTag(const String& tag) const;

    /// Return all tags.
    const StringVector& GetTags() const { return tags_; }

    /// Return child elements with a specific tag either recursively or non-recursively.
    void GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive = false) const;

    /// Return the drag button combo if this element is being dragged.
    int GetDragButtonCombo() const { return dragButtonCombo_; }

    /// Return the number of buttons dragging this element.
    unsigned GetDragButtonCount() const { return dragButtonCount_; }

    /// Return whether a point (either in element or screen coordinates) is inside the element.
    bool IsInside(IntVector2 position, bool isScreen);
    /// Return whether a point (either in element or screen coordinates) is inside the combined rect of the element and its children.
    bool IsInsideCombined(IntVector2 position, bool isScreen);
    /// Return combined screen coordinate rect of element and its children.
    IntRect GetCombinedScreenRect();
    /// Sort child elements if sorting enabled and order dirty. Called by UI.
    void SortChildren();

    /// Return maximum layout element size in the layout direction. Only valid after layout has been calculated. Used internally by UI for optimizations.
    int GetLayoutElementMaxSize() const { return layoutElementMaxSize_; }

    /// Return horizontal indentation.
    int GetIndent() const { return indent_; }

    /// Return indent spacing (number of pixels per indentation level).
    int GetIndentSpacing() const { return indentSpacing_; }

    /// Return indent width in pixels.
    int GetIndentWidth() const { return indent_ * indentSpacing_; }

    /// Set child offset.
    void SetChildOffset(const IntVector2& offset);
    /// Set hovering state.
    void SetHovering(bool enable);
    /// Adjust scissor for rendering.
    void AdjustScissor(IntRect& currentScissor);
    /// Get UI rendering batches with a specified offset. Also recurse to child elements.
    void GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor);

    /// Return color attribute. Uses just the top-left color.
    const Color& GetColorAttr() const { return color_[0]; }

    /// Return traversal mode for rendering.
    TraversalMode GetTraversalMode() const { return traversalMode_; }

    /// Return whether element should send child added / removed events by itself. If false, defers to parent element.
    bool IsElementEventSender() const { return elementEventSender_; }

    /// Get element which should send child added / removed events.
    UIElement* GetElementEventSender() const;

    /// Return effective minimum size, also considering layout. Used internally.
    IntVector2 GetEffectiveMinSize() const;
    
protected:
    /// Handle attribute animation added.
    virtual void OnAttributeAnimationAdded();
    /// Handle attribute animation removed.
    virtual void OnAttributeAnimationRemoved();
    /// Find target of an attribute animation from object hierarchy by name.
    virtual Animatable* FindAttributeAnimationTarget(const String& name, String& outName);
    /// Mark screen position as needing an update.
    void MarkDirty();
    /// Remove child XML element by matching attribute name.
    bool RemoveChildXML(XMLElement& parent, const String& name) const;
    /// Remove child XML element by matching attribute name and value.
    bool RemoveChildXML(XMLElement& parent, const String& name, const String& value) const;
    /// Filter UI-style attributes in serialization process.
    bool FilterUIStyleAttributes(XMLElement& dest, const XMLElement& styleElem) const;
    /// Filter implicit attributes in serialization process.
    virtual bool FilterImplicitAttributes(XMLElement& dest) const;

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
    /// Sort children according to priority flag.
    bool sortChildren_;
    /// Use derived opacity flag.
    bool useDerivedOpacity_;
    /// Input enabled flag.
    bool enabled_;
    /// Last SetEnabled flag before any SetDeepEnabled.
    bool enabledPrev_;
    /// Value editable flag.
    bool editable_;
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
    /// Layout flex scale.
    Vector2 layoutFlexScale_;
    /// Resize nesting level to prevent multiple events and endless loop.
    unsigned resizeNestingLevel_;
    /// Layout update nesting level to prevent endless loop.
    unsigned layoutNestingLevel_;
    /// Layout element maximum size in layout direction.
    int layoutElementMaxSize_;
    /// Horizontal indentation.
    int indent_;
    /// Indent spacing (number of pixels per indentation level).
    int indentSpacing_;
    /// Position.
    IntVector2 position_;
    /// Screen position.
    mutable IntVector2 screenPosition_;
    /// Screen position dirty flag.
    mutable bool positionDirty_;
    /// Applied style.
    String appliedStyle_;
    /// Drag button combo.
    int dragButtonCombo_;
    /// Drag button count.
    unsigned dragButtonCount_;

private:
    /// Return child elements recursively.
    void GetChildrenRecursive(PODVector<UIElement*>& dest) const;
    /// Return child elements with a specific tag recursively.
    void GetChildrenWithTagRecursive(PODVector<UIElement*>& dest, const String& tag) const;
    /// Recursively apply style to a child element hierarchy when adding to an element.
    void ApplyStyleRecursive(UIElement* element);
    /// Calculate layout width for resizing the parent element.
    int CalculateLayoutParentSize(const PODVector<int>& sizes, int begin, int end, int spacing);
    /// Calculate child widths/positions in the layout.
    void CalculateLayout
        (PODVector<int>& positions, PODVector<int>& sizes, const PODVector<int>& minSizes, const PODVector<int>& maxSizes,
            const PODVector<float>& flexScales, int targetWidth, int begin, int end, int spacing);
    /// Get child element constant position in a layout.
    IntVector2 GetLayoutChildPosition(UIElement* child);
    /// Detach from parent.
    void Detach();
    /// Verify that child elements have proper alignment for layout mode.
    void VerifyChildAlignment();
    /// Handle logic post-update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Size.
    IntVector2 size_;
    /// Minimum size.
    IntVector2 minSize_;
    /// Maximum size.
    IntVector2 maxSize_;
    /// Child elements' offset. Used internally.
    IntVector2 childOffset_;
    /// Parent's minimum size calculated by layout. Used internally.
    IntVector2 layoutMinSize_;
    /// Horizontal alignment.
    HorizontalAlignment horizontalAlignment_;
    /// Vertical alignment.
    VerticalAlignment verticalAlignment_;
    /// Opacity.
    float opacity_;
    /// Derived opacity.
    mutable float derivedOpacity_;
    /// Derived color. Only valid when no gradient.
    mutable Color derivedColor_;
    /// Derived opacity dirty flag.
    mutable bool opacityDirty_;
    /// Derived color dirty flag (only used when no gradient.)
    mutable bool derivedColorDirty_;
    /// Child priority sorting dirty flag.
    bool sortOrderDirty_;
    /// Has color gradient flag.
    bool colorGradient_;
    /// Default style file.
    SharedPtr<XMLFile> defaultStyle_;
    /// Last applied style file.
    WeakPtr<XMLFile> appliedStyleFile_;
    /// Traversal mode for rendering.
    TraversalMode traversalMode_;
    /// Flag whether node should send child added / removed events by itself.
    bool elementEventSender_;
    /// XPath query for selecting UI-style.
    static XPathQuery styleXPathQuery_;
    /// Tag list.
    StringVector tags_;
};

template <class T> T* UIElement::CreateChild(const String& name, unsigned index)
{
    return static_cast<T*>(CreateChild(T::GetTypeStatic(), name, index));
}

}
