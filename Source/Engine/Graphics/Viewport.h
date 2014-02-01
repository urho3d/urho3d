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

#pragma once

#include "Object.h"
#include "Ptr.h"
#include "Rect.h"

namespace Urho3D
{

class Camera;
class RenderPath;
class Scene;
class XMLFile;

/// %Viewport definition either for a render surface or the backbuffer.
class URHO3D_API Viewport : public Object
{
    OBJECT(Viewport);
    
public:
    /// Construct with defaults.
    Viewport(Context* context);
    /// Construct with a full rectangle.
    Viewport(Context* context, Scene* scene, Camera* camera, RenderPath* renderPath = 0);
    /// Construct with a specified rectangle.
    Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath = 0);
    /// Destruct.
    ~Viewport();
    
    /// Set scene.
    void SetScene(Scene* scene);
    /// Set camera.
    void SetCamera(Camera* camera);
    /// Set rectangle.
    void SetRect(const IntRect& rect);
    /// Set rendering path.
    void SetRenderPath(RenderPath* path);
    /// Set rendering path from an XML file.
    void SetRenderPath(XMLFile* file);
    
    /// Return scene.
    Scene* GetScene() const;
    /// Return camera.
    Camera* GetCamera() const;
    /// Return rectangle.
    const IntRect& GetRect() const { return rect_; }
    /// Return rendering path.
    RenderPath* GetRenderPath() const;
    
private:
    /// Scene pointer.
    WeakPtr<Scene> scene_;
    /// Camera pointer.
    WeakPtr<Camera> camera_;
    /// Viewport rectangle.
    IntRect rect_;
    /// Rendering path.
    SharedPtr<RenderPath> renderPath_;
};

}
