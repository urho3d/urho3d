//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

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
#include "../Scene/SceneEvents.h"
#include "../Resource/ResourceCache.h"
#include "../IO/Log.h"
#include "../UI/UI.h"
#include "../UI/UIComponent.h"
#include "../UI/UIEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

static int const UICOMPONENT_DEFAULT_TEXTURE_SIZE = 512;
static int const UICOMPONENT_MIN_TEXTURE_SIZE = 64;
static int const UICOMPONENT_MAX_TEXTURE_SIZE = 4096;

class UIElement3D : public UIElement
{
    URHO3D_OBJECT(UIElement3D, UIElement);
public:
    /// Construct.
    explicit UIElement3D(Context* context) : UIElement(context) { }
    /// Destruct.
    ~UIElement3D() override = default;
    /// Set UIComponent which is using this element as root element.
    void SetNode(Node* node) { node_ = node; }
    /// Set active viewport through which this element is rendered. If viewport is not set, it defaults to first viewport.
    void SetViewport(Viewport* viewport) { viewport_ = viewport; }
    /// Convert element coordinates to screen coordinates.
    IntVector2 ElementToScreen(const IntVector2& position) override
    {
        URHO3D_LOGERROR("UIElement3D::ElementToScreen is not implemented.");
        return {-1, -1};
    }
    /// Convert screen coordinates to element coordinates.
    IntVector2 ScreenToElement(const IntVector2& screenPos) override
    {
        IntVector2 result(-1, -1);

        if (node_.Expired())
            return result;

        Scene* scene = node_->GetScene();
        auto* model = node_->GetComponent<StaticModel>();
        if (scene == nullptr || model == nullptr)
            return result;

        auto* renderer = GetSubsystem<Renderer>();
        if (renderer == nullptr)
            return result;

        // \todo Always uses the first viewport, in case there are multiple
        auto* octree = scene->GetComponent<Octree>();
        if (viewport_ == nullptr)
            viewport_ = renderer->GetViewportForScene(scene, 0);

        if (viewport_.Expired() || octree == nullptr)
            return result;

        if (viewport_->GetScene() != scene)
        {
            URHO3D_LOGERROR("UIComponent and Viewport set to component's root element belong to different scenes.");
            return result;
        }

        Camera* camera = viewport_->GetCamera();

        if (camera == nullptr)
            return result;

        IntRect rect = viewport_->GetRect();
        if (rect == IntRect::ZERO)
        {
            auto* graphics = GetSubsystem<Graphics>();
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
            if (queryResult.drawable_ != model)
            {
                // ignore billboard sets by default
                if (queryResult.drawable_->GetTypeInfo()->IsTypeOf(BillboardSet::GetTypeStatic()))
                    continue;
                return result;
            }

            Vector2& uv = queryResult.textureUV_;
            result = IntVector2(static_cast<int>(uv.x_ * GetWidth()),
                static_cast<int>(uv.y_ * GetHeight()));
            return result;
        }
        return result;
    }

protected:
    /// A UIComponent which owns this element.
    WeakPtr<Node> node_;
    /// Viewport which renders this element.
    WeakPtr<Viewport> viewport_;
};

UIComponent::UIComponent(Context* context)
    : Component(context),
    viewportIndex_(0)
{
    texture_ = context_->CreateObject<Texture2D>();
    texture_->SetFilterMode(FILTER_BILINEAR);
    texture_->SetAddressMode(COORD_U, ADDRESS_CLAMP);
    texture_->SetAddressMode(COORD_V, ADDRESS_CLAMP);
    texture_->SetNumLevels(1);                                        // No mipmaps

    rootElement_ = context_->CreateObject<UIElement3D>();
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

UIComponent::~UIComponent() = default;

void UIComponent::RegisterObject(Context* context)
{
    context->RegisterFactory<UIComponent>();
    context->RegisterFactory<UIElement3D>();
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

void UIComponent::OnNodeSet(Node* node)
{
    rootElement_->SetNode(node);
    if (node)
    {
        auto* renderer = GetSubsystem<Renderer>();
        auto* model = node->GetComponent<StaticModel>();
        rootElement_->SetViewport(renderer->GetViewportForScene(GetScene(), viewportIndex_));
        if (model == nullptr)
            model_ = model = node->CreateComponent<StaticModel>();
        model->SetMaterial(material_);
        rootElement_->SetRenderTexture(texture_);
    }
    else
    {
        rootElement_->SetRenderTexture(nullptr);
        if (model_.NotNull())
        {
            model_->Remove();
            model_ = nullptr;
        }
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

    if (texture_->SetSize(width, height, Graphics::GetRGBAFormat(), TEXTURE_RENDERTARGET))
        texture_->GetRenderSurface()->SetUpdateMode(SURFACE_MANUALUPDATE);
    else
        URHO3D_LOGERROR("UIComponent: resizing texture failed.");
}

void UIComponent::SetViewportIndex(unsigned int index)
{
    viewportIndex_ = index;
    if (Scene* scene = GetScene())
    {
        auto* renderer = GetSubsystem<Renderer>();
        Viewport* viewport = renderer->GetViewportForScene(scene, index);
        rootElement_->SetViewport(viewport);
    }
}

}
