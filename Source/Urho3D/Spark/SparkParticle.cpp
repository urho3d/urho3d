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

#include "../Precompiled.h"
#include "../Core/Context.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Material.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/Geometry.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Resource/ResourceCache.h"
#include "../IO/Log.h"

#include "SparkParticle.h"
#include "SparkParticleEffect.h"
#include "SPK_Urho3D_Renderer.h"
#include "SPK_Urho3D_DEF.h"


namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

SparkParticle::SparkParticle(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    sorted_(false),
    animationLodBias_(1.0f),
    animationLodTimer_(0.0f),
    transform_(Matrix3x4::IDENTITY),
    bufferSizeDirty_(true),
    bufferDirty_(true),
    lastTimeStep_(0.0f),
    lastUpdateFrameNumber_(M_MAX_UNSIGNED),
    needUpdate_(false),
    previousOffset_(Vector3::ZERO),
    forceUpdate_(false),
    updateInvisible_(false),
    firstRenderSet_(false)
{
}

SparkParticle::~SparkParticle()
{
}

void SparkParticle::RegisterObject(Context* context)
{
    context->RegisterFactory<SparkParticle>(GEOMETRY_CATEGORY);

    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("SparkEffect", GetEffectAttr, SetEffectAttr, ResourceRef, ResourceRef(SparkParticleEffect::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);   
    URHO3D_ACCESSOR_ATTRIBUTE("Update Invisible", GetUpdateInvisible, SetUpdateInvisible, bool, false, AM_DEFAULT);
}

void SparkParticle::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // If no particles-level testing, use the Drawable test
    if (query.level_ < RAY_TRIANGLE)
    {
        Drawable::ProcessRayQuery(query, results);
        return;
    }

    // Check ray hit distance to AABB before proceeding with particles-level tests
    if (query.ray_.HitDistance(GetWorldBoundingBox()) >= query.maxDistance_)
        return;

    // Approximate the particles as spheres for raycasting
    // TODO
}

void SparkParticle::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    lastTimeStep_ = eventData[P_TIMESTEP].GetFloat();

    // Update if :
    // - first render not yet effectued (needed to compute particles bounding box)
    // - frame has changed
    // - update invibles
    if (!firstRenderSet_ || updateInvisible_ || viewFrameNumber_ != lastUpdateFrameNumber_)
    {
        lastUpdateFrameNumber_ = viewFrameNumber_;
        needUpdate_ = true;
        MarkForUpdate();
    }
}

void SparkParticle::Update(const FrameInfo &frame)
{
    Drawable::Update(frame);

    if (!needUpdate_)
        return;

    UpdateParticles();
    OnMarkedDirty(node_);
    needUpdate_ = false;
}

void SparkParticle::UpdateParticles()
{
    if(_system && _system->isInitialized())
    {
        // Transform spark system with node tranformation
        _system->getTransform().setNC(node_->GetWorldTransform().Data());

        // Update particle system
        _system->updateParticles(lastTimeStep_);

        bufferSizeDirty_ = true;
        bufferDirty_ = true;
    }
}

void SparkParticle::UpdateBatches(const FrameInfo& frame)
{
    // Update information for renderer about this drawable
    const BoundingBox& worldBoundingBox = GetWorldBoundingBox();
    distance_ = frame.camera_->GetDistance(worldBoundingBox.Center());

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        batches_[i].distance_ = distance_;

        SPK::URHO::IUrho3DRenderer* renderer = reinterpret_cast<SPK::URHO::IUrho3DRenderer*>(_system->getGroup(i)->getRenderer().get());
        renderer->updateView(frame.camera_);
    }

    float scale = worldBoundingBox.Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);

    if (newLodDistance != lodDistance_)
        lodDistance_ = newLodDistance;

    if(_system)
    {
        // update spark system camera position

        Matrix3x4 cameraEffectiveTransform = frame.camera_->GetEffectiveWorldTransform();
        _system->setCameraPosition( SPK::Vector3D(
                                        cameraEffectiveTransform.Translation().x_,
                                        cameraEffectiveTransform.Translation().y_,
                                        cameraEffectiveTransform.Translation().z_) );
        /*
         * exemple of computation from camera
         * Matrix3x4 cameraEffectiveTransform = camera_->GetEffectiveWorldTransform();
         * CAMERAPOS = cameraEffectiveTransform.Translation();
         * CAMERAROT = cameraEffectiveTransform.RotationMatrix();
         * VIEWPROJ = camera_->GetProjection();
         * VIEWPROJ = camera_->GetProjection() * camera_->GetView();
        */
    }
}

void SparkParticle::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_)
        UpdateBufferSize();

    if (_system && _system->isInitialized() && bufferDirty_)
        UpdateVertexBuffer(frame);
}

UpdateGeometryType SparkParticle::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_)
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

void SparkParticle::OnWorldBoundingBoxUpdate()
{
    BoundingBox worldBox;

    if(_system)
    {
        SPK::Vector3D AABBMin = _system->getAABBMin();
        SPK::Vector3D AABBMax = _system->getAABBMax();
        worldBox = BoundingBox(Vector3(AABBMin.x, AABBMin.y, AABBMin.z),
                               Vector3(AABBMax.x, AABBMax.y, AABBMax.z));
    }

    worldBoundingBox_ = worldBox;  
}

void SparkParticle::UpdateBufferSize()
{
    // resize index buffer and vertex buffer
    // set index buffer

    bufferSizeDirty_ = false;
    bufferDirty_ = true;
    forceUpdate_ = true;
}

void SparkParticle::UpdateVertexBuffer(const FrameInfo& frame)
{
    // set vertex buffer

    // If using animation LOD, accumulate time and see if it is time to update
    if (animationLodBias_ > 0.0f && lodDistance_ > 0.0f)
    {
        animationLodTimer_ += animationLodBias_ * frame.timeStep_ * ANIMATION_LOD_BASESCALE;
        if (animationLodTimer_ >= lodDistance_)
            animationLodTimer_ = fmodf(animationLodTimer_, lodDistance_);
        else
        {
            // No LOD if immediate update forced
            if (!forceUpdate_)
                return;
        }
    }

    // fill geometry buffers
    _system->renderParticles();

    // do only on first render
    if(!firstRenderSet_)
    {
        // for each group, set batches geometries
        for (size_t i = 0; i < _system->getNbGroups(); ++i)
        {
            SPK::URHO::IUrho3DBuffer* renderBuffer = (SPK::URHO::IUrho3DBuffer*)_system->getGroup(i)->getRenderBuffer();
            assert(renderBuffer);

            // link Drawable batches geometries to spark particle system renderBuffer geometries
            batches_[i].geometry_ = renderBuffer->getGeometry();
        }

        firstRenderSet_ = true;
    }

    bufferDirty_ = false;
    forceUpdate_ = false;
}

void SparkParticle::Commit()
{
    MarkPositionsDirty();
    MarkNetworkUpdate();
}

void SparkParticle::MarkPositionsDirty()
{
    Drawable::OnMarkedDirty(node_);
    bufferDirty_ = true;
}

void SparkParticle::OnSceneSet(Scene* scene)
{
    Drawable::OnSceneSet(scene);

    if (scene && IsEnabledEffective())
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(SparkParticle, HandleScenePostUpdate));
    else if (!scene)
         UnsubscribeFromEvent(E_SCENEPOSTUPDATE);
}

void SparkParticle::OnSetEnabled()
{
    Drawable::OnSetEnabled();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(SparkParticle, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void SparkParticle::SetUpdateInvisible(bool enable)
{
    updateInvisible_ = enable;
    MarkNetworkUpdate();
}

void SparkParticle::SetSystem(SPK::Ref<SPK::System> system)
{
    _system = SPK::SPKObject::copy(system);
    //_system = system;

    if(_system)
    {
        // force spark to use axis aligned bounding box as urho3d culling need it
        _system->enableAABBComputation(true);

        // get nb groups in system and resize batches
        size_t nbGroup = _system->getNbGroups();
        batches_.Resize(nbGroup);

        // for each group, set a batch
        for (size_t i = 0; i < nbGroup; ++i)
        {
            batches_[i].geometryType_ = GEOM_STATIC;
            batches_[i].worldTransform_ = &transform_;
            batches_[i].numWorldTransforms_ = 1;

            SPK::URHO::IUrho3DRenderer* renderer = reinterpret_cast<SPK::URHO::IUrho3DRenderer*>(_system->getGroup(i)->getRenderer().get());
            SPK_ASSERT(renderer, "Renderer is null");

            batches_[i].material_ = renderer->getMaterial();

            // set render order
            batches_[i].material_->SetRenderOrder(128+i);
        }
    }
}

void SparkParticle::SetEffect(SparkParticleEffect* sparkEffect)
{
    if(sparkEffect)
    {
        SetSystem(sparkEffect->GetSystem());
        sparkEffect_ = sparkEffect;
    }
}

void SparkParticle::SetEffectAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetEffect(cache->GetResource<SparkParticleEffect>(value.name_));
}

ResourceRef SparkParticle::GetEffectAttr() const
{
    if(sparkEffect_)
    {
        return GetResourceRef(sparkEffect_, SparkParticleEffect::GetTypeStatic());
    }
    else
    {
        SPK_LOG_DEBUG("[SparkParticle::GetEffectAttr] : sparkEffect_ not set.");
        return ResourceRef(String::EMPTY);
    }
}


}




