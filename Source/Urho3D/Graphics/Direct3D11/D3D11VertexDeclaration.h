//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../../Container/RefCounted.h"
#include "../../Container/Vector.h"
#include "../../Graphics/GraphicsDefs.h"

namespace Urho3D
{

class Graphics;
class ShaderVariation;
class VertexBuffer;

/// Vertex declaration.
class URHO3D_API VertexDeclaration : public RefCounted
{
public:
    /// Construct with vertex buffers and element masks to base declaration on.
    VertexDeclaration(Graphics* graphics, ShaderVariation* vertexShader, VertexBuffer** buffers);
    /// Destruct.
    virtual ~VertexDeclaration() override;

    /// Return input layout object corresponding to the declaration.
    void* GetInputLayout() const { return inputLayout_; }

private:
    /// Input layout object.
    void* inputLayout_;
};

}
