//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Math/Rect.h"

namespace Urho3D
{

/// Rectangular area allocator.
class URHO3D_API AreaAllocator
{
public:
    /// Default construct with empty size.
    AreaAllocator();
    /// Construct with given width and height.
    AreaAllocator(int width, int height, bool fastMode = true);
    /// Construct with given width and height, and set the maximum it allows to grow.
    AreaAllocator(int width, int height, int maxWidth, int maxHeight, bool fastMode = true);

    /// Reset to given width and height and remove all previous allocations.
    void Reset(int width, int height, int maxWidth = 0, int maxHeight = 0, bool fastMode = true);
    /// Try to allocate an area. Return true if successful, with x & y coordinates filled.
    bool Allocate(int width, int height, int& x, int& y);

    /// Return the current width.
    int GetWidth() const { return size_.x_; }

    /// Return the current height.
    int GetHeight() const { return size_.y_; }

    /// Return whether uses fast mode. Fast mode uses a simpler allocation scheme which may waste free space, but is OK for eg. fonts.
    bool GetFastMode() const { return fastMode_; }

private:
    /// Remove space from a free rectangle. Return true if the original rectangle should be erased from the free list. Not called in fast mode.
    bool SplitRect(unsigned freeAreaIndex, const IntRect& reserve);
    /// Clean up redundant free space. Not called in fast mode.
    void Cleanup();

    /// Free rectangles.
    PODVector<IntRect> freeAreas_;
    /// Current size.
    IntVector2 size_;
    /// Maximum size it allows to grow. It is zero when it is not allowed to grow.
    IntVector2 maxSize_;
    /// The dimension use for next growth. Used internally.
    bool doubleWidth_;
    /// Fast mode flag.
    bool fastMode_;
};

}
