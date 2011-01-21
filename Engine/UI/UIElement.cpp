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
#include "Log.h"
#include "ResourceCache.h"
#include "UIElement.h"
#include "UIEvents.h"

#include "DebugNew.h"

UIElement::UIElement(const std::string& name) :
    mName(name),
    mParent(0),
    mClipBorder(IntRect::sZero),
    mHoverColor(Color(0.0f, 0.0f, 0.0f)),
    mPriority(0),
    mOpacity(1.0f),
    mBringToFront(false),
    mClipChildren(false),
    mEnabled(false),
    mFocusable(false),
    mFocus(false),
    mVisible(true),
    mHovering(false),
    mPosition(IntVector2::sZero),
    mSize(IntVector2::sZero),
    mChildOffset(IntVector2::sZero),
    mHorizontalAlignment(HA_LEFT),
    mVerticalAlignment(VA_TOP),
    mScreenPositionDirty(true),
    mDerivedOpacityDirty(true),
    mHasColorGradient(false)
{
}

UIElement::~UIElement()
{
    // If child elements have outside references, detach them
    while (mChildren.size())
    {
        const SharedPtr<UIElement>& element = mChildren.back();
        if (element.getRefCount() > 1)
        {
            element->mParent = 0;
            element->markDirty();
        }
        mChildren.pop_back();
    }
}

void UIElement::setStyle(const XMLElement& element, ResourceCache* cache)
{
    if (!cache)
        EXCEPTION("Null resource cache for UI element");
    
    if (element.hasAttribute("name"))
        mName = element.getString("name");
    if (element.hasChildElement("position"))
        setPosition(element.getChildElement("position").getIntVector2("value"));
    if (element.hasChildElement("size"))
        setSize(element.getChildElement("size").getIntVector2("value"));
    if (element.hasChildElement("alignment"))
    {
        XMLElement alignElem = element.getChildElement("alignment");
        
        std::string horiz;
        std::string vert;
        if (alignElem.hasAttribute("h"))
            horiz = alignElem.getStringLower("h");
        if (alignElem.hasAttribute("v"))
            vert = alignElem.getStringLower("v");
        if (alignElem.hasAttribute("horizontal"))
            horiz = alignElem.getStringLower("horizontal");
        if (alignElem.hasAttribute("vertical"))
            vert = alignElem.getStringLower("vertical");
        if (horiz == "left")
            setHorizontalAlignment(HA_LEFT);
        if (horiz == "center")
            setHorizontalAlignment(HA_CENTER);
        if (horiz == "right")
            setHorizontalAlignment(HA_RIGHT);
        if (vert == "top")
            setVerticalAlignment(VA_TOP);
        if (vert == "center")
            setVerticalAlignment(VA_CENTER);
        if (vert == "bottom")
            setVerticalAlignment(VA_BOTTOM);
    }
    if (element.hasChildElement("clipborder"))
        setClipBorder(element.getChildElement("clipborder").getIntRect("value"));
    if (element.hasChildElement("priority"))
        setPriority(element.getChildElement("priority").getInt("value"));
    if (element.hasChildElement("opacity"))
        setOpacity(element.getChildElement("opacity").getFloat("value"));
    if (element.hasChildElement("color"))
    {
        XMLElement colorElem = element.getChildElement("color");
        if (colorElem.hasAttribute("value"))
            setColor(colorElem.getColor("value"));
        if (colorElem.hasAttribute("topleft"))
            setColor(C_TOPLEFT, colorElem.getColor("topleft"));
        if (colorElem.hasAttribute("topright"))
            setColor(C_TOPRIGHT, colorElem.getColor("topright"));
        if (colorElem.hasAttribute("bottomleft"))
            setColor(C_BOTTOMLEFT, colorElem.getColor("bottomleft"));
        if (colorElem.hasAttribute("bottomright"))
            setColor(C_BOTTOMRIGHT, colorElem.getColor("bottomright"));
    }
    if (element.hasChildElement("hovercolor"))
        setHoverColor(element.getChildElement("hovercolor").getColor("value"));
    if (element.hasChildElement("bringtofront"))
        setBringToFront(element.getChildElement("bringtofront").getBool("enable"));
    if (element.hasChildElement("clipchildren"))
        setClipChildren(element.getChildElement("clipchildren").getBool("enable"));
    if (element.hasChildElement("enabled"))
        setEnabled(element.getChildElement("enabled").getBool("enable"));
    if (element.hasChildElement("focusable"))
        setFocusable(element.getChildElement("focusable").getBool("enable"));
    if (element.hasChildElement("visible"))
        setVisible(element.getChildElement("visible").getBool("enable"));
}

void UIElement::update(float timeStep)
{
}

void UIElement::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    // Reset hovering for next frame
    mHovering = false;
}

IntVector2 UIElement::getScreenPosition()
{
    if (mScreenPositionDirty)
    {
        IntVector2 pos = mPosition;
        const UIElement* parent = mParent;
        const UIElement* current = this;
        
        while (parent)
        {
            switch (current->mHorizontalAlignment)
            {
            case HA_LEFT:
                pos.mX += parent->mPosition.mX;
                break;
                
            case HA_CENTER:
                pos.mX += parent->mPosition.mX + parent->mSize.mX / 2 - current->mSize.mX / 2;
                break;
                
            case HA_RIGHT:
                pos.mX += parent->mPosition.mX + parent->mSize.mX - current->mSize.mX;
                break;
            }
            switch (current->mVerticalAlignment)
            {
            case VA_TOP:
                pos.mY += parent->mPosition.mY;
                break;
                
            case VA_CENTER:
                pos.mY += parent->mPosition.mY + parent->mSize.mY / 2 - current->mSize.mY / 2;
                break;
                
            case VA_BOTTOM:
                pos.mY += parent->mPosition.mY + parent->mSize.mY - current->mSize.mY;
                break;
            }
            
            pos += parent->mChildOffset;
            
            current = parent;
            parent = parent->mParent;
        }
        
        mScreenPosition = pos;
        mScreenPositionDirty = false;
    }
    
    return mScreenPosition;
}

float UIElement::getDerivedOpacity()
{
    if (mDerivedOpacityDirty)
    {
        float opacity = mOpacity;
        const UIElement* parent = mParent;
        
        while (parent)
        {
            opacity *= parent->mOpacity;
            parent = parent->mParent;
        }
        
        mDerivedOpacity = opacity;
        mDerivedOpacityDirty = false;
    }
    
    return mDerivedOpacity;
}

void UIElement::onChar(unsigned key)
{
}

void UIElement::onHover(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
    mHovering = true;
}

void UIElement::onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
}

void UIElement::onDragStart(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
}

void UIElement::onDragEnd(const IntVector2& position, const IntVector2& screenPosition)
{
}

void UIElement::onDragMove(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
}

void UIElement::setName(const std::string& name)
{
    mName = name;
}

void UIElement::setPosition(const IntVector2& position)
{
    if (position != mPosition)
    {
        mPosition = position;
        markDirty();
    }
}

void UIElement::setPosition(int x, int y)
{
    setPosition(IntVector2(x, y));
}

void UIElement::setSize(const IntVector2& size)
{
    if (size != mSize)
    {
        mSize.mX = max(size.mX, 0);
        mSize.mY = max(size.mY, 0);
        markDirty();
    }
}

void UIElement::setSize(int width, int height)
{
    setSize(IntVector2(width, height));
}

void UIElement::setWidth(int width)
{
    setSize(IntVector2(width, mSize.mY));
}

void UIElement::setHeight(int height)
{
    setSize(IntVector2(mSize.mX, height));
}

void UIElement::setAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    mHorizontalAlignment = hAlign;
    mVerticalAlignment = vAlign;
    markDirty();
}

void UIElement::setHorizontalAlignment(HorizontalAlignment align)
{
    mHorizontalAlignment = align;
    markDirty();
}

void UIElement::setVerticalAlignment(VerticalAlignment align)
{
    mVerticalAlignment = align;
    markDirty();
}

void UIElement::setClipBorder(const IntRect& rect)
{
    mClipBorder.mLeft = max(rect.mLeft, 0);
    mClipBorder.mTop = max(rect.mTop, 0);
    mClipBorder.mRight = max(rect.mRight, 0);
    mClipBorder.mBottom = max(rect.mBottom, 0);
}

void UIElement::setClipBorder(int left, int top, int right, int bottom)
{
    setClipBorder(IntRect(left, top, right, bottom));
}

void UIElement::setColor(const Color& color)
{
    for (unsigned i = 0; i < MAX_UIELEMENT_CORNERS; ++i)
        mColor[i] = color;
    mHasColorGradient = false;
}

void UIElement::setColor(UIElementCorner corner, const Color& color)
{
    mColor[corner] = color;
    mHasColorGradient = false;
    
    for (unsigned i = 0; i < MAX_UIELEMENT_CORNERS; ++i)
    {
        if ((i != corner) && (mColor[i] != mColor[corner]))
            mHasColorGradient = true;
    }
}

void UIElement::setHoverColor(const Color& color)
{
    mHoverColor = color;
}

void UIElement::setPriority(int priority)
{
    mPriority = priority;
}

void UIElement::setOpacity(float opacity)
{
    mOpacity = clamp(opacity, 0.0f, 1.0f);
    markDirty();
}

void UIElement::setBringToFront(bool enable)
{
    mBringToFront = enable;
}

void UIElement::setClipChildren(bool enable)
{
    mClipChildren = enable;
}

void UIElement::setEnabled(bool enable)
{
    mEnabled = enable;
}

void UIElement::setFocusable(bool enable)
{
    mFocusable = enable;
}

void UIElement::setFocus(bool enable)
{
    if (!mFocusable)
        enable = false;
    
    if (enable != mFocus)
    {
        mFocus = enable;
        
        using namespace Focused;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        sendEvent(mFocus ? EVENT_FOCUSED : EVENT_DEFOCUSED, eventData);
    }
}

void UIElement::setVisible(bool enable)
{
    mVisible = enable;
}

void UIElement::setStyleAuto(XMLFile* file, ResourceCache* cache)
{
    XMLElement element = getStyleElement(file);
    setStyle(element, cache);
}

void UIElement::addChild(UIElement* element)
{
    if ((!element) || (element->mParent == this) || (mParent == element))
        return;
    
    if (element->mParent)
        element->mParent->removeChild(element);
    
    mChildren.push_back(SharedPtr<UIElement>(element));
    
    element->mParent = this;
    element->markDirty();
}

void UIElement::removeChild(UIElement* element)
{
    for (std::vector<SharedPtr<UIElement> >::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
    {
        if ((*i) == element)
        {
            element->mParent = 0;
            element->markDirty();
            mChildren.erase(i);
            return;
        }
    }
}

void UIElement::removeAllChildren()
{
    while (mChildren.size())
    {
        const SharedPtr<UIElement>& element = mChildren.back();
        element->mParent = 0;
        element->markDirty();
        mChildren.pop_back();
    }
}

std::vector<UIElement*> UIElement::getChildren(bool recursive) const
{
    if (!recursive)
    {
        std::vector<UIElement*> ret;
        for (std::vector<SharedPtr<UIElement> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
            ret.push_back(*i);
        
        return ret;
    }
    else
    {
        std::vector<UIElement*> allChildren;
        getChildrenRecursive(allChildren);
        
        return allChildren;
    }
}

unsigned UIElement::getNumChildren(bool recursive) const
{
    if (!recursive)
        return mChildren.size();
    else
    {
        unsigned allChildren = mChildren.size();
        for (std::vector<SharedPtr<UIElement> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
            allChildren += (*i)->getNumChildren(true);
        
        return allChildren;
    }
}

UIElement* UIElement::getChild(unsigned index) const
{
    if (index >= mChildren.size())
        return 0;
    
    return mChildren[index];
}

UIElement* UIElement::getChild(const std::string& name, bool recursive) const
{
    for (std::vector<SharedPtr<UIElement> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
    {
        if ((*i)->mName == name)
            return *i;
        
        if (recursive)
        {
            UIElement* element = (*i)->getChild(name, true);
            if (element)
                return element;
        }
    }
    
    return 0;
}

XMLElement UIElement::getStyleElement(XMLFile* file) const
{
    if (file)
    {
        XMLElement rootElem = file->getRootElement();
        XMLElement childElem = rootElem.getChildElement("element");
        while (childElem)
        {
            if (childElem.getString("type") == getTypeName())
                return childElem;
            childElem = childElem.getNextElement("element");
        }
    }
    
    return XMLElement();
}

IntVector2 UIElement::screenToElement(const IntVector2& screenPosition)
{
    return screenPosition - getScreenPosition();
}

IntVector2 UIElement::elementToScreen(const IntVector2& position)
{
    return position + getScreenPosition();
}

bool UIElement::isInside(IntVector2 position, bool isScreen)
{
    if (isScreen)
        position = screenToElement(position);
    return (position.mX >= 0) && (position.mY >= 0) && (position.mX < mSize.mX) && (position.mY < mSize.mY);
}

void UIElement::setHovering(bool enable)
{
    mHovering = enable;
}

void UIElement::adjustScissor(IntRect& currentScissor)
{
    if (mClipChildren)
    {
        IntVector2 screenPos = getScreenPosition();
        currentScissor.mLeft = max(currentScissor.mLeft, screenPos.mX + mClipBorder.mLeft);
        currentScissor.mTop = max(currentScissor.mTop, screenPos.mY + mClipBorder.mTop);
        currentScissor.mRight = min(currentScissor.mRight, screenPos.mX + mSize.mX - mClipBorder.mRight);
        currentScissor.mBottom = min(currentScissor.mBottom, screenPos.mY + mSize.mY - mClipBorder.mBottom);
    }
}

XMLElement UIElement::getStyleElement(XMLFile* file, const std::string& typeName)
{
    if (file)
    {
        XMLElement rootElem = file->getRootElement();
        XMLElement childElem = rootElem.getChildElement("element");
        while (childElem)
        {
            if (childElem.getString("type") == typeName)
                return childElem;
            childElem = childElem.getNextElement("element");
        }
    }
    
    return XMLElement();
}

void UIElement::markDirty()
{
    if ((mScreenPositionDirty) && (mDerivedOpacityDirty))
        return;
    
    mScreenPositionDirty = true;
    mDerivedOpacityDirty = true;
    
    for (std::vector<SharedPtr<UIElement> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
        (*i)->markDirty();
}

void UIElement::setChildOffset(const IntVector2& offset)
{
    if (offset != mChildOffset)
    {
        mChildOffset = offset;
        for (std::vector<SharedPtr<UIElement> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
            (*i)->markDirty();
    }
}

void UIElement::getChildrenRecursive(std::vector<UIElement*>& dest) const
{
    for (std::vector<SharedPtr<UIElement> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
    {
        dest.push_back(*i);
        (*i)->getChildrenRecursive(dest);
    }
}
