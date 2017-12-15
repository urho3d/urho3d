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

#ifndef H_SPK_URHO3D_QUADRENDERER
#define H_SPK_URHO3D_QUADRENDERER

#include "SPK_Urho3D_Renderer.h"
#include <Spark/Extensions/Renderers/SPK_QuadRenderBehavior.h>
#include <Spark/Extensions/Renderers/SPK_Oriented3DRenderBehavior.h>

#include "../Core/Context.h"

namespace SPK {
namespace URHO {

class SPK_URHO_PREFIX Urho3DQuadRenderer :
        public IUrho3DRenderer,
        public QuadRenderBehavior,
        public Oriented3DRenderBehavior
{
    SPK_IMPLEMENT_OBJECT(Urho3DQuadRenderer)

    SPK_START_DESCRIPTION
    SPK_PARENT_ATTRIBUTES(Renderer)
    SPK_ATTRIBUTE("material",ATTRIBUTE_TYPE_STRING)
    SPK_ATTRIBUTE("texture",ATTRIBUTE_TYPE_STRING)
    SPK_ATTRIBUTE("scale",ATTRIBUTE_TYPE_FLOATS)
    SPK_ATTRIBUTE("atlasdim",ATTRIBUTE_TYPE_UINT32S)
    SPK_END_DESCRIPTION

public:

    static Ref<Urho3DQuadRenderer> create(Urho3D::Context* context, float scaleX = 1.0f,float scaleY = 1.0f);


protected:
    virtual void innerImport(const IO::Descriptor& descriptor) override;
    virtual void innerExport(IO::Descriptor& descriptor) const override;

private:

    static const size_t NB_INDICES_PER_PARTICLE = 6;
    static const size_t NB_VERTICES_PER_PARTICLE = 4;
    mutable float _u0, _u1, _v0, _v1;
    Urho3D::PODVector<Urho3D::VertexElement> _elements;

    Urho3DQuadRenderer(Urho3D::Context* context = nullptr, float scaleX = 1.0f,float scaleY = 1.0f);
    Urho3DQuadRenderer(const Urho3DQuadRenderer& renderer);

    virtual RenderBuffer* attachRenderBuffer(const Group& group) const override;
    virtual void render(const Group& group,const DataSet* dataSet,RenderBuffer* renderBuffer) const override;
    virtual void computeAABB(Vector3D& AABBMin,Vector3D& AABBMax,const Group& group,const DataSet* dataSet) const override;

    mutable void (Urho3DQuadRenderer::*renderParticle)(const Particle&, IUrho3DBuffer& renderBuffer) const;	// pointer to the right render method

    void renderBasic(const Particle& particle,IUrho3DBuffer& renderBuffer) const;		// Rendering for particles with texture or no texture
    void renderRot(const Particle& particle,IUrho3DBuffer& renderBuffer) const;         // Rendering for particles with texture or no texture and rotation
    void renderAtlas(const Particle& particle,IUrho3DBuffer& renderBuffer) const;		// Rendering for particles with texture atlas
    void renderAtlasRot(const Particle& particle,IUrho3DBuffer& renderBuffer) const;	// Rendering for particles with texture atlas and rotation
};


inline Ref<Urho3DQuadRenderer> Urho3DQuadRenderer::create(Urho3D::Context* context, float scaleX, float scaleY)
{
    return SPK_NEW(Urho3DQuadRenderer, context, scaleX, scaleY);
}


}}

#endif
