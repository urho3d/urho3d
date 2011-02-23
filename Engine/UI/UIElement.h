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

#ifndef UI_UIELEMENT_H
#define UI_UIELEMENT_H

#include "EventListener.h"
#include "HashedType.h"
#include "SharedPtr.h"
#include "UIBatch.h"
#include "Vector2.h"
#include "XMLFile.h"

//! UI element horizontal alignment
enum HorizontalAlignment
{
    HA_LEFT = 0,
    HA_CENTER,
    HA_RIGHT
};

//! UI element vertical alignment
enum VerticalAlignment
{
    VA_TOP = 0,
    VA_CENTER,
    VA_BOTTOM
};

//! UI element corners
enum Corner
{
    C_TOPLEFT = 0,
    C_TOPRIGHT,
    C_BOTTOMLEFT,
    C_BOTTOMRIGHT,
    MAX_UIELEMENT_CORNERS
};

//! UI element orientation
enum Orientation
{
    O_HORIZONTAL = 0,
    O_VERTICAL
};

//! UI element focus mode
enum FocusMode
{
    //! Is not focusable and does not affect existing focus
    FM_NOTFOCUSABLE = 0,
    //! Resets focus when clicked
    FM_RESETFOCUS,
    //! Is focusable
    FM_FOCUSABLE,
    //! Is focusable and also defocusable by pressing ESC
    FM_FOCUSABLE_DEFOCUSABLE
};

//! Layout operation mode
enum LayoutMode
{
    //! No layout operations will be performed
    LM_FREE = 0,
    //! Layout child elements horizontally and resize them to fit. Resize element if necessary
    LM_HORIZONTAL,
    //! Layout child elements vertically and resize them to fit. Resize element if necessary
    LM_VERTICAL
};

//! Drag and drop disabled
static const unsigned DD_DISABLED = 0;
//! Drag and drop source flag
static const unsigned DD_SOURCE = 1;
//! Drag and drop target flag
static const unsigned DD_TARGET = 2;

class ResourceCache;

//! Base class for UI elements
class UIElement : public HashedType, public EventListener
{
    DEFINE_TYPE(Element);
    
public:
    //! Construct with name
    UIElement(const std::string& name = std::string());
    //! Destruct with name
    virtual ~UIElement();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    
    //! React to mouse hover
    virtual void onHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers);
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers);
    //! React to mouse drag start
    virtual void onDragStart(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers);
    //! React to mouse drag motion
    virtual void onDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers);
    //! React to mouse drag end
    virtual void onDragEnd(const IntVector2& position, const IntVector2& screenPosition);
    //! React to drag and drop finish
    virtual void onDrop(UIElement* element);
    //! React to mouse wheel
    virtual void onWheel(int delta, int buttons, int qualifiers);
    //! React to a key press
    virtual void onKey(int key, int buttons, int qualifiers);
    //! React to a key press translated to a character
    virtual void onChar(unsigned char c, int buttons, int qualifiers);
    //! React to resize
    virtual void onResize();
    //! React to gaining focus
    virtual void onFocus();
    //! React to losing focus
    virtual void onDefocus();
    
    //! Set name
    void setName(const std::string& name);
    //! Set position
    void setPosition(const IntVector2& position);
    //! Set position
    void setPosition(int x, int y);
    //! Set size
    void setSize(const IntVector2& size);
    //! Set size
    void setSize(int width, int height);
    //! Set width only
    void setWidth(int width);
    //! Set height only
    void setHeight(int height);
    //! Set minimum size
    void setMinSize(const IntVector2& minSize);
    //! Set minimum size
    void setMinSize(int width, int height);
    //! Set minimum width
    void setMinWidth(int width);
    //! Set minimum height
    void setMinHeight(int height);
    //! Set maximum size
    void setMaxSize(const IntVector2& maxSize);
    //! Set maximum size
    void setMaxSize(int width, int height);
    //! Set maximum width
    void setMaxWidth(int width);
    //! Set maximum height
    void setMaxHeight(int height);
    //! Set fixed size
    void setFixedSize(const IntVector2& size);
    //! Set fixed size
    void setFixedSize(int width, int height);
    //! Set fixed width
    void setFixedWidth(int width);
    //! Set fixed height
    void setFixedHeight(int height);
    //! Set horizontal and vertical alignment
    void setAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign);
    //! Set horizontal alignment
    void setHorizontalAlignment(HorizontalAlignment align);
    //! Set vertical alignment
    void setVerticalAlignment(VerticalAlignment align);
    //! Set child element clipping border
    void setClipBorder(const IntRect& rect);
    //! Set child element clipping border
    void setClipBorder(int left, int top, int right, int bottom);
    //! Set color on all corners
    void setColor(const Color& color);
    //! Set color on one corner
    void setColor(Corner corner, const Color& color);
    //! Set priority
    void setPriority(int priority);
    //! Set opacity
    void setOpacity(float opacity);
    //! Set whether should be brought to front when focused
    void setBringToFront(bool enable);
    //! Set whether should be put to background when another element is focused
    void setBringToBack(bool enable);
    //! Set whether should clip child elements
    void setClipChildren(bool enable);
    //! Set whether reacts to input
    void setEnabled(bool enable);
    //! Set focus mode
    void setFocusMode(FocusMode mode);
    //! Set whether is focused. Usually called by UI
    void setFocus(bool enable);
    //! Set selected mode. Actual meaning is element dependent, for example constant hover or pressed effect
    void setSelected(bool enable);
    //! Set whether is visible
    void setVisible(bool enable);
    //! Set drag and drop flags
    void setDragDropMode(unsigned mode);
    //! Set userdata
    void setUserData(const VariantMap& userData);
    //! Set style from an XML file. Find the style element automatically
    void setStyleAuto(XMLFile* file, ResourceCache* cache);
    //! Set layout
    void setLayout(LayoutMode mode, int spacing = 0, const IntRect& border = IntRect::sZero);
    //! Set layout spacing
    void setLayoutSpacing(int spacing);
    //! Set layout border
    void setLayoutBorder(const IntRect& border);
    //! Manually update layout. Should not be necessary in most cases, but is provided for completeness
    void updateLayout();
    //! Disable layout update momentarily, usually for performance reasons when adding several child elements
    void disableLayoutUpdate();
    //! Enable layout update
    void enableLayoutUpdate();
    //! Bring UI element to front
    void bringToFront();
    //! Add a child element
    void addChild(UIElement* element);
    //! Remove a child element
    void removeChild(UIElement* element);
    //! Remove all child elements
    void removeAllChildren();
    
    //! Return name
    const std::string& getName() const { return mName; }
    //! Return position
    const IntVector2& getPosition() const { return mPosition; }
    //! Return screen position
    IntVector2 getScreenPosition();
    //! Return size
    const IntVector2& getSize() const { return mSize; }
    //! Return width
    int getWidth() const { return mSize.mX; }
    //! Return height
    int getHeight() const { return mSize.mY; }
    //! Return minimum size
    const IntVector2& getMinSize() const { return mMinSize; }
    //! Return minimum width
    int getMinWidth() const { return mMinSize.mX; }
    //! Return minimum height
    int getMinHeight() const { return mMinSize.mY; }
    //! Return maximum size
    const IntVector2& getMaxSize() const { return mMaxSize; }
    //! Return minimum width
    int getMaxWidth() const { return mMaxSize.mX; }
    //! Return minimum height
    int getMaxHeight() const { return mMaxSize.mY; }
    //! Return child element offset
    const IntVector2& getChildOffset() const { return mChildOffset; }
    //! Return horizontal alignment
    HorizontalAlignment getHorizontalAlignment() const { return mHorizontalAlignment; }
    //! Return vertical alignment
    VerticalAlignment getVerticalAlignment() const { return mVerticalAlignment; }
    //! Return child element clipping border
    const IntRect& getClipBorder() const { return mClipBorder; }
    //! Return corner color
    const Color& getColor(Corner corner) const { return mColor[corner]; }
    //! Return priority
    int getPriority() const { return mPriority; }
    //! Return opacity
    float getOpacity() const { return mOpacity; }
    //! Return derived opacity (affected by parent elements)
    float getDerivedOpacity();
    //! Return whether should be brought to front when focused
    bool getBringToFront() const { return mBringToFront; }
    //! Return whether should be put to background when another element is focused
    bool getBringToBack() const { return mBringToBack; }
    //! Return whether should clip child elements
    bool getClipChildren() const { return mClipChildren; }
    //! Return whether reacts to input
    bool isEnabled() const { return mEnabled; }
    //! Return focus mode
    FocusMode getFocusMode() const { return mFocusMode; }
    //! Return whether has focus
    bool hasFocus() const { return mFocus; }
    //! Return whether is selected. Actual meaning is element dependent
    bool isSelected() const { return mSelected; }
    //! Return whether is visible
    bool isVisible() const { return mVisible; }
    //! Return whether the cursor is hovering on this element
    bool isHovering() const { return mHovering; }
    //! Return whether has different color in at least one corner
    bool hasColorGradient() const { return mHasColorGradient; }
    //! Return drag and drop flags
    unsigned getDragDropMode() const { return mDragDropMode; }
    //! Return userdata
    VariantMap& getUserData() { return mUserData; }
    //! Return layout mode
    LayoutMode getLayoutMode() const { return mLayoutMode; }
    //! Return layout spacing
    int getLayoutSpacing() const { return mLayoutSpacing; }
    //! Return layout border
    const IntRect& getLayoutBorder() const { return mLayoutBorder; }
    //! Return number of child elements
    unsigned getNumChildren(bool recursive = false) const;
    //! Return child element by index
    UIElement* getChild(unsigned index) const;
    //! Return child element by name
    UIElement* getChild(const std::string& name, bool recursive = false) const;
    //! Return all child elements
    std::vector<UIElement*> getChildren(bool recursive = false) const;
    //! Return parent element
    UIElement* getParent() const { return mParent; }
    //! Return origin element for popups
    UIElement* getOrigin() const { return mOrigin; }
    //! Return root element
    UIElement* getRootElement() const;
    //! Return first matching UI style element from an XML file. If not found, return empty
    XMLElement getStyleElement(XMLFile* file) const;
    
    //! Convert screen coordinates to element coordinates
    IntVector2 screenToElement(const IntVector2& screenPosition);
    //! Convert element coordinates to screen coordinates
    IntVector2 elementToScreen(const IntVector2& position);
    //! Return whether a point (either in element or screen coordinates) is inside the element
    bool isInside(IntVector2 position, bool isScreen);
    //! Return whether a point (either in element or screen coordinates) is inside the combined rect of element and its children
    bool isInsideCombined(IntVector2 position, bool isScreen);
    //! Return combined screen coordinate rect of element and its children
    IntRect getCombinedScreenRect();
    
    //! Set child offset
    void setChildOffset(const IntVector2& offset);
    //! Set hovering state
    void setHovering(bool enable);
    //! Set origin element
    void setOrigin(UIElement* origin);
    //! Adjust scissor for rendering
    void adjustScissor(IntRect& currentScissor);
    //! Get UI rendering batches with a specified offset. Also recurses to child elements
    void getBatchesWithOffset(IntVector2& offset, std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, IntRect
        currentScissor);
    
    //! Return first matching UI style element from an XML file, with freely specified type. If not found, return empty
    static XMLElement getStyleElement(XMLFile* file, const std::string& typeName);
    
protected:
    //! Mark screen position as needing an update
    void markDirty();
    
    //! Name
    std::string mName;
    //! Child elements
    std::vector<SharedPtr<UIElement> > mChildren;
    //! Parent element
    UIElement* mParent;
    //! Origin element
    UIElement* mOrigin;
    //! Child element clipping border
    IntRect mClipBorder;
    //! Colors
    Color mColor[MAX_UIELEMENT_CORNERS];
    //! Priority
    int mPriority;
    //! Bring to front when focused flag
    bool mBringToFront;
    //! Bring to back when defocused flag
    bool mBringToBack;
    //! Clip children flag
    bool mClipChildren;
    //! Reacts to input flag
    bool mEnabled;
    //! Focus mode
    FocusMode mFocusMode;
    //! Focused flag
    bool mFocus;
    //! Selected flag
    bool mSelected;
    //! Visible flag
    bool mVisible;
    //! Hovering flag
    bool mHovering;
    //! Drag and drop flags
    unsigned mDragDropMode;
    //! Userdata
    VariantMap mUserData;
    //! Layout mode
    LayoutMode mLayoutMode;
    //! Layout spacing
    int mLayoutSpacing;
    //! Layout borders
    IntRect mLayoutBorder;
    //! Resize nesting level to prevent multiple events and endless loop
    unsigned mResizeNestingLevel;
    //! Layout update nesting level to prevent endless loop
    unsigned mUpdateLayoutNestingLevel;
    
    //! Clipboard data
    static std::string sClipBoard;
    
private:
    //! Return child elements recursively
    void getChildrenRecursive(std::vector<UIElement*>& dest) const;
    //! Calculate layout width for resizing the parent element
    int calculateLayoutParentSize(const std::vector<int>& sizes, int begin, int end, int spacing);
    //! Calculate child widths/positions in the layout
    void calculateLayout(std::vector<int>& positions, std::vector<int>& sizes, const std::vector<int>& minSizes,
        const std::vector<int>& maxSizes, int targetWidth, int begin, int end, int spacing);
    //! Get child element constant position in a layout
    IntVector2 getLayoutChildPosition(UIElement* child);
    
    //! Position
    IntVector2 mPosition;
    //! Screen position
    IntVector2 mScreenPosition;
    //! Size
    IntVector2 mSize;
    //! Minimum size
    IntVector2 mMinSize;
    //! Maximum size
    IntVector2 mMaxSize;
    //! Child elements' offset. Used internally
    IntVector2 mChildOffset;
    //! Horizontal alignment
    HorizontalAlignment mHorizontalAlignment;
    //! Vertical alignment
    VerticalAlignment mVerticalAlignment;
    //! Opacity
    float mOpacity;
    //! Derived opacity
    float mDerivedOpacity;
    //! Screen position dirty flag
    bool mScreenPositionDirty;
    //! Derived opacity dirty flag
    bool mDerivedOpacityDirty;
    //! Has color gradient flag
    bool mHasColorGradient;
};

#endif // UI_UIELEMENT_H
