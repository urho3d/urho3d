//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "AppState_Base.h"

#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

void AppState_Base::LoadSceneXml(const String& path)
{
    assert(!scene_);
    scene_ = MakeShared<Scene>(context_);
    SharedPtr<File> file = GetSubsystem<ResourceCache>()->GetFile(path);
    scene_->LoadXML(*file);

#ifndef NDEBUG
    Node* cameraNode = scene_->GetChild("Camera");
    assert(cameraNode);
    Camera* camera = cameraNode->GetComponent<Camera>();
    assert(camera);
#endif
}

void AppState_Base::UpdateCurrentFpsElement()
{
    String fpsStr = fpsCounter_.GetCurrentFps() == -1 ? "?" : String(fpsCounter_.GetCurrentFps());
    Text* fpsElement = GetSubsystem<UI>()->GetRoot()->GetChildStaticCast<Text>(CURRENT_FPS_STR);
    fpsElement->SetText("FPS: " + fpsStr);
}

void AppState_Base::SetupViewport()
{
    Node* cameraNode = scene_->GetChild("Camera");
    Camera* camera = cameraNode->GetComponent<Camera>();
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));

    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);
}

void AppState_Base::DestroyViewport()
{
    GetSubsystem<Renderer>()->SetViewport(0, nullptr);
}
