// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

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
    AreaAllocator(i32 width, i32 height, bool fastMode = true);
    /// Construct with given width and height, and set the maximum it allows to grow.
    AreaAllocator(i32 width, i32 height, i32 maxWidth, i32 maxHeight, bool fastMode = true);

    /// Reset to given width and height and remove all previous allocations.
    void Reset(i32 width, i32 height, i32 maxWidth = 0, i32 maxHeight = 0, bool fastMode = true);
    /// Try to allocate an area. Return true if successful, with x & y coordinates filled.
    bool Allocate(i32 width, i32 height, i32& x, i32& y);

    /// Return the current width.
    i32 GetWidth() const { return size_.x_; }

    /// Return the current height.
    i32 GetHeight() const { return size_.y_; }

    /// Return whether uses fast mode. Fast mode uses a simpler allocation scheme which may waste free space, but is OK for eg. fonts.
    bool GetFastMode() const { return fastMode_; }

private:
    /// Remove space from a free rectangle. Return true if the original rectangle should be erased from the free list. Not called in fast mode.
    bool SplitRect(i32 freeAreaIndex, const IntRect& reserve);
    /// Clean up redundant free space. Not called in fast mode.
    void Cleanup();

    /// Free rectangles.
    Vector<IntRect> freeAreas_;
    /// Current size.
    IntVector2 size_;
    /// Maximum size it allows to grow. It is zero when it is not allowed to grow.
    IntVector2 maxSize_;
    /// The dimension use for next growth. Used internally.
    bool doubleWidth_{true};
    /// Fast mode flag.
    bool fastMode_{true};
};

}
