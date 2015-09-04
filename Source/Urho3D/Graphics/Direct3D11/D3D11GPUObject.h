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

#include "../../Container/Ptr.h"

namespace Urho3D
{

class Graphics;

/// Base class for GPU resources.
class URHO3D_API GPUObject
{
public:
    /// Construct with graphics subsystem pointer.
    GPUObject(Graphics* graphics);
    /// Destruct. Remove from the graphics subsystem.
    virtual ~GPUObject();

    /// Unconditionally release the GPU resource.
    virtual void Release() { }

    /// Clear the data lost flag. No-op on D3D11.
    void ClearDataLost() { }

    /// Return the graphics subsystem.
    Graphics* GetGraphics() const;

    /// Return Direct3D object.
    void* GetGPUObject() const { return object_; }

    /// Return whether data is lost due to device loss. Always false on D3D11.
    bool IsDataLost() const { return false; }

    /// Return whether has pending data assigned while device was lost. Always false on D3D11.
    bool HasPendingData() const { return false; }

protected:
    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Direct3D object.
    void* object_;
};

}
