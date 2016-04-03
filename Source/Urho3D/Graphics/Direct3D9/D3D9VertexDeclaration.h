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

#pragma once

#include "../../Container/RefCounted.h"
#include "../../Container/Vector.h"
#include "../../Graphics/GraphicsDefs.h"

#include <d3d9.h>

namespace Urho3D
{

class Graphics;
class VertexBuffer;

/// One element in a vertex declaration. In contrast to the VertexElement structure, takes into account the stream source index.
struct VertexDeclarationElement
{
    /// Element type.
    VertexElementType type_;
    /// Element semantic.
    VertexElementSemantic semantic_;
    /// Semantic index.
    unsigned char index_;
    /// Stream index.
    unsigned char streamIndex_;
    /// Byte offset.
    unsigned offset_;
};

/// Vertex declaration.
class URHO3D_API VertexDeclaration : public RefCounted
{
public:
    /// Construct with a single buffer's vertex element list.
    VertexDeclaration(Graphics* graphics, const PODVector<VertexElement>& srcElements);
    /// Construct with vertex buffers to base declaration on. Higher index buffers will override semantics on lower indices.
    VertexDeclaration(Graphics* graphics, const PODVector<VertexBuffer*>& buffers);
    /// Construct with vertex buffers (shared pointer vector) to base declaration on. Higher index buffers will override semantics on lower indices.
    VertexDeclaration(Graphics* graphics, const Vector<SharedPtr<VertexBuffer> >& buffers);
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
