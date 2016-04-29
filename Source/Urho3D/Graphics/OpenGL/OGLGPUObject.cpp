//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GPUObject.h"

#include "../../DebugNew.h"

namespace Urho3D
{

GPUObject::GPUObject(Graphics* graphics) :
    graphics_(graphics),
    object_(0),
    dataLost_(false),
    dataPending_(false)
{
    if (graphics_)
        graphics->AddGPUObject(this);
}

GPUObject::~GPUObject()
{
    if (graphics_)
        graphics_->RemoveGPUObject(this);
}

void GPUObject::OnDeviceLost()
{
    object_ = 0;
}

void GPUObject::ClearDataLost()
{
    dataLost_ = false;
}

Graphics* GPUObject::GetGraphics() const
{
    return graphics_;
}

}
