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

#pragma once

#include "Rect.h"

/// Rectangular area allocator.
class AreaAllocator
{
public:
    /// Construct with given width and height.
    AreaAllocator(int width, int height);
    
    /// Reset to given width and height and remove all previous allocations.
    void Reset(int width, int height);
    /// Try to allocate an area. Return true if successful, with x & y coordinates filled.
    bool Allocate(int width, int height, int& x, int& y);

private:
    /// Cut the reserved area from a rectangle. Return true if the rectangle should be removed from the vector.
    bool SplitRect(IntRect original, const IntRect& reserved);
    /// Remove overlapping free rectangles.
    void Cleanup();
    
    /// Free rectangles.
    PODVector<IntRect> freeAreas_;
};
