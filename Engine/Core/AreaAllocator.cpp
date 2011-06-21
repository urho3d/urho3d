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

#include "Precompiled.h"
#include "AreaAllocator.h"

AreaAllocator::AreaAllocator(int width, int height)
{
    Reset(width, height);
}

void AreaAllocator::Reset(int width, int height)
{
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
    
    PODVector<IntRect>::Iterator best = freeAreas_.End();
    int bestFreeArea = M_MAX_INT;
    
    for (PODVector<IntRect>::Iterator i = freeAreas_.Begin(); i != freeAreas_.End(); ++i)
    {
        int freeWidth = i->right_ - i->left_;
        int freeHeight = i->bottom_ - i->top_;
        
        if (freeWidth >= width && freeHeight >= height)
        {
            // Calculate rank for free area. Lower is better
            int freeArea = freeWidth * freeHeight;
            
            if (best == freeAreas_.End() || freeArea < bestFreeArea)
            {
                best = i;
                bestFreeArea = freeArea;
            }
        }
    }
    
    if (best == freeAreas_.End())
        return false;
    
    IntRect reserved;
    reserved.left_ = best->left_;
    reserved.top_ = best->top_;
    reserved.right_ = best->left_ + width;
    reserved.bottom_ = best->top_ + height;
    
    x = best->left_;
    y = best->top_;
    
    // Remove the reserved area from all free areas
    for (unsigned i = 0; i < freeAreas_.Size();)
    {
        if (SplitRect(freeAreas_[i], reserved))
            freeAreas_.Erase(i);
        else
            ++i;
    }
    
    Cleanup();
    return true;
}

bool AreaAllocator::SplitRect(IntRect original, const IntRect& reserve)
{
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
    for (unsigned i = 0; i < freeAreas_.Size(); )
    {
        bool erased = false;
        for (unsigned j = i + 1; j < freeAreas_.Size(); )
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
