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
#include "BaseUIElementFactory.h"
#include "Cursor.h"
#include "Font.h"
#include "InputEvents.h"
#include "Log.h"
#include "Matrix4.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererEvents.h"
#include "RendererImpl.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "UI.h"
#include "UIEvents.h"
#include "VertexShader.h"

#include <algorithm>

#include "DebugNew.h"

static bool compareUIElements(const UIElement* lhs, const UIElement* rhs)
{
    return lhs->getPriority() < rhs->getPriority();
}

UI::UI(Renderer* renderer, ResourceCache* cache) :
    mRenderer(renderer),
    mCache(cache),
    mMouseDrag(false),
    mMouseDragElement(0),
    mDefocusElement(0),
    mMouseButtons(0),
    mQualifiers(0)
{
    if (!mRenderer)
        EXCEPTION("Null renderer for UI");
    if (!mCache)
        EXCEPTION("Null resource cache for UI");
    
    LOGINFO("UI created");
    
    mRootElement = new UIElement();
    mRootElement->setSize(mRenderer->getWidth(), mRenderer->getHeight());
    subscribeToEvent(EVENT_WINDOWRESIZED, EVENT_HANDLER(UI, handleWindowResized));
    subscribeToEvent(EVENT_MOUSEMOVE, EVENT_HANDLER(UI, handleMouseMove));
    subscribeToEvent(EVENT_MOUSEBUTTONDOWN, EVENT_HANDLER(UI, handleMouseButtonDown));
    subscribeToEvent(EVENT_MOUSEBUTTONUP, EVENT_HANDLER(UI, handleMouseButtonUp));
    subscribeToEvent(EVENT_KEYDOWN, EVENT_HANDLER(UI, handleKeyDown));
    subscribeToEvent(EVENT_CHAR, EVENT_HANDLER(UI, handleChar));
    
    mNoTextureVS = mCache->getResource<VertexShader>("Shaders/SM2/Basic_VCol.vs2");
    mDiffTextureVS = mCache->getResource<VertexShader>("Shaders/SM2/Basic_DiffVCol.vs2");
    mNoTexturePS = mCache->getResource<PixelShader>("Shaders/SM2/Basic_VCol.ps2");
    mDiffTexturePS = mCache->getResource<PixelShader>("Shaders/SM2/Basic_DiffVCol.ps2");
    mAlphaTexturePS = mCache->getResource<PixelShader>("Shaders/SM2/Basic_AlphaVCol.ps2");
    
    // Add the base element factory
    addElementFactory(new BaseUIElementFactory());
}

UI::~UI()
{
    LOGINFO("UI shut down");
}

void UI::setCursor(Cursor* cursor)
{
    // Remove old cursor (if any) and set new
    if (mCursor)
    {
        mRootElement->removeChild(mCursor);
        mCursor.reset();
    }
    if (cursor)
    {
        mRootElement->addChild(cursor);
        mCursor = cursor;
        
        IntVector2 pos = mCursor->getPosition();
        const IntVector2& rootSize = mRootElement->getSize();
        pos.mX = clamp(pos.mX, 0, rootSize.mX - 1);
        pos.mY = clamp(pos.mY, 0, rootSize.mY - 1);
        mCursor->setPosition(pos);
    }
}

void UI::setFocusElement(UIElement* element)
{
    using namespace TryFocus;
    
    VariantMap eventData;
    eventData[P_ELEMENT] = (void*)element;
    sendEvent(EVENT_TRYFOCUS, eventData);
    
    // Return if already has focus
    if ((element) && (element->hasFocus()))
        return;
    // Return if element can not be focused, and does not reset the focus either
    if ((element) && (element->getFocusMode() == FM_NOTFOCUSABLE))
        return;
    
    std::vector<UIElement*> allChildren = mRootElement->getChildren(true);
    
    // Go through all elements to clear the old focus
    for (std::vector<UIElement*>::iterator i = allChildren.begin(); i != allChildren.end(); ++i)
    {
        UIElement* other = *i;
        if ((other != element) && (other->hasFocus()))
            other->setFocus(false);
    }
    
    if (element)
        element->setFocus(true);
}

void UI::clear()
{
    mRootElement->removeAllChildren();
    if (mCursor)
        mRootElement->addChild(mCursor);
}

void UI::update(float timeStep)
{
    PROFILE(UI_Update);
    
    // If device lost, do not perform update
    if (mRenderer->isDeviceLost())
        return;
    
    if ((mCursor) && (mCursor->isVisible()))
    {
        IntVector2 pos = mCursor->getPosition();
        UIElement* element = getElementAt(pos);
        if (element)
        {
            // If a drag is going on, transmit hover only to the element being dragged
            if ((!mMouseDragElement) || (mMouseDragElement == element))
                element->onHover(element->screenToElement(pos), pos, mMouseButtons, mQualifiers);
        }
    }
    
    // Defocus element now if should
    if (mDefocusElement)
    {
        // Do nothing if the focus element changed in the meanwhile
        if (mDefocusElement == getFocusElement())
            setFocusElement(0);
        mDefocusElement = 0;
    }
    
    {
        PROFILE(UI_UpdateElements);
        
        update(timeStep, mRootElement);
    }

    {
        PROFILE(UI_GetBatches);
        
        mBatches.clear();
        mQuads.clear();
        const IntVector2& rootSize = mRootElement->getSize();
        getBatches(mRootElement, IntRect(0, 0, rootSize.mX, rootSize.mY));
    }
}

void UI::render()
{
    PROFILE(UI_Render);
    
    static const Vector2 scale(2.0f, -2.0f);
    static const Vector2 offset(-1.0f, 1.0f);
    
    Matrix4 projection;
    
    memset(&projection, 0, sizeof(projection));
    projection.m00 = scale.mX;
    projection.m03 = offset.mX;
    projection.m11 = scale.mY;
    projection.m13 = offset.mY;
    projection.m22 = 1.0f;
    projection.m23 = 0.0f;
    projection.m33 = 1.0f;
    
    mRenderer->resetRenderTargets();
    mRenderer->setCullMode(CULL_CCW);
    mRenderer->setDepthTest(CMP_ALWAYS);
    mRenderer->setDepthWrite(false);
    mRenderer->setFillMode(FILL_SOLID);
    mRenderer->setStencilTest(false);
    mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), projection);
    mRenderer->setPixelShaderConstant(getPSRegister(PSP_MATDIFFCOLOR), Color(1.0f, 1.0f, 1.0f, 1.0f));
    
    PixelShader* ps = 0;
    VertexShader* vs = 0;
    
    for (unsigned i = 0; i < mBatches.size(); ++i)
    {
        // Choose shaders here so that UIBatch does not need to look up shaders each time
        if (!mBatches[i].mTexture)
        {
            ps = mNoTexturePS;
            vs = mNoTextureVS;
        }
        else
        {
            // If texture contains only an alpha channel, use the alpha pixel shader
            vs = mDiffTextureVS;
            
            if (mBatches[i].mTexture->getFormat() == D3DFMT_A8)
                ps = mAlphaTexturePS;
            else
                ps = mDiffTexturePS;
        }
        
        mBatches[i].draw(mRenderer, vs, ps);
    }
}

void UI::addElementFactory(UIElementFactory* factory)
{
    if (!factory)
        return;
    
    mFactories.push_back(SharedPtr<UIElementFactory>(factory));
}

SharedPtr<UIElement> UI::createElement(ShortStringHash type, const std::string& name)
{
    SharedPtr<UIElement> element;
    
    for (unsigned i = 0; i < mFactories.size(); ++i)
    {
        element = mFactories[i]->createElement(type, name);
        if (element)
            return element;
    }
    
    EXCEPTION("Could not create unknown UI element type " + toString(type));
}

SharedPtr<UIElement> UI::loadLayout(XMLFile* file, XMLFile* styleFile)
{
    PROFILE(UI_LoadLayout);
    
    SharedPtr<UIElement> root;
    
    if (!file)
    {
        LOGERROR("Null UI layout XML file");
        return root;
    }
    
    LOGDEBUG("Loading UI layout " + file->getName());
    
    XMLElement rootElem = file->getRootElement("element");
    if (!rootElem)
    {
        LOGERROR("No root UI element in " + file->getName());
        return root;
    }
    
    root = createElement(ShortStringHash(rootElem.getString("type")), rootElem.getString("name"));
    
    // First set the base style from the style file if exists, then apply UI layout overrides
    if (styleFile)
        root->setStyleAuto(styleFile, mCache);
    root->setStyle(rootElem, mCache);
    
    // Load rest of the elements recursively
    loadLayout(root, rootElem, styleFile);
    
    return root;
}

UIElement* UI::getElementAt(const IntVector2& position, bool enabledOnly)
{
    UIElement* result = 0;
    getElementAt(result, mRootElement, position, enabledOnly);
    return result;
}

UIElement* UI::getElementAt(int x, int y, bool enabledOnly)
{
    UIElement* result = 0;
    getElementAt(result, mRootElement, IntVector2(x, y), enabledOnly);
    return result;
}

UIElement* UI::getFocusElement()
{
    std::vector<UIElement*> allChildren = mRootElement->getChildren(true);
    for (std::vector<UIElement*>::iterator i = allChildren.begin(); i != allChildren.end(); ++i)
    {
        if ((*i)->hasFocus())
            return *i;
    }
    
    return 0;
}

IntVector2 UI::getCursorPosition()
{
    if (!mCursor)
        return IntVector2::sZero;
    else
        return mCursor->getPosition();
}

void UI::update(float timeStep, UIElement* element)
{
    element->update(timeStep);
    
    const std::vector<UIElement*> children = element->getChildren();
    for (std::vector<UIElement*>::const_iterator i = children.begin(); i != children.end(); ++i)
        update(timeStep, *i);
}

void UI::getBatches(UIElement* element, IntRect currentScissor)
{
    // Set clipping scissor for child elements. No need to draw if zero size
    element->adjustScissor(currentScissor);
    if ((currentScissor.mLeft == currentScissor.mRight) || (currentScissor.mTop == currentScissor.mBottom))
        return;
    
    std::vector<UIElement*> children = element->getChildren();
    if (children.empty())
        return;
    
    std::sort(children.begin(), children.end(), compareUIElements);
    
    // For non-root elements draw all children of same priority before recursing into their children: assumption is that they have
    // same renderstate
    std::vector<UIElement*>::const_iterator i = children.begin();
    if (element != mRootElement)
    {
        std::vector<UIElement*>::const_iterator j = i;
        int currentPriority = children.front()->getPriority();
        while (i != children.end())
        {
            while ((j != children.end()) && ((*j)->getPriority() == currentPriority))
            {
                if ((*j)->isVisible())
                    (*j)->getBatches(mBatches, mQuads, currentScissor);
                ++j;
            }
            // Now recurse into the children
            while (i != j)
            {
                if ((*i)->isVisible())
                    getBatches(*i, currentScissor);
                ++i;
            }
            if (i != children.end())
                currentPriority = (*i)->getPriority();
        }
    }
    // On the root level draw each element and its children immediately after to avoid artifacts
    else
    {
        while (i != children.end())
        {
            if ((*i)->isVisible())
            {
                (*i)->getBatches(mBatches, mQuads, currentScissor);
                getBatches(*i, currentScissor);
            }
            ++i;
        }
    }
}

void UI::getElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool enabledOnly)
{
    if (!current)
        return;
    
    // Get children from lowest priority to highest
    std::vector<UIElement*> children = current->getChildren(false);
    std::sort(children.begin(), children.end(), compareUIElements);
    
    for (std::vector<UIElement*>::const_iterator i = children.begin(); i != children.end(); ++i)
    {
        UIElement* element = *i;
        if ((element != mCursor.getPtr()) && (element->isVisible()))
        {
            if (element->isInside(position, true))
            {
                // Store the current result, then recurse into its children. Because children
                // are sorted from lowest to highest priority, we should be left with the topmost match
                if ((element->isEnabled()) || (!enabledOnly))
                    result = element;
            }
            
            if (element->isInsideCombined(position, true))
                getElementAt(result, element, position, enabledOnly);
        }
    }
}

UIElement* UI::verifyElement(UIElement* element)
{
    std::vector<UIElement*> allChildren = mRootElement->getChildren(true);
    for (std::vector<UIElement*>::iterator i = allChildren.begin(); i != allChildren.end(); ++i)
    {
        if ((*i) == element)
            return *i;
    }
    
    return 0;
}

void UI::handleWindowResized(StringHash eventType, VariantMap& eventData)
{
    using namespace WindowResized;
    
    mRootElement->setSize(eventData[P_WIDTH].getInt(), eventData[P_HEIGHT].getInt());
}

void UI::handleMouseMove(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;
    
    mMouseButtons = eventData[P_BUTTONS].getInt();
    mQualifiers = eventData[P_QUALIFIERS].getInt();
    
    if ((mCursor) && (mCursor->isVisible()))
    {
        IntVector2 pos = mCursor->getPosition();
        pos.mX += eventData[P_X].getInt();
        pos.mY += eventData[P_Y].getInt();
        const IntVector2& rootSize = mRootElement->getSize();
        pos.mX = clamp(pos.mX, 0, rootSize.mX - 1);
        pos.mY = clamp(pos.mY, 0, rootSize.mY - 1);
        mCursor->setPosition(pos);
        
        if ((mMouseDrag) && (mMouseButtons))
        {
            UIElement* element = verifyElement(mMouseDragElement);
            if ((element) && (element->isEnabled()) && (element->isVisible()))
                element->onDragMove(element->screenToElement(pos), pos, mMouseButtons, mQualifiers);
            else
            {
                mMouseDrag = false;
                mMouseDragElement = 0;
            }
        }
    }
}

void UI::handleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonDown;
    
    mMouseButtons = eventData[P_BUTTONS].getInt();
    mQualifiers = eventData[P_QUALIFIERS].getInt();
    int button = eventData[P_BUTTON].getInt();
    
    if ((mCursor) && (mCursor->isVisible()))
    {
        IntVector2 pos = mCursor->getPosition();
        UIElement* element = getElementAt(pos);
        if (element)
        {
            // Handle focusing & bringing to front
            if (button == MOUSEB_LEFT)
            {
                setFocusElement(element);
                element->bringToFront();
            }
            
            // Handle click
            element->onClick(element->screenToElement(pos), pos, mMouseButtons, mQualifiers);
            
            // Handle start of drag
            if (!mMouseDrag)
            {
                mMouseDrag = true;
                mMouseDragElement = element;
                element->onDragStart(element->screenToElement(pos), pos, mMouseButtons, mQualifiers);
            }
        }
        else
        {
            // If clicked over no element, or a disabled element, lose focus
            setFocusElement(0);
        }
    }
}

void UI::handleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonUp;
    
    mMouseButtons = eventData[P_BUTTONS].getInt();
    mQualifiers = eventData[P_QUALIFIERS].getInt();
    
    if ((mCursor) && (mCursor->isVisible()))
    {
        IntVector2 pos = mCursor->getPosition();
        
        if ((mMouseDrag) && (!mMouseButtons))
        {
            UIElement* element = verifyElement(mMouseDragElement);
            if ((element) && (element->isEnabled()) && (element->isVisible()))
                element->onDragEnd(element->screenToElement(pos), pos);
            
            mMouseDrag = false;
            mMouseDragElement = 0;
        }
    }
}

void UI::handleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;
    
    mMouseButtons = eventData[P_BUTTONS].getInt();
    mQualifiers = eventData[P_QUALIFIERS].getInt();
    int key = eventData[P_KEY].getInt();
    
    UIElement* element = getFocusElement();
    if (element)
    {
        // Switch focus between focusable sibling elements
        if (key == KEY_TAB)
        {
            UIElement* parent = element->getParent();
            if (parent)
            {
                std::vector<UIElement*> children = parent->getChildren();
                for (std::vector<UIElement*>::iterator i = children.begin(); i != children.end();)
                {
                    if ((*i)->getFocusMode() < FM_FOCUSABLE)
                        i = children.erase(i);
                    else
                        ++i;
                }
                for (unsigned i = 0; i < children.size(); ++i)
                {
                    if (children[i] == element)
                    {
                        UIElement* next = children[(i + 1) % children.size()];
                        setFocusElement(next);
                        return;
                    }
                }
            }
        }
        // Defocus the element
        else if ((key == KEY_ESC) && (element->getFocusMode() == FM_FOCUSABLE_DEFOCUSABLE))
            mDefocusElement = element;
        // If none of the special keys, pass the key to the focused element
        else
            element->onKey(key, mMouseButtons, mQualifiers);
    }
}

void UI::handleChar(StringHash eventType, VariantMap& eventData)
{
    using namespace Char;
    
    mMouseButtons = eventData[P_BUTTONS].getInt();
    mQualifiers = eventData[P_QUALIFIERS].getInt();
    
    UIElement* element = getFocusElement();
    if (element)
        element->onChar(eventData[P_CHAR].getInt(), mMouseButtons, mQualifiers);
}

void UI::loadLayout(UIElement* current, const XMLElement& elem, XMLFile* styleFile)
{
    XMLElement childElem = elem.getChildElement("element");
    while (childElem)
    {
        // Create and add to the hierarchy
        SharedPtr<UIElement> child = createElement(ShortStringHash(childElem.getString("type")), childElem.getString("name"));
        current->addChild(child);
        
        // First set the base style from the style file if exists, then apply UI layout overrides
        if (styleFile)
            child->setStyleAuto(styleFile, mCache);
        child->setStyle(childElem, mCache);
        
        // Load the children recursively
        loadLayout(child, childElem, styleFile);
        
        childElem = childElem.getNextElement("element");
    }
}
