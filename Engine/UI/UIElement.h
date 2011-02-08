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
enum UIElementCorner
{
    C_TOPLEFT = 0,
    C_TOPRIGHT,
    C_BOTTOMLEFT,
    C_BOTTOMRIGHT,
    MAX_UIELEMENT_CORNERS
};

//! UI element orientation
enum UIElementOrientation
{
    O_HORIZONTAL = 0,
    O_VERTICAL
};

class ResourceCache;

//! Base class for UI elements
class UIElement : public HashedType, public EventListener
{
    DEFINE_TYPE(UIElement);
    
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
    //! Return UI element screen position
    virtual IntVector2 getScreenPosition();
    //! Return UI element opacity
    virtual float getDerivedOpacity();
    
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
    //! React to a key press
    virtual void onKey(int key, int buttons, int qualifiers);
    //! React to a key press translated to a character
    virtual void onChar(unsigned char c, int buttons, int qualifiers);
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
    //! Set width and height
    void setSize(const IntVector2& size);
    //! Set width and height
    void setSize(int width, int height);
    //! Set width
    void setWidth(int width);
    //! Set height
    void setHeight(int height);
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
    void setColor(UIElementCorner corner, const Color& color);
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
    //! Set whether can be focused
    void setFocusable(bool enable);
    //! Set whether can be defocused by pressing ESC
    void setDefocusable(bool enable);
    //! Set whether is focused. Usually called by UI
    void setFocus(bool enable);
    //! Set selected mode. Actual meaning is element dependent, but is visually same as a constant hover
    void setSelected(bool enable);
    //! Set whether is visible
    void setVisible(bool enable);
    //! Set userdata
    void setUserData(const Variant& userData);
    //! Set style from an XML file. Find the style element automatically
    void setStyleAuto(XMLFile* file, ResourceCache* cache);
    //! Bring UI element to front
    void bringToFront();
    //! Add a child element
    void addChild(UIElement* element);
    //! Remove a child element
    void removeChild(UIElement* element);
    //! Remove all child elements
    void removeAllChildren();
    //! Layout child elements horizontally. Expand/contract the element optionally
    void layoutHorizontal(int spacing = 0, const IntRect& border = IntRect::sZero, bool expand = true, bool contract = true);
    //! Layout child elements vertically. Expand/contract the element optionally
    void layoutVertical(int spacing = 0, const IntRect& border = IntRect::sZero, bool expand = true, bool contract = true);
    
    //! Return name
    const std::string& getName() const { return mName; }
    //! Return position
    const IntVector2& getPosition() const { return mPosition; }
    //! Return size
    const IntVector2& getSize() const { return mSize; }
    //! Return width
    int getWidth() const { return mSize.mX; }
    //! Return height
    int getHeight() const { return mSize.mY; }
    //! Return child element offset
    const IntVector2& getChildOffset() const { return mChildOffset; }
    //! Return horizontal alignment
    HorizontalAlignment getHorizontalAlignment() const { return mHorizontalAlignment; }
    //! Return vertical alignment
    VerticalAlignment getVerticalAlignment() const { return mVerticalAlignment; }
    //! Return child element clipping border
    const IntRect& getClipBorder() const { return mClipBorder; }
    //! Return corner color
    const Color& getColor(UIElementCorner corner) const { return mColor[corner]; }
    //! Return priority
    int getPriority() const { return mPriority; }
    //! Return opacity
    float getOpacity() const { return mOpacity; }
    //! Return whether should be brought to front when focused
    bool getBringToFront() const { return mBringToFront; }
    //! Return whether should be put to background when another element is focused
    bool getBringToBack() const { return mBringToBack; }
    //! Return whether should clip child elements
    bool getClipChildren() const { return mClipChildren; }
    //! Return whether reacts to input
    bool isEnabled() const { return mEnabled; }
    //! Return whether can be focused
    bool isFocusable() const { return mFocusable; }
    //! Return whether can be defocused with ESC
    bool isDefocusable() const { return mDefocusable; }
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
    //! Return userdata
    Variant getUserData() const { return mUserData; }
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
    
    //! Set hovering state
    void setHovering(bool enable);
    //! Set origin element
    void setOrigin(UIElement* origin);
    //! Adjust scissor for rendering
    void adjustScissor(IntRect& currentScissor);
    
    //! Return first matching UI style element from an XML file, with freely specified type. If not found, return empty
    static XMLElement getStyleElement(XMLFile* file, const std::string& typeName);
    
protected:
    //! Mark screen position as needing an update
    void markDirty();
    //! Set child offset
    void setChildOffset(const IntVector2& offset);
    
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
    //! Focusable flag
    bool mFocusable;
    //! Defocusable flag
    bool mDefocusable;
    //! Focused flag
    bool mFocus;
    //! Selected flag
    bool mSelected;
    //! Visible flag
    bool mVisible;
    //! Hovering flag
    bool mHovering;
    //! Userdata
    Variant mUserData;
    
    //! Clipboard data
    static std::string sClipBoard;
    
private:
    //! Return child elements recursively
    void getChildrenRecursive(std::vector<UIElement*>& dest) const;
    //! Adjust size after laying out the child elements
    void adjustSize(const IntVector2& neededSize, bool expand, bool contract);
    
    //! Position
    IntVector2 mPosition;
    //! Screen position
    IntVector2 mScreenPosition;
    //! Size
    IntVector2 mSize;
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
