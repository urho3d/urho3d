//
// Copyright (c) 2014-2015, THUNDERBEAST GAMES LLC All rights reserved
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
#include "../Core/Context.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Viewport.h"
#include "../Scene/Scene.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Octree.h"
#include "../Urho2D/Light2D.h"
#include "../Graphics/Renderer.h"
#include "../Resource/XMLFile.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/Material.h"
#include "../Graphics/Technique.h"
#include "../Graphics/Zone.h"

#include "../Urho2D/RigidBody2D.h"
#include "../Urho2D/Renderer2D.h"

#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"


namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

Light2D::Light2D(Context* context) : Component(context),
    lightgroupID_(0),
    color_(Color::WHITE),
    castShadows_(false),
    softShadows_(false),
    softShadowLength_(2.5f),
    backtrace_(false),
    raysInitialized_(false)
{
    SetNumRays(32);
}

Light2D::~Light2D()
{

}

void Light2D::SetNumRays(int numRays)
{
    raysInitialized_ = false;
    rays_.Resize(numRays);
}

void Light2D::OnSceneSet(Scene* scene)
{
    if (scene)
    {
        PODVector<Light2DGroup*> lightgroups;
        scene->GetComponents<Light2DGroup>(lightgroups, true);

        lightgroup_ = 0;
        for (unsigned i = 0; i < lightgroups.Size(); i++)
        {
            Light2DGroup* lightgroup = lightgroups.At(i);
            if (lightgroup->GetLightGroupID() == lightgroupID_)
            {
                lightgroup_ = lightgroup;
                lightgroup_->AddLight2D(this);
                break;
            }
        }

        if (lightgroup_.Null())
        {
            lightgroup_ = node_->CreateComponent<Light2DGroup>();
            lightgroup_->SetTemporary(true);
            lightgroup_->AddLight2D(this);
        }
    }
    else
    {
        if (lightgroup_)
        {
            lightgroup_->RemoveLight2D(this);
            lightgroup_ = 0;
        }

    }
}


void Light2D::OnSetEnabled()
{
    Component::OnSetEnabled();

    if (lightgroup_)
        lightgroup_->SetDirty();

    if (!enabled_)
    {
        vertices_.Clear();
    }
}

void Light2D::AddVertices(Vector<Vertex2D>& vertices)
{
    vertices += vertices_;
}

void Light2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Light2D>(URHO2D_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Component);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("LightGroup", GetLightGroupID, SetLightGroupID, int, 0, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Color", GetColor, SetColor, Color, Color::WHITE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Cast Shadows", GetCastShadows, SetCastShadows, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Num Rays", GetNumRays, SetNumRays, int, 32, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Soft Shadows", GetSoftShadows, SetSoftShadows, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Soft Shadows Length", GetSoftShadowLength, SetSoftShadowLength, float, 2.5f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Backtrace", GetBacktrace, SetBacktrace, bool, false, AM_DEFAULT);

}

void Light2D::CastRays()
{
    if (!raysInitialized_)
        return;

    PhysicsWorld2D* physicsWorld = lightgroup_->GetPhysicsWorld();

    if (physicsWorld && castShadows_) {

        for (unsigned i = 0; i < rays_.Size(); i++) {

            Light2DRay& ray = rays_[i];

            Vector2 oend = ray.end_;
            float distance = (ray.end_ - ray.start_).Length();
            if (Abs(distance < .01f))
                distance = .01f;

            float bestDistance = 999999;

            PODVector<PhysicsRaycastResult2D> results;
            physicsWorld->Raycast(results, ray.start_, ray.end_);

            RigidBody2D* body = NULL;

            for (PODVector<PhysicsRaycastResult2D>::ConstIterator itr = results.Begin(); itr != results.End(); itr++)
            {
                const PhysicsRaycastResult2D& result = *itr;

                if (result.body_->GetCastShadows() && result.distance_  < distance && result.distance_ < bestDistance)
                {
                    bestDistance = result.distance_;
                    body = result.body_;
                    ray.fraction_ = result.distance_ / distance;
                    ray.end_.x_ = result.position_.x_;
                    ray.end_.y_ = result.position_.y_;
                }
            }

            // backtracing can introduce artifacts, for now don't backtrace
            // on static hit... also, may need to clamp on a body size
            if (backtrace_ && body && body->GetBodyType() != BT_STATIC)
            {
                results.Clear();
                bestDistance = -999999;
                physicsWorld->Raycast(results, oend, ray.end_);

                for (PODVector<PhysicsRaycastResult2D>::ConstIterator itr = results.Begin(); itr != results.End(); itr++)
                {
                    const PhysicsRaycastResult2D& result = *itr;

                    if (result.distance_ > bestDistance && result.body_->GetBodyType() != BT_STATIC)
                    {
                        bestDistance = result.distance_;
                        ray.fraction_ = (distance - result.distance_) / distance;
                        ray.end_.x_ = result.position_.x_;
                        ray.end_.y_ = result.position_.y_;
                    }
                }
            }
        }
    }
}

DirectionalLight2D::DirectionalLight2D(Context* context) : Light2D(context),
    direction_(-45.0f)
{
    lightType_ = LIGHT2D_DIRECTIONAL;
}

DirectionalLight2D::~DirectionalLight2D()
{

}

void DirectionalLight2D::RegisterObject(Context* context)
{
    context->RegisterFactory<DirectionalLight2D>(URHO2D_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Light2D);

    URHO3D_ACCESSOR_ATTRIBUTE("Direction", GetDirection, SetDirection, float, -45.0f, AM_DEFAULT);
}

void DirectionalLight2D::UpdateVertices()
{
    if (!lightgroup_ || !enabled_)
    {
        vertices_.Clear();
        return;
    }

    const BoundingBox& frustumBox = lightgroup_->GetFrustumBox();

    float cos = Cos(direction_);
    float sin = Sin(direction_);

    float width = frustumBox.Size().x_;
    float height = frustumBox.Size().y_;

    if (!width || !height)
        return;

    float sizeOfScreen = width > height ? width : height;

    float xAxelOffSet = sizeOfScreen * cos;
    float yAxelOffSet = sizeOfScreen * sin;

    // preventing length <0 assertion error on box2d.
    if ((xAxelOffSet * xAxelOffSet < 0.1f) && (yAxelOffSet * yAxelOffSet < 0.1f)) {
        xAxelOffSet = 1;
        yAxelOffSet = 1;
    }

    float widthOffSet = sizeOfScreen * -sin;
    float heightOffSet = sizeOfScreen * cos;

    float x = (frustumBox.min_.x_ + frustumBox.max_.x_) * 0.5f - widthOffSet;
    float y = (frustumBox.min_.y_ + frustumBox.max_.y_) * 0.5f - heightOffSet;

    unsigned rayNum = rays_.Size();

    float portionX = 2.0f * widthOffSet / (rayNum - 1);
    x = (floorf(x / (portionX * 2))) * portionX * 2;
    float portionY = 2.0f * heightOffSet / (rayNum - 1);
    y = (ceilf(y / (portionY * 2))) * portionY * 2;

    for (unsigned i = 0; i < rayNum; i++)
    {
        Light2DRay& ray = rays_[i];

        float steppedX = float(i) * portionX + x;
        float steppedY = float(i) * portionY + y;

        ray.start_.x_ = steppedX - xAxelOffSet;
        ray.start_.y_ = steppedY - yAxelOffSet;

        ray.end_.x_ = steppedX + xAxelOffSet;
        ray.end_.y_ = steppedY + yAxelOffSet;

        ray.fraction_ = 0.0f;
    }

    raysInitialized_ = true;
    CastRays();

    Vertex2D vertex0;
    Vertex2D vertex1;
    Vertex2D vertex2;
    Vertex2D vertex3;

    vertex0.color_ = vertex1.color_ = vertex2.color_ = vertex3.color_ = color_.ToUInt();
    vertex0.uv_.x_ = 1.0f;
    vertex2.uv_.x_ = 1.0 ;
    vertex1.uv_.x_ = 1.0f;
    vertex3.uv_.x_ = 1.0f;

    int vertexCount = (rayNum - 1) * 6;

    if (softShadows_ && castShadows_)
        vertexCount *= 2;

    if (vertices_.Size() != vertexCount)
        vertices_.Resize(vertexCount);

    Vertex2D* v = &vertices_[0];

    for (unsigned i = 0; i < rayNum - 1; i++) {

        Light2DRay& ray0 = rays_[i];
        Light2DRay& ray1 = rays_[i + 1];

        vertex0.position_.x_ = ray0.start_.x_;
        vertex0.position_.y_ = ray0.start_.y_;

        vertex1.position_.x_ = ray0.end_.x_;
        vertex1.position_.y_ = ray0.end_.y_;

        vertex2.position_.x_ = ray1.start_.x_;
        vertex2.position_.y_ = ray1.start_.y_;

        vertex3.position_.x_ = ray1.end_.x_;
        vertex3.position_.y_ = ray1.end_.y_;

        *v++ = vertex0;
        *v++ = vertex1;
        *v++ = vertex3;

        *v++ = vertex0;
        *v++ = vertex3;
        *v++ = vertex2;

    }

    if (softShadows_ && castShadows_)
    {
        // THIS CAN BE OPTIMIZED!
        for (unsigned i = 0; i < rays_.Size() - 1; i++) {

            Light2DRay& ray0 = rays_[i];
            Light2DRay& ray1 = rays_[i + 1];

            vertex0.position_ = Vector3( ray0.end_.x_, ray0.end_.y_, 0.0f);

            Vector2 v0 = (ray0.end_ - ray0.start_).Normalized();
            Vector2 v1 = (ray1.end_ - ray1.start_).Normalized();

            vertex1.position_ = Vector3( ray0.end_.x_ + v0.x_ * softShadowLength_,
                                         ray0.end_.y_ + v0.y_ * softShadowLength_, 0.0f);


            vertex2.position_ = Vector3( ray1.end_.x_ + v1.x_ * softShadowLength_,
                                         ray1.end_.y_ + v1.y_ * softShadowLength_, 0.0f);

            vertex3.position_ = Vector3( ray1.end_.x_, ray1.end_.y_, 0.0f);


            vertex0.color_ = 0;
            vertex3.color_ = 0;
            vertex0.uv_.x_ = 0;
            vertex3.uv_.x_ = 0;

            vertex1.color_ = 0;
            vertex2.color_ = 0;
            vertex1.uv_.x_ = 1.0;
            vertex2.uv_.x_ = 1.0;

            *v++ = vertex0;
            *v++ = vertex1;
            *v++ = vertex2;

            *v++ = vertex0;
            *v++ = vertex2;
            *v++ = vertex3;

        }

    }

}

PositionalLight2D::PositionalLight2D(Context* context) : Light2D(context)
{

}

PositionalLight2D::~PositionalLight2D()
{

}

void PositionalLight2D::RegisterObject(Context* context)
{
    context->RegisterFactory<PositionalLight2D>(URHO2D_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Light2D);
}

void PositionalLight2D::UpdateVertices()
{
    if (!lightgroup_ || !enabled_)
    {
        vertices_.Clear();
        return;
    }

    CastRays();

    Vertex2D vertex0;
    Vertex2D vertex1;
    Vertex2D vertex2;
    Vertex2D vertex3;

    vertex0.color_ = vertex1.color_ = vertex2.color_ = vertex3.color_ = color_.ToUInt();

    int vertexCount = (rays_.Size() - 1 ) * 3;

    if (softShadows_ && castShadows_)
        vertexCount += (rays_.Size() - 1) * 6;

    if (vertices_.Size() != vertexCount)
        vertices_.Resize(vertexCount);

    Vertex2D* v = &vertices_[0];

    for (unsigned i = 0; i < rays_.Size() - 1; i++) {

        Light2DRay& ray0 = rays_[i];
        Light2DRay& ray1 = rays_[i + 1];

        vertex0.position_.x_ = ray0.start_.x_;
        vertex0.position_.y_ = ray0.start_.y_;

        vertex1.position_.x_ = ray0.end_.x_;
        vertex1.position_.y_ = ray0.end_.y_;

        vertex2.position_.x_ = ray1.end_.x_;
        vertex2.position_.y_ = ray1.end_.y_;

        vertex0.uv_.x_ = 1.0f;
        vertex1.uv_.x_ =  1.0f - ray0.fraction_;
        vertex2.uv_.x_ =  1.0f - ray1.fraction_;

        *v++ = vertex0;
        *v++ = vertex1;
        *v++ = vertex2;

    }

    if (softShadows_ && castShadows_)
    {
        // THIS CAN BE OPTIMIZED!
        for (unsigned i = 0; i < rays_.Size() - 1; i++) {

            Light2DRay& ray0 = rays_[i];
            Light2DRay& ray1 = rays_[i + 1 == rays_.Size() ? 0 : i + 1];

            float s0 = (1.0f - ray0.fraction_);
            float s1 = (1.0f - ray1.fraction_);

            vertex0.position_.x_ = ray0.end_.x_;
            vertex0.position_.y_ = ray0.end_.y_;

            vertex1.position_.x_ = ray0.end_.x_ + s0 * softShadowLength_ * ray0.cos_;
            vertex1.position_.y_ = ray0.end_.y_ + s0 * softShadowLength_ * ray0.sin_;

            vertex2.position_.x_ = ray1.end_.x_ + s1 * softShadowLength_ * ray1.cos_;
            vertex2.position_.y_ = ray1.end_.y_ + s1 * softShadowLength_ * ray1.sin_;

            vertex3.position_.x_ = ray1.end_.x_;
            vertex3.position_.y_ = ray1.end_.y_;

            vertex1.uv_.x_ = 0;
            vertex2.uv_.x_ = 0;
            vertex1.color_ = 0x00000000;
            vertex2.color_ = 0x00000000;
            // darkness of shadow, we should break this all out of uint
            vertex0.uv_.x_ = s0 * .65f;
            vertex3.uv_.x_ = s1 * .65f;

            *v++ = vertex0;
            *v++ = vertex1;
            *v++ = vertex2;

            *v++ = vertex0;
            *v++ = vertex2;
            *v++ = vertex3;

        }

    }
}

PointLight2D::PointLight2D(Context* context) : PositionalLight2D(context),
    radius_(4.0f)
{
    lightType_ = LIGHT2D_POINT;
}

PointLight2D::~PointLight2D()
{

}

void PointLight2D::RegisterObject(Context* context)
{
    context->RegisterFactory<PointLight2D>(URHO2D_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(PositionalLight2D);

    URHO3D_ACCESSOR_ATTRIBUTE("Radius", GetRadius, SetRadius, float, 4.0f, AM_DEFAULT);
}

void PointLight2D::UpdateVertices()
{
    const Node* lightNode = GetNode();

    if (!lightgroup_ || !enabled_ || !lightNode)
    {
        vertices_.Clear();
        return;
    }

    Vector2 start = lightNode->GetWorldPosition2D();

    float angleNum = 360.0f / float((rays_.Size() - 1));
    for (unsigned i = 0; i < rays_.Size(); i++) {
        float angle = angleNum * i;
        Light2DRay& ray = rays_[i];
        ray.start_ = start;
        ray.sin_ = Sin(angle);
        ray.cos_ = Cos(angle);
        ray.end_.x_ = ray.start_.x_ + radius_ * ray.cos_;
        ray.end_.y_ = ray.start_.y_ + radius_ * ray.sin_;
        ray.fraction_ = 1.0f;
    }

    raysInitialized_ = true;
    PositionalLight2D::UpdateVertices();

}


void Light2DGroup::RegisterObject(Context* context)
{
    context->RegisterFactory<Light2DGroup>(URHO2D_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable2D);
}



void Light2DGroup::OnSceneSet(Scene* scene)
{

    if (scene && node_ )
    {
        physicsWorld_ = scene->GetOrCreateComponent<PhysicsWorld2D>();

        Zone* zone = scene->GetComponent<Zone>();
        if (zone)
            SetAmbientColor(zone->GetAmbientColor());

        renderer_ = node_->GetOrCreateComponent<Renderer2D>();
        renderer_->SetTemporary(true);
        renderer_->SetUseTris(true);

        if (light2DMaterial_.Null())
            CreateLight2DMaterial();

        if (IsEnabledEffective())
            renderer_->AddDrawable(this);

        node_->AddListener(this);
    }
    else
    {
        if (renderer_)
            renderer_->RemoveDrawable(this);
    }

}

Light2DGroup::Light2DGroup(Context* context) : Drawable2D(context),
    lightgroupID_(0),
    ambientColor_(0, 0, 0, 0),
    frustum_(0)
{
    sourceBatches_.Resize(1);
    sourceBatches_[0].owner_ = this;
    SubscribeToEvent(E_BEGINRENDERING, URHO3D_HANDLER(Light2DGroup, HandleBeginRendering));
    SubscribeToEvent(E_BEGINVIEWUPDATE, URHO3D_HANDLER(Light2DGroup, HandleBeginViewUpdate));
}

Light2DGroup::~Light2DGroup()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    if (renderer)
    {
        Viewport* viewport = renderer->GetViewport(0);
        if (viewport)
        {
            RenderPath* renderpath = viewport->GetRenderPath();
            if (renderpath)
                renderpath->RemoveCommands("Light2D");
        }

    }

}

void Light2DGroup::HandleBeginViewUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace BeginViewUpdate;

    Scene* scene = GetScene();
    // Check that we are updating the correct scene
    if (scene != eventData[P_SCENE].GetPtr())
        return;

    Camera* camera = static_cast<Camera*>(eventData[P_CAMERA].GetPtr());
    frustum_ = &camera->GetFrustum();
    if (camera->IsOrthographic())// && camera->GetNode()->GetWorldDirection() == Vector3::FORWARD)
    {
        // Define bounding box with min and max points
        // todo: handle rotation
        frustumBoundingBox_.Define(frustum_->vertices_[2], frustum_->vertices_[4]);
    }

}

void Light2DGroup::HandleBeginRendering(StringHash eventType, VariantMap& eventData)
{
    sourceBatchesDirty_ = true;
}

void Light2DGroup::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
    worldBoundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
}

void Light2DGroup::OnDrawOrderChanged()
{
    sourceBatches_[0].drawOrder_ = GetDrawOrder();
}

void Light2DGroup::UpdateSourceBatches()
{
    if (!sourceBatchesDirty_)
        return;

    Vector<Vertex2D>& vertices = sourceBatches_[0].vertices_;
    vertices.Clear();

    for (Vector<WeakPtr<Light2D> >::Iterator itr = lights_.Begin(); itr != lights_.End(); itr++)
    {
        Light2D* light = *itr;

        if (!light->IsEnabled())
            continue;

        light->UpdateVertices();
        light->AddVertices(vertices);
    }

    sourceBatchesDirty_ = false;


}

void Light2DGroup::AddLight2D(Light2D* light)
{
    Vector<WeakPtr<Light2D>>::Iterator itr = lights_.Find(WeakPtr<Light2D>(light));

    if (itr != lights_.End())
        return;

    lights_.Push(WeakPtr<Light2D>(light));

}

void Light2DGroup::RemoveLight2D(Light2D* light)
{

    Vector<WeakPtr<Light2D>>::Iterator itr = lights_.Find(WeakPtr<Light2D>(light));

    if (itr != lights_.End())
        lights_.Erase(itr);

}


void Light2DGroup::SetAmbientColor(const Color& color)
{
    if (color == ambientColor_)
        return;

    ambientColor_ = color;

    Renderer* renderer = GetSubsystem<Renderer>();
    // only on main viewport atm and viewport must first be set
    if (renderer)
    {
        Viewport* viewport = renderer->GetViewport(0);
        if (viewport)
        {
            RenderPath* renderpath = viewport->GetRenderPath();
            renderpath->SetShaderParameter("ShadowAmbient", ambientColor_);
        }
    }

}

void Light2DGroup::CreateLight2DMaterial()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    Viewport* viewport = renderer->GetViewport(0);
    RenderPath* renderpath = viewport->GetRenderPath();

    RenderTargetInfo ntarget;
    ntarget.enabled_ = true;
    ntarget.name_ = "light2dtarget";
    ntarget.tag_ = "Light2D";
    ntarget.format_ = Graphics::GetRGBAFormat();
    ntarget.sizeMode_ = SIZE_VIEWPORTDIVISOR;
    ntarget.size_ = Vector2(4, 4);
    // try true
    ntarget.filtered_ = false;

    renderpath->AddRenderTarget(ntarget);

    RenderPathCommand clearCommand;
    clearCommand.tag_ = "Light2D";
    clearCommand.type_ = CMD_CLEAR;
    clearCommand.clearColor_ = Color(0, 0, 0, 0);
    clearCommand.clearFlags_ = CLEAR_COLOR;
    clearCommand.enabled_ = true;
    clearCommand.SetNumOutputs(1);
    clearCommand.SetOutputName(0, "light2dtarget");
    renderpath->AddCommand(clearCommand);

    RenderPathCommand passCommand;
    passCommand.tag_ = "Light2D";
    passCommand.type_ = CMD_SCENEPASS;
    passCommand.pass_ = "light2d";
    passCommand.enabled_ = true;
    passCommand.SetNumOutputs(1);
    passCommand.SetOutputName(0, "light2dtarget");
    renderpath->AddCommand(passCommand);

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* light2DBlur = cache->GetResource<XMLFile>("PostProcess/Light2DBlur.xml");
    renderpath->Append(light2DBlur);

    RenderPathCommand copyCommand;
    copyCommand.enabled_ = true;
    copyCommand.tag_ = "Light2D";
    copyCommand.type_ = CMD_QUAD;
    copyCommand.vertexShaderName_ = "Shadow2D";
    copyCommand.pixelShaderName_ = "Shadow2D";
    copyCommand.SetTextureName(TU_DIFFUSE, "viewport");
    copyCommand.SetTextureName(TU_EMISSIVE, "light2dtarget");
    copyCommand.SetShaderParameter("ShadowAmbient", ambientColor_);
    copyCommand.SetNumOutputs(1);
    copyCommand.SetOutputName(0, "viewport");
    renderpath->AddCommand(copyCommand);

    light2DMaterial_ = new Material(context_);
    light2DMaterial_->SetName("Light2DMaterial");

    Technique* tech = new Technique(context_);
    Pass* pass = tech->CreatePass("light2d");
    pass->SetBlendMode(BLEND_ADDALPHA);
    pass->SetDepthTestMode(CMP_ALWAYS);

    pass->SetVertexShader("Light2D");
    pass->SetPixelShader("Light2D");

    pass->SetDepthWrite(false);

    light2DMaterial_->SetTechnique(0, tech);
    light2DMaterial_->SetCullMode(CULL_NONE);

    sourceBatches_[0].material_ = light2DMaterial_;

}

}
