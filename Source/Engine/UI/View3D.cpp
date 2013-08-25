#include "Precompiled.h"
#include "Context.h"
#include "Camera.h"
#include "Graphics.h"
#include "Octree.h"
#include "Scene.h"
#include "Texture2D.h"
#include "Viewport.h"
#include "View3D.h"
#include "UI.h"
#include "UIEvents.h"
#include "Zone.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;

View3D::View3D(Context* context) :
    Window(context),
    rttFormat_(Graphics::GetRGBFormat()),
    autoUpdate_(true)
{
    renderTexture_ = new Texture2D(context_);
    viewport_ = new Viewport(context_);
}

View3D::~View3D()
{
}

void View3D::RegisterObject(Context* context)
{
    context->RegisterFactory<View3D>(UI_CATEGORY);

    COPY_BASE_ATTRIBUTES(View3D, Window);
    // The texture format is API specific, so do not register it as a serializable attribute
    ACCESSOR_ATTRIBUTE(View3D, VAR_BOOL, "Auto Update", GetAutoUpdate, SetAutoUpdate, bool, true, AM_FILE);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE(View3D, "Clip Children", true);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE(View3D, "Is Enabled", true);
}

void View3D::OnResize()
{
    int width = GetWidth();
    int height = GetHeight();
    
    if (width > 0 && height >> 0)
    {
        renderTexture_->SetSize(width, height, rttFormat_, TEXTURE_RENDERTARGET);
        RenderSurface* surface = renderTexture_->GetRenderSurface();
        surface->SetViewport(0, viewport_);
        surface->SetUpdateMode(autoUpdate_ ? SURFACE_UPDATEALWAYS : SURFACE_MANUALUPDATE);

        SetTexture(renderTexture_);
        SetImageRect(IntRect(0, 0, width, height));

        if (!autoUpdate_)
            surface->QueueUpdate();
    }
}

void View3D::SetView(Scene* scene, Camera* camera)
{
    scene_ = scene;
    cameraNode_ = camera ? camera->GetNode() : 0;
    
    viewport_->SetScene(scene_);
    viewport_->SetCamera(camera);
}

void View3D::SetFormat(unsigned format)
{
    if (format != rttFormat_)
    {
        rttFormat_ = format;
        OnResize();
    }
}

void View3D::SetAutoUpdate(bool enable)
{
    if (enable != autoUpdate_)
    {
        autoUpdate_ = enable;
        RenderSurface* surface = renderTexture_->GetRenderSurface();
        if (surface)
            surface->SetUpdateMode(autoUpdate_ ? SURFACE_UPDATEALWAYS : SURFACE_MANUALUPDATE);
    }
}

void View3D::QueueUpdate()
{
    if (!autoUpdate_)
    {
        RenderSurface* surface = renderTexture_->GetRenderSurface();
        if (surface)
            surface->QueueUpdate();
    }
}

Scene* View3D::GetScene() const
{
    return scene_;
}

Node* View3D::GetCameraNode() const
{
    return cameraNode_;
}

Texture2D* View3D::GetRenderTexture() const
{
    return renderTexture_;
}

Viewport* View3D::GetViewport() const
{
    return viewport_;
}

}
