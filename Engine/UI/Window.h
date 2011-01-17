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

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "BorderImage.h"

static const int WINDOW_MIN_SIZE = 4;

//! Window movement and resizing modes
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

//! Window that can optionally by moved or resized
class Window : public BorderImage
{
    DEFINE_TYPE(Window);
    
public:
    //! Construct with name
    Window(const std::string& name = std::string());
    //! Destruct
    virtual ~Window();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! React to mouse drag start
    virtual void onDragStart(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag motion
    virtual void onDragMove(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag end
    virtual void onDragEnd(const IntVector2& position, const IntVector2& screenPosition);
    
    //! Set whether can be moved
    void setMovable(bool enable);
    //! Set whether can be resized
    void setResizable(bool enable);
    //! Set minimum size
    void setMinSize(const IntVector2& minSize);
    //! Set minimum size
    void setMinSize(int width, int height);
    //! Set maximum size
    void setMaxSize(const IntVector2& maxSize);
    //! Set maximum size
    void setMaxSize(int width, int height);
    //! Set resize area width at edges
    void setResizeBorder(const IntRect& rect);
    //! Set resize area width at edges
    void setResizeBorder(int left, int top, int right, int bottom);
    
    //! Return whether is movable
    bool isMovable() const { return mMovable; }
    //! Return whether is resizable
    bool isResizable() const { return mResizable; }
    //! Return minimum size
    const IntVector2& getMinSize() const { return mMinSize; }
    //! Return maximum size
    const IntVector2& getMaxSize() const { return mMaxSize; }
    //! Return resize area width at edges
    const IntRect& getResizeBorder() const { return mResizeBorder; }
    
protected:
    //! Validate window size
    void validateSize();
    //! Validate window position
    void validatePosition();
    //! Check whether alignment supports moving and resizing
    bool checkAlignment() const;
    
    //! Movable flag
    bool mMovable;
    //! Resizable flag
    bool mResizable;
    //! Minimum size
    IntVector2 mMinSize;
    //! Maximum size
    IntVector2 mMaxSize;
    //! Resize area width at edges
    IntRect mResizeBorder;
    //! Current drag mode
    WindowDragMode mDragMode;
    //! Mouse position at drag start
    IntVector2 mDragStartPosition;
    //! Original position at drag start
    IntVector2 mOriginalPosition;
    //! Original size at drag start
    IntVector2 mOriginalSize;
};

#endif // UI_WINDOW_H
