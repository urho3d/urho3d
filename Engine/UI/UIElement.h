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
    C_BOTTOMRIGHT
};

static const unsigned NUM_UIELEMENT_CORNERS = 4;

class ResourceCache;

//! Base class for UI elements
class UIElement : public RefCounted, public EventListener
{
public:
    //! Construct with name
    UIElement(const std::string& name = std::string());
    //! Destruct with name
    virtual ~UIElement();
    
    //! Load parameters from an XML file
    virtual XMLElement loadParameters(XMLFile* file, const std::string& elementName, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    //! Return UI element screen position
    virtual IntVector2 getScreenPosition();
    //! Return UI element opacity
    virtual float getDerivedOpacity();
    
    //! React to mouse hover
    virtual void onHover(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag start
    virtual void onDragStart(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag motion
    virtual void onDragMove(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag end
    virtual void onDragEnd(const IntVector2& position, const IntVector2& screenPosition);
    //! React to a character typed on keyboard
    virtual void onChar(unsigned key);
    
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
    //! Set color on all corners
    void setColor(const Color& color);
    //! Set color on one corner
    void setColor(UIElementCorner corner, const Color& color);
    //! Set hover color modification
    void setHoverColor(const Color& color);
    //! Set priority
    void setPriority(int priority);
    //! Set opacity
    void setOpacity(float opacity);
    //! Set whether should be brought to front when focused
    void setBringToFront(bool enable);
    //! Set whether should clip child elements
    void setClipChildren(bool enable);
    //! Set whether reacts to input
    void setEnabled(bool enable);
    //! Set whether can be focused
    void setFocusable(bool enable);
    //! Set whether is focused. Usually called by UI
    void setFocus(bool enable);
    //! Set whether is visible
    void setVisible(bool enable);
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
    //! Return size
    const IntVector2& getSize() const { return mSize; }
    //! Return width
    int getWidth() const { return mSize.mX; }
    //! Return height
    int getHeight() const { return mSize.mY; }
    //! Return horizontal alignment
    HorizontalAlignment getHorizontalAlignment() const { return mHorizontalAlignment; }
    //! Return vertical alignment
    VerticalAlignment getVerticalAlignment() const { return mVerticalAlignment; }
    //! Return corner color
    const Color& getColor(UIElementCorner corner) const { return mColor[corner]; }
    //! Return hover color modification
    const Color& getHoverColor() { return mHoverColor; }
    //! Return priority
    int getPriority() const { return mPriority; }
    //! Return opacity
    float getOpacity() const { return mOpacity; }
    //! Return whether should be brought to front when focused
    bool getBringToFront() const { return mBringToFront; }
    //! Return whether should clip children
    bool getClipChildren() const { return mClipChildren; }
    //! Return whether reacts to input
    bool isEnabled() const { return mEnabled; }
    //! Return whether can be focused
    bool isFocusable() const { return mFocusable; }
    //! Return whether has focus
    bool hasFocus() const { return mFocus; }
    //! Return whether is visible
    bool isVisible() const { return mVisible; }
    //! Return whether the cursor is hovering on this element
    bool isHovering() const { return mHovering; }
    //! Return whether has different color in at least one corner
    bool hasColorGradient() const { return mHasColorGradient; }
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
    
    //! Convert screen coordinates to element coordinates
    IntVector2 screenToElement(const IntVector2& screenPosition);
    //! Convert element coordinates to screen coordinates
    IntVector2 elementToScreen(const IntVector2& position);
    
    //! Adjust scissor for rendering
    void adjustScissor(IntRect& currentScissor);
    
protected:
    //! Mark screen position as needing an update
    void markDirty();
    
    //! Name
    std::string mName;
    //! Child elements
    std::vector<SharedPtr<UIElement> > mChildren;
    //! Parent element
    UIElement* mParent;
    //! Colors
    Color mColor[NUM_UIELEMENT_CORNERS];
    //! Hover color modification
    Color mHoverColor;
    //! Priority
    int mPriority;
    //! Bring to front when focused flag
    bool mBringToFront;
    //! Clip children flag
    bool mClipChildren;
    //! Reacts to input flag
    bool mEnabled;
    //! Focusable flag
    bool mFocusable;
    //! Focused flag
    bool mFocus;
    //! Visible flag
    bool mVisible;
    //! Hovering flag
    bool mHovering;
    
private:
    //! Return child elements recursively
    void getChildrenRecursive(std::vector<UIElement*>& dest) const;
    
    //! Position
    IntVector2 mPosition;
    //! Screen position
    IntVector2 mScreenPosition;
    //! Size
    IntVector2 mSize;
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
