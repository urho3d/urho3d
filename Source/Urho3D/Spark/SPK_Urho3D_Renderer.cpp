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

#include "../Spark/SPK_Urho3D_Renderer.h"

namespace SPK {
namespace URHO {

IUrho3DRenderer::IUrho3DRenderer(Urho3D::Context* context, bool NEEDS_DATASET) :
    Renderer(NEEDS_DATASET)
{
    _context = context;
    _camera = nullptr;
    _material = nullptr;
}

void IUrho3DRenderer::setBlendMode(BlendMode blendMode)
{
    switch(blendMode)
    {
    case BLEND_MODE_NONE :
        break;

    case BLEND_MODE_ADD :
        break;

    case BLEND_MODE_ALPHA :
        break;

    default :
        SPK_LOG_WARNING("IUrho3DRenderer::setBlendMode(BlendMode) - Unsupported blending mode. Nothing happens");
        break;
    }
}

void IUrho3DRenderer::updateView(Urho3D::Camera* camera)
{
    _camera = camera;
}

Urho3D::Material* IUrho3DRenderer::getMaterial()
{
    return _material;
}
void IUrho3DRenderer::setMaterial(Urho3D::Material* material)
{
    _material =  material;
}

}
}
