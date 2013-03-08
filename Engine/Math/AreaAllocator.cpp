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

#include "Precompiled.h"
#include "AreaAllocator.h"

namespace Urho3D
{

AreaAllocator::AreaAllocator(int width, int height) :
    size_(width, height),
    maxSize_(IntVector2::ZERO),
    doubleWidth_(true)
{
    Reset(width, height);
}

AreaAllocator::AreaAllocator(int width, int height, int maxWidth, int maxHeight) :
    size_(width, height),
    maxSize_(maxWidth, maxHeight),
    doubleWidth_(true)
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
    
    for(;;)
    {
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
                IntRect newArea(oldWidth, 0, size_.x_, size_.y_);
                freeAreas_.Push(newArea);
            }
            else if (!doubleWidth_ && size_.y_ < maxSize_.y_)
            {
                int oldHeight = size_.y_;
                size_.y_ <<= 1;
                IntRect newArea(0, oldHeight, size_.x_, size_.y_);
                freeAreas_.Push(newArea);
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
    
    // Reserved the area by spliting up the remaining free area
    best->left_ = reserved.right_;
    if (best->Height() > 2 * height)
    {
        IntRect splitArea(reserved.left_, reserved.bottom_, best->right_, best->bottom_);
        best->bottom_ = reserved.bottom_;
        freeAreas_.Push(splitArea);
    }

    return true;
}

}
