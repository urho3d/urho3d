//
// Copyright (c) 2008-2017 the Urho3D project.
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

#ifndef H_SPK_URHO3DBUFFER
#define H_SPK_URHO3DBUFFER

#include <Spark/SPARK_Core.h>

#include "SPK_Urho3D_DEF.h"

#include "../Graphics/Geometry.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"

namespace SPK {
namespace URHO {

class SPK_URHO_PREFIX IUrho3DBuffer : public RenderBuffer
{

public :

    IUrho3DBuffer(Urho3D::Context *context, size_t nbParticles, size_t nbVerticesPerParticle, size_t nbIndicesPerParticle);
    ~IUrho3DBuffer();

    Urho3D::SharedPtr<Urho3D::Geometry>     getGeometry();
    Urho3D::VertexBuffer*                   getVertexBuffer() { return _vb; }
    Urho3D::IndexBuffer*                    getIndexBuffer() { return _ib; }

private:

    Urho3D::Context*                        _context;
    Urho3D::SharedPtr<Urho3D::Geometry>     _geometry;
    Urho3D::SharedPtr<Urho3D::VertexBuffer> _vb;
    Urho3D::SharedPtr<Urho3D::IndexBuffer>  _ib;

};


inline Urho3D::SharedPtr<Urho3D::Geometry> IUrho3DBuffer::getGeometry()
{
    return _geometry;
}

}}

#endif
