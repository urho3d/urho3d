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
    reset(width, height);
}

void AreaAllocator::reset(int width, int height)
{
    mFreeAreas.clear();
    
    IntRect initialArea(0, 0, width, height);
    mFreeAreas.push_back(initialArea);
}

bool AreaAllocator::reserve(int width, int height, int& x, int& y)
{
    if (width < 0)
        width = 0;
    if (height < 0)
        height = 0;
    
    std::vector<IntRect>::iterator best = mFreeAreas.end();
    int bestFreeArea = M_MAX_INT;
    
    for (std::vector<IntRect>::iterator i = mFreeAreas.begin(); i != mFreeAreas.end(); ++i)
    {
        int freeWidth = i->mRight - i->mLeft;
        int freeHeight = i->mBottom - i->mTop;
        
        if ((freeWidth >= width) && (freeHeight >= height))
        {
            // Calculate rank for free area. Lower is better
            int freeArea = freeWidth * freeHeight;
            
            if ((best == mFreeAreas.end()) || (freeArea < bestFreeArea))
            {
                best = i;
                bestFreeArea = freeArea;
            }
        }
    }
    
    if (best == mFreeAreas.end())
        return false;
    
    IntRect reserved;
    reserved.mLeft = best->mLeft;
    reserved.mTop = best->mTop;
    reserved.mRight = best->mLeft + width;
    reserved.mBottom = best->mTop + height;
    
    x = best->mLeft;
    y = best->mTop;
    
    // Remove the reserved area from all free areas
    for (unsigned i = 0; i < mFreeAreas.size();)
    {
        if (splitRect(mFreeAreas[i], reserved))
            mFreeAreas.erase(mFreeAreas.begin() + i);
        else
            ++i;
    }
    
    cleanup();
    return true;
}

bool AreaAllocator::splitRect(IntRect original, const IntRect& reserve)
{
    if ((reserve.mRight > original.mLeft) && (reserve.mLeft < original.mRight) &&
        (reserve.mBottom > original.mTop) && (reserve.mTop < original.mBottom))
    {
        // Check for splitting from the right
        if (reserve.mRight < original.mRight) 
        {
            IntRect newRect = original;
            newRect.mLeft = reserve.mRight;
            mFreeAreas.push_back(newRect);
        }
        // Check for splitting from the left
        if (reserve.mLeft > original.mLeft)
        {
            IntRect newRect = original;
            newRect.mRight = reserve.mLeft;
            mFreeAreas.push_back(newRect);
        }
        // Check for splitting from the bottom
        if (reserve.mBottom < original.mBottom)
        {
            IntRect newRect = original;
            newRect.mTop = reserve.mBottom;
            mFreeAreas.push_back(newRect);
        }
        // Check for splitting from the top
        if (reserve.mTop > original.mTop)
        {
            IntRect newRect = original;
            newRect.mBottom = reserve.mTop;
            mFreeAreas.push_back(newRect);
        }
        
        return true;
    }
    
    return false;
}

void AreaAllocator::cleanup()
{
    // Remove rects which are contained within another rect
    for (unsigned i = 0; i < mFreeAreas.size(); )
    {
        bool erased = false;
        for (unsigned j = i + 1; j < mFreeAreas.size(); )
        {
            if ((mFreeAreas[i].mLeft >= mFreeAreas[j].mLeft) &&
                (mFreeAreas[i].mTop >= mFreeAreas[j].mTop) &&
                (mFreeAreas[i].mRight <= mFreeAreas[j].mRight) &&
                (mFreeAreas[i].mBottom <= mFreeAreas[j].mBottom))
            {
                mFreeAreas.erase(mFreeAreas.begin() + i);
                erased = true;
                break;
            }
            if ((mFreeAreas[j].mLeft >= mFreeAreas[i].mLeft) &&
                (mFreeAreas[j].mTop >= mFreeAreas[i].mTop) &&
                (mFreeAreas[j].mRight <= mFreeAreas[i].mRight) &&
                (mFreeAreas[j].mBottom <= mFreeAreas[i].mBottom))
                mFreeAreas.erase(mFreeAreas.begin() + j);
            else
                ++j;
        }
        if (!erased)
            ++i;
    }
}
