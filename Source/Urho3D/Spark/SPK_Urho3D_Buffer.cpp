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

#include "SPK_Urho3D_Buffer.h"

namespace SPK {
namespace URHO {

IUrho3DBuffer::IUrho3DBuffer(Urho3D::Context* context, size_t nbParticles, size_t nbVerticesPerParticle, size_t nbIndicesPerParticle) :
    RenderBuffer()
  , _context(context)
{
    SPK_ASSERT(nbParticles > 0, "IUrho3DBuffer::IUrho3DBuffer - The number of particles cannot be 0");
    SPK_ASSERT(nbVerticesPerParticle > 0, "IUrho3DBuffer::IUrho3DBuffer - The number of vertices per particle cannot be 0");
    SPK_ASSERT(nbIndicesPerParticle > 0, "IUrho3DBuffer::IUrho3DBuffer - The number of indices per particle cannot be 0");

    _vb = new Urho3D::VertexBuffer(_context);
    _ib = new Urho3D::IndexBuffer(_context);
    _geometry = new Urho3D::Geometry(_context);

    _ib->SetShadowed(true);
    _vb->SetShadowed(true);

    _geometry->SetVertexBuffer(0, _vb);
    _geometry->SetIndexBuffer(_ib);
}

IUrho3DBuffer::~IUrho3DBuffer()
{
}

}
}
