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

#include "../../Graphics/GraphicsDefs.h"
#include "../../Container/RefCounted.h"
#include "../../Container/Vector.h"

#include <d3d9.h>

namespace Urho3D
{

class Graphics;
class VertexBuffer;

/// Element in the vertex declaration.
struct VertexDeclarationElement
{
    /// Stream index.
    unsigned stream_;
    /// Element type.
    VertexElement element_;
    /// Element offset.
    unsigned offset_;
};

/// Vertex declaration.
class URHO3D_API VertexDeclaration : public RefCounted
{
public:
    /// Construct with vertex element mask.
    VertexDeclaration(Graphics* graphics, unsigned elementMask);
    /// Construct with vertex buffers and element masks to base declaration on.
    VertexDeclaration(Graphics* graphics, const PODVector<VertexBuffer*>& buffers, const PODVector<unsigned>& elementMasks);
    /// Construct with vertex buffers (shared pointer vector) and element masks to base declaration on.
    VertexDeclaration(Graphics* graphics, const Vector<SharedPtr<VertexBuffer> >& buffers, const PODVector<unsigned>& elementMasks);
    /// Destruct.
    ~VertexDeclaration();
    
    /// Return Direct3D vertex declaration.
    IDirect3DVertexDeclaration9* GetDeclaration() const { return declaration_; }
    
private:
    /// Create declaration.
    void Create(Graphics* graphics, const PODVector<VertexDeclarationElement>& elements);
    /// Release declaration.
    void Release();
    
    /// Direct3D vertex declaration.
    IDirect3DVertexDeclaration9* declaration_;
};

}
