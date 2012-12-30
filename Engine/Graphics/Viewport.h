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

#pragma once

#include "Ptr.h"
#include "Rect.h"

namespace Urho3D
{

class Camera;
class PostProcess;
class Scene;
class XMLFile;

/// Rendering path command types.
enum RenderCommandType
{
    CMD_CLEAR = 0,
    CMD_SCENEPASS,
    CMD_QUAD,
    CMD_FORWARDLIGHTS,
    CMD_LIGHTVOLUMES,
    CMD_UNKNOWN
};

/// Rendering path sorting modes.
enum RenderCommandSortMode
{
    SORT_STATE = 0,
    SORT_FRONTTOBACK,
    SORT_BACKTOFRONT
};

/// Rendertarget definition.
struct RenderTargetInfo
{
    /// Name.
    String name_;
    /// Texture format.
    unsigned format_;
    /// Size.
    IntVector2 size_;
    /// Divisor mode flag.
    bool sizeDivisor_;
    /// Filtering flag.
    bool filtered_;
};

/// Rendering path command.
struct RenderPathCommand
{
    /// Command type.
    RenderCommandType type_;
    /// Sorting mode.
    RenderCommandSortMode sortMode_;
    /// Scene pass name.
    String passName_;
    /// Clear flags.
    unsigned clearFlags_;
    /// Clear color.
    Color clearColor_;
    /// Clear depth.
    float clearDepth_;
    /// Clear stencil value.
    unsigned clearStencil_;
    /// Vertex shader name.
    String vertexShaderName_;
    /// Pixel shader name.
    String pixelShaderName_;
    /// Textures.
    String textureNames_[MAX_MATERIAL_TEXTURE_UNITS];
    /// %Shader parameters.
    HashMap<StringHash, Vector4> shaderParameters_;
    /// Output rendertarget names.
    Vector<String> outputs_;
};

/// Rendering path definition.
struct RenderPath
{
    /// Rendertargets.
    Vector<RenderTargetInfo> renderTargets_;
    /// Rendering commands.
    Vector<RenderPathCommand> commands_;
};

/// %Viewport definition either for a render surface or the backbuffer.
class Viewport : public Object
{
    OBJECT(Viewport);
    
public:
    /// Construct with defaults.
    Viewport(Context* context);
    /// Construct with a full rectangle.
    Viewport(Context* context, Scene* scene, Camera* camera, XMLFile* renderPath = 0);
    /// Construct with a specified rectangle.
    Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, XMLFile* renderPath = 0);
    /// Construct with a full rectangle and post-processing effects.
    Viewport(Context* context, Scene* scene, Camera* camera, const Vector<SharedPtr<PostProcess> >& postProcesses, XMLFile* renderPath = 0);
    /// Construct with a specified rectangle and post-processing effects.
    Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, const Vector<SharedPtr<PostProcess> >& postProcesses, XMLFile* renderPath = 0);
    /// Destruct.
    ~Viewport();
    
    /// Set scene.
    void SetScene(Scene* scene);
    /// Set camera.
    void SetCamera(Camera* camera);
    /// Set rectangle.
    void SetRect(const IntRect& rect);
    /// Set rendering path. Return true if successful.
    bool SetRenderPath(XMLFile* file);
    /// Add a post-processing effect at the end of the chain.
    void AddPostProcess(PostProcess* effect);
    /// Insert a post-processing effect at position in the chain.
    void InsertPostProcess(unsigned index, PostProcess* effect);
    /// Remove a post-processing effect.
    void RemovePostProcess(PostProcess* effect);
    /// Remove a post-processing effect by index.
    void RemovePostProcess(unsigned index);
    /// Remove all post-processing effects.
    void RemoveAllPostProcesses();
    
    /// Return scene.
    Scene* GetScene() const;
    /// Return camera.
    Camera* GetCamera() const;
    /// Return rendering path.
    const RenderPath& GetRenderPath() const { return renderPath_; }
    /// Return rectangle.
    const IntRect& GetRect() const { return rect_; }
    /// Return number of post-processing effects.
    unsigned GetNumPostProcesses() const { return postProcesses_.Size(); }
    /// Return post-processing effect at index.
    PostProcess* GetPostProcess(unsigned index) const;
    /// Return all post-processing effects.
    const Vector<SharedPtr<PostProcess> >& GetPostProcesses() const { return postProcesses_; }
    
private:
    /// Scene pointer.
    WeakPtr<Scene> scene_;
    /// Camera pointer.
    WeakPtr<Camera> camera_;
    /// Viewport rectangle.
    IntRect rect_;
    /// Rendering path.
    RenderPath renderPath_;
    /// Post-processing effects.
    Vector<SharedPtr<PostProcess> > postProcesses_;
};

}
