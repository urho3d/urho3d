//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "PostProcess.h"
#include "Scene.h"
#include "Viewport.h"

#include "DebugNew.h"

namespace Urho3D
{

Viewport::Viewport() :
    rect_(IntRect::ZERO)
{
}

Viewport::Viewport(Scene* scene, Camera* camera) :
    scene_(scene),
    camera_(camera),
    rect_(IntRect::ZERO)
{
}

Viewport::Viewport(Scene* scene, Camera* camera, const IntRect& rect) :
    scene_(scene),
    camera_(camera),
    rect_(rect)
{
}

Viewport::Viewport(Scene* scene, Camera* camera, const Vector<SharedPtr<PostProcess> >& postProcesses) :
    scene_(scene),
    camera_(camera),
    rect_(IntRect::ZERO),
    postProcesses_(postProcesses)
{
}

Viewport::Viewport(Scene* scene, Camera* camera, const IntRect& rect, const Vector<SharedPtr<PostProcess> >& postProcesses) :
    scene_(scene),
    camera_(camera),
    rect_(rect),
    postProcesses_(postProcesses)
{
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

void Viewport::AddPostProcess(PostProcess* effect)
{
    if (!effect)
        return;
    
    SharedPtr<PostProcess> effectPtr(effect);
    if (!postProcesses_.Contains(effectPtr))
        postProcesses_.Push(effectPtr);
}

void Viewport::InsertPostProcess(unsigned index, PostProcess* effect)
{
    if (!effect)
        return;
    
    SharedPtr<PostProcess> effectPtr(effect);
    if (postProcesses_.Contains(effectPtr))
        return;
    
    if (index >= postProcesses_.Size())
        postProcesses_.Push(effectPtr);
    else
        postProcesses_.Insert(index, effectPtr);
}

void Viewport::RemovePostProcess(PostProcess* effect)
{
    for (Vector<SharedPtr<PostProcess> >::Iterator i = postProcesses_.Begin(); i != postProcesses_.End(); ++i)
    {
        if (i->Get() == effect)
        {
            postProcesses_.Erase(i);
            return;
        }
    }
}

void Viewport::RemovePostProcess(unsigned index)
{
    postProcesses_.Erase(index);
}

void Viewport::RemoveAllPostProcesses()
{
    postProcesses_.Clear();
}

Scene* Viewport::GetScene() const
{
    return scene_;
}

Camera* Viewport::GetCamera() const
{
    return camera_;
}

PostProcess* Viewport::GetPostProcess(unsigned index) const
{
    return index < postProcesses_.Size() ? postProcesses_[index] : (PostProcess*)0;
}

}
