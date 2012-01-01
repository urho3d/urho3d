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

#include "BorderImage.h"

/// %Window movement and resizing modes.
enum WindowDragMode
{
    DRAG_NONE,
    DRAG_MOVE,
    DRAG_RESIZE_TOPLEFT,
    DRAG_RESIZE_TOP,
    DRAG_RESIZE_TOPRIGHT,
    DRAG_RESIZE_RIGHT,
    DRAG_RESIZE_BOTTOMRIGHT,
    DRAG_RESIZE_BOTTOM,
    DRAG_RESIZE_BOTTOMLEFT,
    DRAG_RESIZE_LEFT
};

/// %Window %UI element that can optionally by moved or resized.
class Window : public BorderImage
{
    OBJECT(Window);
    
    using UIElement::SetStyle;
    
public:
    /// Construct.
    Window(Context* context);
    /// Destruct.
    virtual ~Window();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set UI element style from XML data.
    virtual void SetStyle(const XMLElement& element);
    /// React to mouse hover.
    virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag start.
    virtual void OnDragStart(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag motion.
    virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag end.
    virtual void OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, Cursor* cursor);
    
    /// %Set whether can be moved.
    void SetMovable(bool enable);
    /// %Set whether can be resized.
    void SetResizable(bool enable);
    /// %Set resize area width at edges.
    void SetResizeBorder(const IntRect& rect);
    
    /// Return whether is movable.
    bool IsMovable() const { return movable_; }
    /// Return whether is resizable.
    bool IsResizable() const { return resizable_; }
    /// Return resize area width at edges.
    const IntRect& GetResizeBorder() const { return resizeBorder_; }
    
protected:
    /// Identify drag mode (move/resize.)
    WindowDragMode GetDragMode(const IntVector2& position) const;
    /// %Set cursor shape based on drag mode.
    void SetCursorShape(WindowDragMode mode, Cursor* cursor) const;
    /// Validate window position.
    void ValidatePosition();
    /// Check whether alignment supports moving and resizing.
    bool CheckAlignment() const;
    
    /// Movable flag.
    bool movable_;
    /// Resizable flag.
    bool resizable_;
    /// Resize area width at edges.
    IntRect resizeBorder_;
    /// Current drag mode.
    WindowDragMode dragMode_;
    /// Mouse position at drag start.
    IntVector2 dragStartCursor_;
    /// Original position at drag start.
    IntVector2 dragStartPosition_;
    /// Original size at drag start.
    IntVector2 dragStartSize_;
};
