//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Cursor.h"
#include "UIBatch.h"

namespace Urho3D
{

class Cursor;
class Graphics;
class ResourceCache;
class Timer;
class UIBatch;
class UIElement;
class VertexBuffer;
class XMLElement;
class XMLFile;

/// %UI subsystem. Manages the graphical user interface.
class URHO3D_API UI : public Object
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
    /// Set modal element. Until all the modal elements are dismissed, all the inputs and events are only sent to them. Return true when successful.
    /// Only the modal element can clear its modal status or when it is being destructed.
    /// UI subystem auto-removes modal element when an ESC key is pressed, however if this is not desirable, setting a user-defined variable "NoAutoRemove" in the modal element would prevent this.
    /// In that case, the modal element will only have its modal flag reset and reparented back to its original parent.
    bool SetModalElement(UIElement* modalElement, bool enable);
    /// Clear the UI (excluding the cursor.)
    void Clear();
    /// Update the UI logic. Called by HandlePostUpdate().
    void Update(float timeStep);
    /// Update the UI for rendering. Called by HandleRenderUpdate().
    void RenderUpdate();
    /// Render the UI.
    void Render();
    /// Debug draw a UI element.
    void DebugDraw(UIElement* element);
    /// Load a UI layout from an XML file. Optionally specify another XML file for element style. Return the root element.
    SharedPtr<UIElement> LoadLayout(Deserializer& source, XMLFile* styleFile = 0);
    /// Load a UI layout from an XML file. Optionally specify another XML file for element style. Return the root element.
    SharedPtr<UIElement> LoadLayout(XMLFile* file, XMLFile* styleFile = 0);
    /// Save a UI layout to an XML file. Return true if successful.
    bool SaveLayout(Serializer& dest, UIElement* element);
    /// Set clipboard text.
    void SetClipBoardText(const String& text);
    /// Set UI element double click interval in seconds.
    void SetDoubleClickInterval(float interval);
    /// Set mouse wheel handling flag.
    void SetNonFocusedMouseWheel(bool nonFocusedMouseWheel);

    /// Return root UI element.
    UIElement* GetRoot() const { return rootElement_; }
    /// Return root modal element.
    UIElement* GetRootModalElement() const { return rootModalElement_; }
    /// Return cursor.
    Cursor* GetCursor() const { return cursor_; }
    /// Return cursor position.
    IntVector2 GetCursorPosition() const;
    /// Return UI element at screen coordinates.
    UIElement* GetElementAt(const IntVector2& position, bool enabledOnly = true);
    /// Return UI element at screen coordinates.
    UIElement* GetElementAt(int x, int y, bool enabledOnly = true);
    /// Return focused element.
    UIElement* GetFocusElement() const { return focusElement_; }
    /// Return topmost enabled root-level non-modal element.
    UIElement* GetFrontElement() const;
    /// Return clipboard text.
    const String& GetClipBoardText() const { return clipBoard_; }
    /// Return UI element double click interval in seconds.
    float GetDoubleClickInterval() const { return doubleClickInterval_; }
    /// Return mouse wheel handling flag.
    bool IsNonFocusedMouseWheel() const { return nonFocusedMouseWheel_; }
    /// Return true when UI has modal element(s).
    bool HasModalElement() const;

private:
    /// Initialize when screen mode initially se.
    void Initialize();
    /// Update UI element logic recursively.
    void Update(float timeStep, UIElement* element);
    /// Upload UI geometry into a vertex buffer.
    void SetVertexData(VertexBuffer* dest, const PODVector<float>& vertexData);
    /// Render UI batches. Geometry must have been uploaded first.
    void Render(VertexBuffer* buffer, const PODVector<UIBatch>& batches, unsigned batchStart, unsigned batchEnd);
    /// Generate batches from an UI element recursively. Skip the cursor element.
    void GetBatches(UIElement* element, IntRect currentScissor);
    /// Return UI element at screen position recursively.
    void GetElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool enabledOnly);
    /// Return the first element in hierarchy that can alter focus.
    UIElement* GetFocusableElement(UIElement* element);
    /// Return cursor position and visibility either from the cursor element, or the Input subsystem.
    void GetCursorPositionAndVisible(IntVector2& pos, bool& visible);
    /// Set active cursor's shape.
    void SetCursorShape(CursorShape shape);
    /// Handle button or touch begin.
    void ProcessClickBegin(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible);
    /// Handle button or touch end.
    void ProcessClickEnd(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible);
    /// Handle mouse or touch move.
    void ProcessMove(const IntVector2& cursorPos, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible);
    /// Send a UI element drag event.
    void SendDragEvent(StringHash eventType, UIElement* element, const IntVector2& screenPos);
    /// Send a UI click or double click event.
    void SendClickEvent(StringHash eventType, UIElement* element, const IntVector2& pos, int button, int buttons, int qualifiers);
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
    /// Handle a file being drag-dropped into the application window.
    void HandleDropFile(StringHash eventType, VariantMap& eventData);

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
    /// UI root modal element.
    SharedPtr<UIElement> rootModalElement_;
    /// Cursor.
    SharedPtr<Cursor> cursor_;
    /// UI element being dragged.
    WeakPtr<UIElement> dragElement_;
    /// Currently focused element
    WeakPtr<UIElement> focusElement_;
    /// UI rendering batches.
    PODVector<UIBatch> batches_;
    /// UI rendering vertex data.
    PODVector<float> vertexData_;
    /// UI rendering batches for debug draw.
    PODVector<UIBatch> debugDrawBatches_;
    /// UI rendering vertex data for debug draw.
    PODVector<float> debugVertexData_;
    /// UI vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// UI debug geometry vertex buffer.
    SharedPtr<VertexBuffer> debugVertexBuffer_;
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
    /// Touch used flag.
    bool usingTouchInput_;
    /// Flag to switch mouse wheel event to be sent to non-focused element at cursor.
    bool nonFocusedMouseWheel_;
    /// Non-modal batch size (used internally for rendering).
    unsigned nonModalBatchSize_;
    /// Timer used to trigger double click.
    Timer* clickTimer_;
    /// UI element last clicked for tracking click end.
    WeakPtr<UIElement> clickElement_;
    /// UI element last clicked for tracking double clicks.
    WeakPtr<UIElement> doubleClickElement_;
    /// Last mouse button pressed.
    int lastMouseButtons_;
    /// Seconds between clicks to register a double click.
    float doubleClickInterval_;
};

/// Register UI library objects.
void RegisterUILibrary(Context* context);

}
