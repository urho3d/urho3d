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

#ifndef RENDERER_VERTEXDECLARATION_H
#define RENDERER_VERTEXDECLARATION_H

#include "RefCount.h"
#include "RendererDefs.h"

#include <d3d9.h>
#include <vector>

class Renderer;
class VertexBuffer;

//! Element in the vertex declaration
struct VertexDeclarationElement
{
    //! Stream index
    unsigned mStream;
    //! Element type
    VertexElement mElement;
    //! Element offset
    unsigned mOffset;
};

//! A vertex declaration
class VertexDeclaration : public RefCounted
{
public:
    //! Construct with renderer subsystem pointer and vertex element mask
    VertexDeclaration(Renderer* renderer, unsigned elementMask);
    //! Construct with renderer subsystem pointer and vertex buffers to base declaration on
    VertexDeclaration(Renderer* renderer, const std::vector<VertexBuffer*>& buffers, const std::vector<unsigned>& elementMasks);
    //! Construct with renderer subsystem pointer and vertex buffers to base declaration on
    VertexDeclaration(Renderer* renderer, const std::vector<SharedPtr<VertexBuffer> >& buffers, const std::vector<unsigned>& elementMasks);
    //! Destruct
    ~VertexDeclaration();
    
    //! Return Direct3D vertex declaration
    IDirect3DVertexDeclaration9* getDeclaration() const { return mDeclaration; }
    
private:
    //! Create declaration
    void create(Renderer* renderer, const std::vector<VertexDeclarationElement>& elements);
    //! Release declaration
    void release();
    
    //! Direct3D vertex declaration
    IDirect3DVertexDeclaration9* mDeclaration;
};

#endif // RENDERER_VERTEXDECLARATION_H
