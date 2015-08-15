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

#include "../Precompiled.h"

#include "../Math/AreaAllocator.h"

#include "../DebugNew.h"

namespace Urho3D
{

AreaAllocator::AreaAllocator()
{
    Reset(0, 0);
}

AreaAllocator::AreaAllocator(int width, int height, bool fastMode)
{
    Reset(width, height, width, height, fastMode);
}

AreaAllocator::AreaAllocator(int width, int height, int maxWidth, int maxHeight, bool fastMode)
{
    Reset(width, height, maxWidth, maxHeight, fastMode);
}

void AreaAllocator::Reset(int width, int height, int maxWidth, int maxHeight, bool fastMode)
{
    doubleWidth_ = true;
    size_ = IntVector2(width, height);
    maxSize_ = IntVector2(maxWidth, maxHeight);
    fastMode_ = fastMode;

    freeAreas_.Clear();
    IntRect initialArea(0, 0, width, height);
    freeAreas_.Push(initialArea);
}

bool AreaAllocator::Allocate(int width, int height, int& x, int& y)
{
    if (width < 0)
        width = 0;
    if (height < 0)
        height = 0;

    PODVector<IntRect>::Iterator best;
    int bestFreeArea;

    for (;;)
    {
        best = freeAreas_.End();
        bestFreeArea = M_MAX_INT;
        for (PODVector<IntRect>::Iterator i = freeAreas_.Begin(); i != freeAreas_.End(); ++i)
        {
            int freeWidth = i->Width();
            int freeHeight = i->Height();

            if (freeWidth >= width && freeHeight >= height)
            {
                // Calculate rank for free area. Lower is better
                int freeArea = freeWidth * freeHeight;

                if (freeArea < bestFreeArea)
                {
                    best = i;
                    bestFreeArea = freeArea;
                }
            }
        }

        if (best == freeAreas_.End())
        {
            if (doubleWidth_ && size_.x_ < maxSize_.x_)
            {
                int oldWidth = size_.x_;
                size_.x_ <<= 1;
                // If no allocations yet, simply expand the single free area
                IntRect& first = freeAreas_.Front();
                if (freeAreas_.Size() == 1 && first.left_ == 0 && first.top_ == 0 && first.right_ == oldWidth &&
                    first.bottom_ == size_.y_)
                    first.right_ = size_.x_;
                else
                {
                    IntRect newArea(oldWidth, 0, size_.x_, size_.y_);
                    freeAreas_.Push(newArea);
                }
            }
            else if (!doubleWidth_ && size_.y_ < maxSize_.y_)
            {
                int oldHeight = size_.y_;
                size_.y_ <<= 1;
                // If no allocations yet, simply expand the single free area
                IntRect& first = freeAreas_.Front();
                if (freeAreas_.Size() == 1 && first.left_ == 0 && first.top_ == 0 && first.right_ == size_.x_ &&
                    first.bottom_ == oldHeight)
                    first.bottom_ = size_.y_;
                else
                {
                    IntRect newArea(0, oldHeight, size_.x_, size_.y_);
                    freeAreas_.Push(newArea);
                }
            }
            else
                return false;

            doubleWidth_ = !doubleWidth_;
        }
        else
            break;
    }

    IntRect reserved(best->left_, best->top_, best->left_ + width, best->top_ + height);
    x = best->left_;
    y = best->top_;

    if (fastMode_)
    {
        // Reserve the area by splitting up the remaining free area
        best->left_ = reserved.right_;
        if (best->Height() > 2 * height || height >= size_.y_ / 2)
        {
            IntRect splitArea(reserved.left_, reserved.bottom_, best->right_, best->bottom_);
            best->bottom_ = reserved.bottom_;
            freeAreas_.Push(splitArea);
        }
    }
    else
    {
        // Remove the reserved area from all free areas
        for (unsigned i = 0; i < freeAreas_.Size();)
        {
            if (SplitRect(i, reserved))
                freeAreas_.Erase(i);
            else
                ++i;
        }

        Cleanup();
    }

    return true;
}

bool AreaAllocator::SplitRect(unsigned freeAreaIndex, const IntRect& reserve)
{
    // Make a copy, as the vector will be modified
    IntRect original = freeAreas_[freeAreaIndex];

    if (reserve.right_ > original.left_ && reserve.left_ < original.right_ && reserve.bottom_ > original.top_ &&
        reserve.top_ < original.bottom_)
    {
        // Check for splitting from the right
        if (reserve.right_ < original.right_)
        {
            IntRect newRect = original;
            newRect.left_ = reserve.right_;
            freeAreas_.Push(newRect);
        }
        // Check for splitting from the left
        if (reserve.left_ > original.left_)
        {
            IntRect newRect = original;
            newRect.right_ = reserve.left_;
            freeAreas_.Push(newRect);
        }
        // Check for splitting from the bottom
        if (reserve.bottom_ < original.bottom_)
        {
            IntRect newRect = original;
            newRect.top_ = reserve.bottom_;
            freeAreas_.Push(newRect);
        }
        // Check for splitting from the top
        if (reserve.top_ > original.top_)
        {
            IntRect newRect = original;
            newRect.bottom_ = reserve.top_;
            freeAreas_.Push(newRect);
        }

        return true;
    }

    return false;
}

void AreaAllocator::Cleanup()
{
    // Remove rects which are contained within another rect
    for (unsigned i = 0; i < freeAreas_.Size();)
    {
        bool erased = false;
        for (unsigned j = i + 1; j < freeAreas_.Size();)
        {
            if ((freeAreas_[i].left_ >= freeAreas_[j].left_) &&
                (freeAreas_[i].top_ >= freeAreas_[j].top_) &&
                (freeAreas_[i].right_ <= freeAreas_[j].right_) &&
                (freeAreas_[i].bottom_ <= freeAreas_[j].bottom_))
            {
                freeAreas_.Erase(i);
                erased = true;
                break;
            }
            if ((freeAreas_[j].left_ >= freeAreas_[i].left_) &&
                (freeAreas_[j].top_ >= freeAreas_[i].top_) &&
                (freeAreas_[j].right_ <= freeAreas_[i].right_) &&
                (freeAreas_[j].bottom_ <= freeAreas_[i].bottom_))
                freeAreas_.Erase(j);
            else
                ++j;
        }
        if (!erased)
            ++i;
    }
}

}
