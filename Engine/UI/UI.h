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

#ifndef UI_UI_H
#define UI_UI_H

#include "EventListener.h"
#include "SharedPtr.h"
#include "UIBatch.h"

class Cursor;
class Renderer;
class ResourceCache;
class UIBatch;
class UIElement;
class UIElementFactory;

//! Manages the graphical user interface
class UI : public RefCounted, public EventListener
{
public:
    //! Construct with renderer subsystem and resource cache pointers
    UI(Renderer* Renderer, ResourceCache* cache);
    //! Destruct
    virtual ~UI();
    
    //! Set cursor UI element
    void setCursor(Cursor* cursor);
    //! Set focused UI element
    void setFocusElement(UIElement* element);
    //! Bring an UI element to front
    void bringToFront(UIElement* element);
    //! Update the UI
    void update(float timeStep);
    //! Render the UI
    void render();
    //! Add a UI element factory
    void addElementFactory(UIElementFactory* factory);
    //! Create a UI element by type. Throw exception if can not create
    SharedPtr<UIElement> createElement(ShortStringHash type, const std::string& name = std::string());
    //! Load a UI layout from an XML file. Optionally specify another XML file for element style. Return the root element
    SharedPtr<UIElement> loadLayout(XMLFile* file, XMLFile* styleFile = 0);
    
    //! Return root UI elemenet
    UIElement* getRootElement() const { return mRootElement; }
    //! Return cursor
    Cursor* getCursor() const { return mCursor; }
    //! Return UI element at screen coordinates
    UIElement* getElementAt(const IntVector2& position, bool enabledOnly = true);
    //! Return UI element at screen coordinates
    UIElement* getElementAt(int x, int y, bool enabledOnly = true);
    //! Return focused element
    UIElement* getFocusElement();
    //! Return cursor position
    IntVector2 getCursorPosition();
    //! Return UI element factories
    const std::vector<SharedPtr<UIElementFactory> >& getElementFactories() const { return mFactories; }
    
private:
    //! Update UI elements and generate batches for UI rendering
    void update(float timeStep, UIElement* element);
    //! Generate batches from an UI element recursively
    void getBatches(UIElement* element, IntRect currentScissor);
    //! Return UI element at screen position recursively
    void getElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool enabledOnly);
    //! Switch focus to UI element
    void switchFocusTo(UIElement* element);
    //! Verify that an UI element belongs to the UI element hierarchy
    UIElement* verifyElement(UIElement* element);
    //! Handle window resized event
    void handleWindowResized(StringHash eventType, VariantMap& eventData);
    //! Handle mouse move event
    void handleMouseMove(StringHash eventType, VariantMap& eventData);
    //! Handle mouse button down event
    void handleMouseButtonDown(StringHash eventType, VariantMap& eventData);
    //! Handle mouse button up event
    void handleMouseButtonUp(StringHash eventType, VariantMap& eventData);
    //! Handle character event
    void handleChar(StringHash eventType, VariantMap& eventData);
    //! Load a UI layout from an XML file recursively
    void loadLayout(UIElement* current, const XMLElement& elem, XMLFile* styleFile);
    
    //! Renderer
    SharedPtr<Renderer> mRenderer;
    //! Resource cache
    SharedPtr<ResourceCache> mCache;
    //! Vertex shader for no texture
    SharedPtr<VertexShader> mNoTextureVS;
    //! Vertex shader for diffuse texture
    SharedPtr<VertexShader> mDiffTextureVS;
    //! Pixel shader for no texture
    SharedPtr<PixelShader> mNoTexturePS;
    //! Pixel shader for diffuse texture
    SharedPtr<PixelShader> mDiffTexturePS;
    //! Pixel shader for alpha texture
    SharedPtr<PixelShader> mAlphaTexturePS;
    //! UI root element
    SharedPtr<UIElement> mRootElement;
    //! Cursor
    SharedPtr<Cursor> mCursor;
    //! UI element factories
    std::vector<SharedPtr<UIElementFactory> > mFactories;
    //! UI rendering batches
    std::vector<UIBatch> mBatches;
    //! UI rendering quads
    std::vector<UIQuad> mQuads;
    //! Mouse drag flag
    bool mMouseDrag;
    //! Mouse drag UI element
    UIElement* mMouseDragElement;
    //! Mouse buttons held down
    unsigned mMouseButtons;
};

#endif // UI_UI_H
