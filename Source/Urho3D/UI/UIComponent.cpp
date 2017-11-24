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


UIComponent::UIComponent(Context* context) : 
    Component(context),
    isStaticModelOwned_(false)
{
    texture_ = context_->CreateObject<Texture2D>();
    texture_->SetFilterMode(FILTER_BILINEAR);
    texture_->SetAddressMode(COORD_U, ADDRESS_CLAMP);
    texture_->SetAddressMode(COORD_V, ADDRESS_CLAMP);
    texture_->SetNumLevels(1);                                        // No mipmaps

    rootElement_ = context_->CreateObject<UIElement3D>();
    rootElement_->SetUIComponent(this);
    rootElement_->SetTraversalMode(TM_BREADTH_FIRST);
    rootElement_->SetEnabled(true);

    material_ = context_->CreateObject<Material>();
    material_->SetTechnique(0, GetSubsystem<ResourceCache>()->GetResource<Technique>("Techniques/Diff.xml"));
    material_->SetTexture(TU_DIFFUSE, texture_);

    SubscribeToEvent(rootElement_, E_RESIZED, URHO3D_HANDLER(UIComponent, OnElementResized));

    // Triggers resizing of texture.
    rootElement_->SetRenderTexture(texture_);
    rootElement_->SetSize(UICOMPONENT_DEFAULT_TEXTURE_SIZE, UICOMPONENT_DEFAULT_TEXTURE_SIZE);
}

UIComponent::~UIComponent()
{
}

void UIComponent::RegisterObject(Context* context)
{
    context->RegisterFactory<UIComponent>();
}

UIElement* UIComponent::GetRoot() const
{
    return rootElement_;
}

Material* UIComponent::GetMaterial() const
{
    return material_;
}

Texture2D* UIComponent::GetTexture() const
{
    return texture_;
}

StaticModel* UIComponent::GetModel() const
{
    return model_;
}

void UIComponent::OnNodeSet(Node* node)
{
    if (node)
    {
        model_ = node->GetComponent<StaticModel>();
        if (model_.Null())
        {
            isStaticModelOwned_ = true;
            model_ = node->CreateComponent<StaticModel>();
        }
        model_->SetMaterial(material_);
        rootElement_->SetRenderTexture(texture_);
    }
    else
    {
        rootElement_->SetRenderTexture(nullptr);
        model_->SetMaterial(nullptr);
        if (isStaticModelOwned_)
        {
            model_->GetNode()->RemoveComponent<StaticModel>();
            isStaticModelOwned_ = false;
        }
        model_ = nullptr;
    }
}

void UIComponent::OnElementResized(StringHash eventType, VariantMap& args)
{
    int width = args[Resized::P_WIDTH].GetInt();
    int height = args[Resized::P_HEIGHT].GetInt();

    if (width < UICOMPONENT_MIN_TEXTURE_SIZE || width > UICOMPONENT_MAX_TEXTURE_SIZE ||
        height < UICOMPONENT_MIN_TEXTURE_SIZE || height > UICOMPONENT_MAX_TEXTURE_SIZE)
    {
        URHO3D_LOGERRORF("UIComponent: Texture size %dx%d is not valid. Width and height should be between %d and %d.",
                         width, height, UICOMPONENT_MIN_TEXTURE_SIZE, UICOMPONENT_MAX_TEXTURE_SIZE);
        return;
    }

    if (texture_->SetSize(width, height, GetSubsystem<Graphics>()->GetRGBAFormat(), TEXTURE_RENDERTARGET))
        texture_->GetRenderSurface()->SetUpdateMode(SURFACE_MANUALUPDATE);
    else
        URHO3D_LOGERROR("UIComponent: resizing texture failed.");
}

IntVector2 UIElement3D::ScreenToElement(const IntVector2& screenPos)
{
    IntVector2 result(-1, -1);

    Scene* scene = component_->GetScene();
    if (!scene)
        return result;

    Renderer* renderer = GetSubsystem<Renderer>();
    if (!renderer)
        return result;

    // \todo Always uses the first viewport, in case there are multiple
    Octree* octree = scene->GetComponent<Octree>();
    Viewport* viewport = viewport_;
    if (viewport == nullptr)
        viewport = renderer->GetViewportForScene(scene, 0);

    if (!viewport || !octree)
        return result;

    if (viewport->GetScene() != scene)
    {
        URHO3D_LOGERROR("UIComponent and Viewport set to component's root element belong to different scenes.");
        return result;
    }

    Camera* camera = viewport->GetCamera();

    if (!camera)
        return result;

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
        return result;

    for (unsigned i = 0; i < queryResultVector.Size(); i++)
    {
        RayQueryResult& queryResult = queryResultVector[i];
        if (queryResult.drawable_ != component_->GetModel())
        {
            // ignore billboard sets by default
            if (queryResult.drawable_->GetTypeInfo()->IsTypeOf(BillboardSet::GetTypeStatic()))
                continue;
            return result;
        }

        Vector2& uv = queryResult.textureUV_;
        result = IntVector2(static_cast<int>(uv.x_ * component_->GetRoot()->GetWidth()),
            static_cast<int>(uv.y_ * component_->GetRoot()->GetHeight()));
        return result;
    }
    return result;
}

IntVector2 UIElement3D::ElementToScreen(const IntVector2& position)
{
    URHO3D_LOGERROR("UIElement3D::ElementToScreen is not implemented.");
    return {-1, -1};
}

void UIElement3D::RegisterObject(Context* context)
{
    context->RegisterFactory<UIElement3D>();
}

UIElement3D::UIElement3D(Context* context)
    : UIElement(context)
{
}

void UIElement3D::SetUIComponent(UIComponent* component)
{
    component_ = component;
}

void UIElement3D::SetViewport(Viewport* viewport)
{
    viewport_ = viewport;
}

}
