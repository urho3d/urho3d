#pragma once

#include "Window.h"

namespace Urho3D
{

class Camera;
class Node;
class Scene;
class Texture2D;
class Viewport;

/// %UI element which renders a 3D scene.
class URHO3D_API View3D : public Window
{
    OBJECT(View3D);

public:
    /// Construct.
    View3D(Context* context);
    /// Destruct.
    ~View3D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// React to resize.
    virtual void OnResize();

    /// Define the scene and camera to use in rendering. The View3D will take ownership of them with shared pointers.
    void SetView(Scene* scene, Camera* camera);
    /// Set render texture pixel format. Default is RGB.
    void SetFormat(unsigned format);
    /// Set render target auto update mode. Default is true.
    void SetAutoUpdate(bool enable);
    /// Queue manual update on the render texture.
    void QueueUpdate();
    
    /// Return render texture pixel format.
    unsigned GetFormat() const { return rttFormat_; }
    /// Return whether render target updates automatically.
    bool GetAutoUpdate() const { return autoUpdate_; }
    /// Return scene.
    Scene* GetScene() const;
    /// Return camera scene node.
    Node* GetCameraNode() const;
    /// Return render texture.
    Texture2D* GetRenderTexture() const;
    /// Return viewport.
    Viewport* GetViewport() const;
    
    /// Renderable texture.
    SharedPtr<Texture2D> renderTexture_;
    /// Viewport.
    SharedPtr<Viewport> viewport_;
    /// Scene.
    SharedPtr<Scene> scene_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    /// Render texture format.
    unsigned rttFormat_;
    /// Render texture auto update mode.
    bool autoUpdate_;
};

}
