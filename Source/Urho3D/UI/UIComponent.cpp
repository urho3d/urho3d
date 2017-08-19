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
#include "UIComponent.h"
#include "../Core/Context.h"
#include "../Graphics/BillboardSet.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Octree.h"
#include "../Graphics/Technique.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Camera.h"
#include "../Graphics/VertexBuffer.h"
#include "../Scene/Scene.h"
#include "../Resource/ResourceCache.h"
#include "../IO/Log.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"


namespace Urho3D
{

static int const UICOMPONENT_DEFAULT_TEXTURE_SIZE = 512;
static int const UICOMPONENT_MIN_TEXTURE_SIZE = 64;
static int const UICOMPONENT_MAX_TEXTURE_SIZE = 4096;

UIComponent::UIComponent(Context* context)
    : Component(context)
{
    vertexBuffer_ = new VertexBuffer(context_);
    debugVertexBuffer_ = new VertexBuffer(context_);
}

void UIComponent::RegisterObject(Context* context)
{
    context->RegisterFactory<UIComponent>();
}

void UIComponent::OnNodeSet(Node* node)
{
    if (node)
    {
        if (texture_.Null())
            SetTextureSize(UICOMPONENT_DEFAULT_TEXTURE_SIZE, UICOMPONENT_DEFAULT_TEXTURE_SIZE);

        if (material_.Null())
        {
            material_ = context_->CreateObject<Material>();
            material_->SetTechnique(0, GetSubsystem<ResourceCache>()->GetResource<Technique>("Techniques/Diff.xml"));
            material_->SetTexture(TU_DIFFUSE, texture_);
        }

        model_ = node->GetComponent<StaticModel>();
        if (model_.Null())
            model_ = node->CreateComponent<StaticModel>();
    }
    else
    {
        material_ = 0;
        texture_ = 0;
        model_ = 0;
        SetElement(0);
    }
}

void UIComponent::SetElement(UIElement* element)
{
    UI* ui = GetSubsystem<UI>();
    if (element)
    {
        // Elements rendered to texture do not belong to normal UI tree. They are treated as top-level elements.
        element->Remove();
        element->SetTraversalMode(TM_DEPTH_FIRST);
        SetTextureSize(element->GetSize());
        SubscribeToEvent(element, E_RESIZED, URHO3D_HANDLER(UIComponent, OnElementResized));
        ui->SetRenderToTexture(this, true);
        if (model_.NotNull())
            model_->SetMaterial(material_);
    }
    else
    {
        if (element_.NotNull())
            element_->SetTraversalMode(TM_BREADTH_FIRST);
        UnsubscribeFromEvent(E_RESIZED);
        ui->SetRenderToTexture(this, false);
        if (model_.NotNull())
            model_->SetMaterial(0);
    }
    element_ = element;
}

void UIComponent::OnElementResized(StringHash eventType, VariantMap& args)
{
    SetTextureSize(args[Resized::P_WIDTH].GetInt(), args[Resized::P_HEIGHT].GetInt());
}

bool UIComponent::SetTextureSize(const IntVector2& size)
{
    return SetTextureSize(size.x_, size.y_);
}

bool UIComponent::SetTextureSize(int width, int height)
{
    if (width < UICOMPONENT_MIN_TEXTURE_SIZE || width > UICOMPONENT_MAX_TEXTURE_SIZE ||
        height < UICOMPONENT_MIN_TEXTURE_SIZE || height > UICOMPONENT_MAX_TEXTURE_SIZE)
    {
        URHO3D_LOGERROR("UIComponent::SetTextureSize() - Attempting to set invalid size, failed");
        return false;
    }

    if (texture_.Null())
        texture_ = context_->CreateObject<Texture2D>();

    if (texture_->SetSize(width, height, GetSubsystem<Graphics>()->GetRGBAFormat(), TEXTURE_RENDERTARGET))
    {
        texture_->SetFilterMode(FILTER_BILINEAR);
        texture_->SetAddressMode(COORD_U, ADDRESS_CLAMP);
        texture_->SetAddressMode(COORD_V, ADDRESS_CLAMP);
        texture_->SetNumLevels(1);                                                // No mipmaps
        texture_->GetRenderSurface()->SetUpdateMode(SURFACE_MANUALUPDATE);
        return true;
    }
    return false;
}

Viewport* UIComponent::GetViewport() const
{
    if (!GetScene())
        return 0;

    Renderer* renderer = GetSubsystem<Renderer>();
    for (unsigned i = 0; i < renderer->GetNumViewports(); ++i)
    {
        Viewport* viewport = renderer->GetViewport(i);
        // Find viewport with same scene
        // TODO: support multiple viewports
        if (viewport && viewport->GetScene() == GetScene())
            return viewport;
    }
    return 0;
}

bool UIComponent::ScreenToUIPosition(IntVector2 screenPos, IntVector2& result)
{
    Viewport* viewport = GetViewport();
    if (!viewport)
        return false;

    Scene* scene = GetScene();
    Camera* camera = viewport->GetCamera();
    Octree* octree = scene->GetComponent<Octree>();

    if (!camera || !octree)
        return false;

    IntRect rect = viewport->GetRect();
    if (rect == IntRect::ZERO)
    {
        Graphics* graphics = GetSubsystem<Graphics>();
        rect.right_ = graphics->GetWidth();
        rect.bottom_ = graphics->GetHeight();
    }

    Ray ray(camera->GetScreenRay((float)screenPos.x_ / rect.Width(), (float)screenPos.y_ / rect.Height()));
    PODVector<RayQueryResult> queryResultVector;
    RayOctreeQuery query(queryResultVector, ray, RAY_TRIANGLE_UV, M_INFINITY, DRAWABLE_GEOMETRY, DEFAULT_VIEWMASK);

    octree->Raycast(query);

    if (queryResultVector.Empty())
        return false;

    for (unsigned i = 0; i < queryResultVector.Size(); i++)
    {
        RayQueryResult& queryResult = queryResultVector[i];
        if (queryResult.drawable_ != model_)
        {
            // ignore billboard sets by default
            if (queryResult.drawable_->GetTypeInfo()->IsTypeOf(BillboardSet::GetTypeStatic()))
                continue;
            return false;
        }

        Vector2& uv = queryResult.textureUV_;
        result = IntVector2(static_cast<int>(uv.x_ * element_->GetWidth()),
                            static_cast<int>(uv.y_ * element_->GetHeight()));
        return true;
    }
    return false;
}

bool UIComponent::IsEnabled() const
{
    return Component::IsEnabled() && model_.NotNull() && texture_.NotNull() && material_.NotNull();;
}

}
