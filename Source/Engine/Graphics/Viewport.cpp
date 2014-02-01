//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Precompiled.h"
#include "Camera.h"
#include "Graphics.h"
#include "Log.h"
#include "Renderer.h"
#include "RenderPath.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "Viewport.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

Viewport::Viewport(Context* context) :
    Object(context),
    rect_(IntRect::ZERO)
{
    SetRenderPath((RenderPath*)0);
}

Viewport::Viewport(Context* context, Scene* scene, Camera* camera, RenderPath* renderPath) :
    Object(context),
    scene_(scene),
    camera_(camera),
    rect_(IntRect::ZERO)
{
    SetRenderPath(renderPath);
}

Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath) :
    Object(context),
    scene_(scene),
    camera_(camera),
    rect_(rect)
{
    SetRenderPath(renderPath);
}

Viewport::~Viewport()
{
}

void Viewport::SetScene(Scene* scene)
{
    scene_ = scene;
}

void Viewport::SetCamera(Camera* camera)
{
    camera_ = camera;
}

void Viewport::SetRect(const IntRect& rect)
{
    rect_ = rect;
}

void Viewport::SetRenderPath(RenderPath* renderPath)
{
    if (renderPath)
        renderPath_ = renderPath;
    else
    {
        Renderer* renderer = GetSubsystem<Renderer>();
        if (renderer)
            renderPath_ = renderer->GetDefaultRenderPath();
    }
}

void Viewport::SetRenderPath(XMLFile* file)
{
    SharedPtr<RenderPath> newRenderPath(new RenderPath());
    if (newRenderPath->Load(file))
        renderPath_ = newRenderPath;
}

Scene* Viewport::GetScene() const
{
    return scene_;
}

Camera* Viewport::GetCamera() const
{
    return camera_;
}

RenderPath* Viewport::GetRenderPath() const
{
    return renderPath_;
}

}
