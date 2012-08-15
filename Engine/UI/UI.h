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

#include "Object.h"
#include "UIBatch.h"

namespace Urho3D
{

class Cursor;
class Graphics;
class ResourceCache;
class UIBatch;
class UIElement;
class VertexBuffer;
class XMLElement;
class XMLFile;

/// %UI subsystem. Manages the graphical user interface.
class UI : public Object
{
    OBJECT(UI);
    
public:
    /// Construct.
    UI(Context* context);
    /// Destruct.
    virtual ~UI();
    
    /// Set cursor UI element.
    void SetCursor(Cursor* cursor);
    /// Set focused UI element.
    void SetFocusElement(UIElement* element);
    /// Clear the UI (excluding the cursor.)
    void Clear();
    /// Update the UI logic. Called by HandlePostUpdate().
    void Update(float timeStep);
    /// Update the UI for rendering. Called by HandleRenderUpdate().
    void RenderUpdate();
    /// Render the UI.
    void Render();
    /// Load a UI layout from an XML file. Optionally specify another XML file for element style. Return the root element.
    SharedPtr<UIElement> LoadLayout(XMLFile* file, XMLFile* styleFile = 0);
    /// Set clipboard text.
    void SetClipBoardText(const String& text);
    
    /// Return root UI element.
    UIElement* GetRoot() const { return rootElement_; }
    /// Return cursor.
    Cursor* GetCursor() const { return cursor_; }
    /// Return UI element at screen coordinates.
    UIElement* GetElementAt(const IntVector2& position, bool activeOnly = true);
    /// Return UI element at screen coordinates.
    UIElement* GetElementAt(int x, int y, bool activeOnly = true);
    /// Return focused element.
    UIElement* GetFocusElement() const;
    /// Return topmost enabled root-level element.
    UIElement* GetFrontElement() const;
    /// Return cursor position.
    IntVector2 GetCursorPosition();
    /// Return clipboard text.
    const String& GetClipBoardText() const { return clipBoard_; }
    
private:
    /// Initialize when screen mode initially se.
    void Initialize();
    /// Update UI element logic recursively.
    void Update(float timeStep, UIElement* element);
    /// Generate batches from an UI element recursively.
    void GetBatches(UIElement* element, IntRect currentScissor);
    /// Return whether element is visible and within the scissor rectangle
    bool IsVisible(UIElement* element, const IntRect& currentScissor);
    /// Return UI element at screen position recursively.
    void GetElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool activeOnly);
    /// Return the first element in hierarchy that can alter focus.
    UIElement* GetFocusableElement(UIElement* element);
    /// Load a UI layout from an XML file recursively.
    void LoadLayout(UIElement* current, const XMLElement& elem, XMLFile* styleFile);
    /// Handle screen mode event.
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle mouse button down event.
    void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData);
    /// Handle mouse button up event.
    void HandleMouseButtonUp(StringHash eventType, VariantMap& eventData);
    /// Handle mouse move event.
    void HandleMouseMove(StringHash eventType, VariantMap& eventData);
    /// Handle mouse wheel event.
    void HandleMouseWheel(StringHash eventType, VariantMap& eventData);
    /// Handle touch begin event.
    void HandleTouchBegin(StringHash eventType, VariantMap& eventData);
    /// Handle touch end event.
    void HandleTouchEnd(StringHash eventType, VariantMap& eventData);
    /// Handle touch move event.
    void HandleTouchMove(StringHash eventType, VariantMap& eventData);
    /// Handle keypress event.
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    /// Handle character event.
    void HandleChar(StringHash eventType, VariantMap& eventData);
    /// Handle logic post-update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle render update event.
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Vertex shader for no texture.
    SharedPtr<ShaderVariation> noTextureVS_;
    /// Vertex shader for diffuse texture.
    SharedPtr<ShaderVariation> diffTextureVS_;
    /// Pixel shader for no texture.
    SharedPtr<ShaderVariation> noTexturePS_;
    /// Pixel shader for diffuse texture.
    SharedPtr<ShaderVariation> diffTexturePS_;
    /// Pixel shader for diffuse texture masking.
    SharedPtr<ShaderVariation> diffMaskTexturePS_;
    /// Pixel shader for alpha texture.
    SharedPtr<ShaderVariation> alphaTexturePS_;
    /// UI root element.
    SharedPtr<UIElement> rootElement_;
    /// Cursor.
    SharedPtr<Cursor> cursor_;
    /// UI element being dragged.
    WeakPtr<UIElement> dragElement_;
    /// Currently focused element
    WeakPtr<UIElement> focusElement_;
    /// UI rendering batches.
    PODVector<UIBatch> batches_;
    /// UI rendering quads.
    PODVector<UIQuad> quads_;
    /// UI vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// UI element query vector.
    PODVector<UIElement*> tempElements_;
    /// Clipboard text.
    String clipBoard_;
    /// Mouse buttons held down.
    int mouseButtons_;
    /// Qualifier keys held down.
    int qualifiers_;
    /// Initialized flag.
    bool initialized_;
};

/// Register UI library objects.
void RegisterUILibrary(Context* context);

}
