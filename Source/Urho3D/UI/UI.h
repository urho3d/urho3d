//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../Core/Object.h"
#include "../UI/Cursor.h"
#include "../UI/UIBatch.h"

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
    void SetFocusElement(UIElement* element, bool byKey = false);
    /// Set modal element. Until all the modal elements are dismissed, all the inputs and events are only sent to them. Return true when successful.
    /// Only the modal element can clear its modal status or when it is being destructed.
    bool SetModalElement(UIElement* modalElement, bool enable);
    /// Clear the UI (excluding the cursor.)
    void Clear();
    /// Update the UI logic. Called by HandlePostUpdate().
    void Update(float timeStep);
    /// Update the UI for rendering. Called by HandleRenderUpdate().
    void RenderUpdate();
    /// Render the UI. If resetRenderTargets is true, is assumed to be the default UI render to backbuffer called by Engine, and will be performed only once. Additional UI renders to a different rendertarget may be triggered from the renderpath.
    void Render(bool resetRenderTargets = true);
    /// Debug draw a UI element.
    void DebugDraw(UIElement* element);
    /// Load a UI layout from an XML file. Optionally specify another XML file for element style. Return the root element.
    SharedPtr<UIElement> LoadLayout(Deserializer& source, XMLFile* styleFile = 0);
    /// Load a UI layout from an XML file. Optionally specify another XML file for element style. Return the root element.
    SharedPtr<UIElement> LoadLayout(XMLFile* file, XMLFile* styleFile = 0);
    /// Save a UI layout to an XML file. Return true if successful.
    bool SaveLayout(Serializer& dest, UIElement* element);
    /// Set clipboard text.
    void SetClipboardText(const String& text);
    /// Set UI element double click interval in seconds.
    void SetDoubleClickInterval(float interval);
    /// Set UI drag event start interval in seconds.
    void SetDragBeginInterval(float interval);
    /// Set UI drag event start distance threshold in pixels.
    void SetDragBeginDistance(int pixels);
    /// Set tooltip default display delay in seconds.
    void SetDefaultToolTipDelay(float delay);
    /// Set maximum font face texture size. Must be a power of two. Default is 2048.
    void SetMaxFontTextureSize(int size);
    /// Set whether mouse wheel can control also a non-focused element.
    void SetNonFocusedMouseWheel(bool nonFocusedMouseWheel);
    /// Set whether to use system clipboard. Default false.
    void SetUseSystemClipboard(bool enable);
    /// Set whether to show the on-screen keyboard (if supported) when a %LineEdit is focused. Default true on mobile devices.
    void SetUseScreenKeyboard(bool enable);
    /// Set whether to use mutable (eraseable) glyphs to ensure a font face never expands to more than one texture. Default false.
    void SetUseMutableGlyphs(bool enable);
    /// Set whether to force font autohinting instead of using FreeType's TTF bytecode interpreter.
    void SetForceAutoHint(bool enable);

    /// Return root UI element.
    UIElement* GetRoot() const { return rootElement_; }
    /// Return root modal element.
    UIElement* GetRootModalElement() const { return rootModalElement_; }
    /// Return cursor.
    Cursor* GetCursor() const { return cursor_; }
    /// Return cursor position.
    IntVector2 GetCursorPosition() const;
    /// Return UI element at screen coordinates. By default returns only input-enabled elements.
    UIElement* GetElementAt(const IntVector2& position, bool enabledOnly = true);
    /// Return UI element at screen coordinates. By default returns only input-enabled elements.
    UIElement* GetElementAt(int x, int y, bool enabledOnly = true);
    /// Return focused element.
    UIElement* GetFocusElement() const { return focusElement_; }
    /// Return topmost enabled root-level non-modal element.
    UIElement* GetFrontElement() const;
    /// Return currently dragged elements.
    const Vector<UIElement*> GetDragElements();
    /// Return the number of currently dragged elements.
    unsigned GetNumDragElements() const { return dragConfirmedCount_; }
    /// Return the drag element at index.
    UIElement* GetDragElement(unsigned index);
    /// Return clipboard text.
    const String& GetClipboardText() const;
    /// Return UI element double click interval in seconds.
    float GetDoubleClickInterval() const { return doubleClickInterval_; }
    /// Return UI drag start event interval in seconds.
    float GetDragBeginInterval() const { return dragBeginInterval_; }
    /// Return UI drag start event distance threshold in pixels.
    int GetDragBeginDistance() const { return dragBeginDistance_; }
    /// Return tooltip default display delay in seconds.
    float GetDefaultToolTipDelay() const { return defaultToolTipDelay_; }
    /// Return font texture maximum size.
    int GetMaxFontTextureSize() const { return maxFontTextureSize_; }
    /// Return whether mouse wheel can control also a non-focused element.
    bool IsNonFocusedMouseWheel() const { return nonFocusedMouseWheel_; }
    /// Return whether is using the system clipboard.
    bool GetUseSystemClipboard() const { return useSystemClipboard_; }
    /// Return whether focusing a %LineEdit will show the on-screen keyboard.
    bool GetUseScreenKeyboard() const { return useScreenKeyboard_; }
    /// Return whether is using mutable (eraseable) glyphs for fonts.
    bool GetUseMutableGlyphs() const { return useMutableGlyphs_; }
    /// Return whether is using forced autohinting.
    bool GetForceAutoHint() const { return forceAutoHint_; }
    /// Return true when UI has modal element(s).
    bool HasModalElement() const;
    /// Return whether a drag is in progress.
    bool IsDragging() const { return dragConfirmedCount_ > 0; };

    /// Data structure used to represent the drag data associated to a UIElement.
    struct DragData
    {
        /// Which button combo initiated the drag.
        int dragButtons;
        /// How many buttons initiated the drag.
        int numDragButtons;
        /// Sum of all touch locations
        IntVector2 sumPos;
        /// Flag for a drag start event pending.
        bool dragBeginPending;
        /// Timer used to trigger drag begin event.
        Timer dragBeginTimer;
        /// Drag start position.
        IntVector2 dragBeginSumPos;
    };

private:
    /// Initialize when screen mode initially set.
    void Initialize();
    /// Update UI element logic recursively.
    void Update(float timeStep, UIElement* element);
    /// Upload UI geometry into a vertex buffer.
    void SetVertexData(VertexBuffer* dest, const PODVector<float>& vertexData);
    /// Render UI batches. Geometry must have been uploaded first.
    void Render(bool resetRenderTargets, VertexBuffer* buffer, const PODVector<UIBatch>& batches, unsigned batchStart, unsigned batchEnd);
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
    /// Force release of font faces when global font properties change.
    void ReleaseFontFaces();
    /// Handle button or touch hover
    void ProcessHover(const IntVector2& cursorPos, int buttons, int qualifiers, Cursor* cursor);
    /// Handle button or touch begin.
    void ProcessClickBegin(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible);
    /// Handle button or touch end.
    void ProcessClickEnd(const IntVector2& cursorPos, int button, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible);
    /// Handle mouse or touch move.
    void ProcessMove(const IntVector2& cursorPos, const IntVector2& cursorDeltaPos, int buttons, int qualifiers, Cursor* cursor, bool cursorVisible);
    /// Send a UI element drag or hover begin event.
    void SendDragOrHoverEvent(StringHash eventType, UIElement* element, const IntVector2& screenPos, const IntVector2& deltaPos, UI::DragData* dragData);
    /// Send a UI click or double click event.
    void SendClickEvent(StringHash eventType, UIElement* beginElement, UIElement* endElement, const IntVector2& pos, int button, int buttons, int qualifiers);
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
    /// Handle text input event.
    void HandleTextInput(StringHash eventType, VariantMap& eventData);
    /// Handle frame begin event.
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    /// Handle logic post-update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle render update event.
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle a file being drag-dropped into the application window.
    void HandleDropFile(StringHash eventType, VariantMap& eventData);
    /// Remove drag data and return next iterator.
    HashMap<WeakPtr<UIElement>, DragData*>::Iterator DragElementErase(HashMap<WeakPtr<UIElement>, DragData*>::Iterator dragElement);
    /// Handle clean up on a drag cancel.
    void ProcessDragCancel();
    /// Sum touch positions and return the begin position ready to send.
    IntVector2 SumTouchPositions(UI::DragData* dragData, const IntVector2& oldSendPos);

    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// UI root element.
    SharedPtr<UIElement> rootElement_;
    /// UI root modal element.
    SharedPtr<UIElement> rootModalElement_;
    /// Cursor.
    SharedPtr<Cursor> cursor_;
    /// Currently focused element.
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
    mutable String clipBoard_;
    /// Seconds between clicks to register a double click.
    float doubleClickInterval_;
    /// Seconds from mouse button down to begin a drag if there has been no movement exceeding pixel threshold.
    float dragBeginInterval_;
    /// Tooltip default display delay in seconds.
    float defaultToolTipDelay_;
    /// Drag begin event distance threshold in pixels.
    int dragBeginDistance_;
    /// Mouse buttons held down.
    int mouseButtons_;
    /// Last mouse button pressed.
    int lastMouseButtons_;
    /// Qualifier keys held down.
    int qualifiers_;
    /// Font texture maximum size.
    int maxFontTextureSize_;
    /// Initialized flag.
    bool initialized_;
    /// Touch used flag.
    bool usingTouchInput_;
    /// Flag to switch mouse wheel event to be sent to non-focused element at cursor.
    bool nonFocusedMouseWheel_;
    /// Flag for using operating system clipboard instead of internal.
    bool useSystemClipboard_;
    /// Flag for showing the on-screen keyboard on focusing a %LineEdit.
    bool useScreenKeyboard_;
    /// Flag for using mutable (eraseable) font glyphs.
    bool useMutableGlyphs_;
    /// Flag for forcing FreeType autohinting.
    bool forceAutoHint_;
    /// Flag for UI already being rendered this frame.
    bool uiRendered_;
    /// Non-modal batch size (used internally for rendering).
    unsigned nonModalBatchSize_;
    /// Timer used to trigger double click.
    Timer clickTimer_;
    /// UI element last clicked for tracking double clicks.
    WeakPtr<UIElement> doubleClickElement_;
    /// Currently hovered elements.
    HashMap<WeakPtr<UIElement>, bool> hoveredElements_;
    /// Currently dragged elements.
    HashMap<WeakPtr<UIElement>, DragData*> dragElements_;
    /// Number of elements in dragElements_.
    int dragElementsCount_;
    /// Number of elements in dragElements_ with dragPending = false.
    int dragConfirmedCount_;
    /// UI elements that are being touched with touch input.
    HashMap<WeakPtr<UIElement>, int> touchDragElements_;
    /// Confirmed drag elements cache.
    Vector<UIElement*> dragElementsConfirmed_;
};

/// Register UI library objects.
void URHO3D_API RegisterUILibrary(Context* context);

}
