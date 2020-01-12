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
#include "../Graphics/RibbonTrail.h"
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

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;
static const unsigned MAX_TAIL_COLUMN = 16;

const char* trailTypeNames[] =
{
    "Face Camera",
    "Bone",
    nullptr
};

inline bool CompareTails(TrailPoint* lhs, TrailPoint* rhs)
{
    return lhs->sortDistance_ > rhs->sortDistance_;
}

TrailPoint::TrailPoint(const Vector3& position, const Vector3& forward) :
    position_{position},
    forward_{forward}
{
}

RibbonTrail::RibbonTrail(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    geometry_(new Geometry(context_)),
    animationLodBias_(1.0f),
    animationLodTimer_(0.0f),
    vertexBuffer_(new VertexBuffer(context_)),
    indexBuffer_(new IndexBuffer(context_)),
    transforms_(Matrix3x4::IDENTITY),
    bufferSizeDirty_(false),
    bufferDirty_(true),
    previousPosition_(Vector3::ZERO),
    numPoints_(0),
    lifetime_(1.0f),
    vertexDistance_(0.1f),
    width_(0.2f),
    startScale_(1.0f),
    endScale_(1.0f),
    lastTimeStep_(0.0f),
    endColor_(Color(1.0f, 1.0f, 1.0f, 0.0f)),
    startColor_(Color(1.0f, 1.0f, 1.0f, 1.0f)),
    lastUpdateFrameNumber_(M_MAX_UNSIGNED),
    needUpdate_(false),
    sorted_(false),
    previousOffset_(Vector3::ZERO),
    forceUpdate_(false),
    trailType_(TT_FACE_CAMERA),
    tailColumn_(1),
    updateInvisible_(false),
    emitting_(true),
    startEndTailTime_(0.0f)
{
    geometry_->SetVertexBuffer(0, vertexBuffer_);
    geometry_->SetIndexBuffer(indexBuffer_);

    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    batches_[0].geometryType_ = GEOM_TRAIL_FACE_CAMERA;
    batches_[0].worldTransform_ = &transforms_;
    batches_[0].numWorldTransforms_ = 1;
}

RibbonTrail::~RibbonTrail() = default;

void RibbonTrail::RegisterObject(Context* context)
{
    context->RegisterFactory<RibbonTrail>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Emitting", IsEmitting, SetEmitting, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Update Invisible", GetUpdateInvisible, SetUpdateInvisible, bool, false, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Trail Type", GetTrailType, SetTrailType, TrailType, trailTypeNames, TT_FACE_CAMERA, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Base Velocity", GetBaseVelocity, SetBaseVelocity, Vector3, Vector3::ZERO, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Tail Lifetime", GetLifetime, SetLifetime, float, 1.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Tail Column", GetTailColumn, SetTailColumn, unsigned, 0, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Vertex Distance", GetVertexDistance, SetVertexDistance, float, 0.1f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Width", GetWidth, SetWidth, float, 0.2f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Start Scale", GetStartScale, SetStartScale, float, 1.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("End Scale", GetEndScale, SetEndScale, float, 1.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Start Color", GetStartColor, SetStartColor, Color, Color::WHITE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("End Color", GetEndColor, SetEndColor, Color, Color(1.0f, 1.0f, 1.0f, 0.0f), AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Animation LOD Bias", GetAnimationLodBias, SetAnimationLodBias, float, 1.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Sort By Distance", IsSorted, SetSorted, bool, false, AM_DEFAULT);
}

void RibbonTrail::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // If no trail-level testing, use the Drawable test
    if (query.level_ < RAY_TRIANGLE)
    {
        Drawable::ProcessRayQuery(query, results);
        return;
    }

    // Check ray hit distance to AABB before proceeding with trail-level tests
    if (query.ray_.HitDistance(GetWorldBoundingBox()) >= query.maxDistance_)
        return;

    // Approximate the tails as spheres for raycasting
    for (unsigned i = 0; i < points_.Size() - 1; ++i)
    {
        Vector3 center = (points_[i].position_ + points_[i+1].position_) * 0.5f;
        Vector3 scale = width_ * Vector3::ONE;
        // Tail should be represented in cylinder shape, but we don't have this yet on Urho,
        // so this implementation will use bounding box instead (hopefully only temporarily)
        float distance = query.ray_.HitDistance(BoundingBox(center - scale, center + scale));
        if (distance < query.maxDistance_)
        {
            // If the code reaches here then we have a hit
            RayQueryResult result;
            result.position_ = query.ray_.origin_ + distance * query.ray_.direction_;
            result.normal_ = -query.ray_.direction_;
            result.distance_ = distance;
            result.drawable_ = this;
            result.node_ = node_;
            result.subObject_ = i;
            results.Push(result);
        }
    }
}

void RibbonTrail::OnSetEnabled()
{
    Drawable::OnSetEnabled();

    previousPosition_ = node_->GetWorldPosition();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(RibbonTrail, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void RibbonTrail::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    lastTimeStep_ = eventData[P_TIMESTEP].GetFloat();

    // Update if frame has changed
    if (updateInvisible_ || viewFrameNumber_ != lastUpdateFrameNumber_)
    {
        // Reset if ribbon trail is too small and too much difference in frame
        if (points_.Size() < 3 && viewFrameNumber_ - lastUpdateFrameNumber_ > 1)
        {
            previousPosition_ = node_->GetWorldPosition();
            points_.Erase(0, points_.Size());
        }

        lastUpdateFrameNumber_ = viewFrameNumber_;
        needUpdate_ = true;
        MarkForUpdate();
    }
}

void RibbonTrail::Update(const FrameInfo &frame)
{
    Drawable::Update(frame);

    if (!needUpdate_)
        return;

    UpdateTail(frame.timeStep_);
    OnMarkedDirty(node_);
    needUpdate_ = false;
}

void RibbonTrail::UpdateTail(float timeStep)
{
    // Apply base velocity to all cached positions
    if (baseVelocity_ != Vector3::ZERO)
    {
        for (TrailPoint& point : points_)
            point.position_ += baseVelocity_ * timeStep;
        previousPosition_ += baseVelocity_ * timeStep;
    }

    const Vector3 worldPosition = node_->GetWorldPosition();
    const float path = (previousPosition_ - worldPosition).Length();

    // Update tails lifetime
    int expiredIndex = -1;
    if (points_.Size() > 0)
    {
        // No need to update last point
        for (unsigned i = 0; i < points_.Size() - 1; ++i)
        {
            points_[i].lifetime_ += lastTimeStep_;

            // Get point index with expired lifetime
            if (points_[i].lifetime_ > lifetime_)
                expiredIndex = i;
        }
    }

    // Delete expired points
    if (expiredIndex != -1)
    {
        points_.Erase(0, (unsigned)(expiredIndex + 1));

        // Update endTail pointer
        if (points_.Size() > 1)
        {
            endTail_.position_ = points_[0].position_;
            startEndTailTime_ = points_[0].lifetime_;
        }
    }

    // Update previous world position if trail is still zero
    if (points_.Size() == 0)
    {
        previousPosition_ = worldPosition;
    }
    // Delete lonely point
    else if (points_.Size() == 1)
    {
        points_.Erase(0, 1);
        previousPosition_ = worldPosition;
    }
    // Update end of trail position using endTail linear interpolation
    else if (points_.Size() > 1 && points_[0].lifetime_ < lifetime_)
    {
        const float step = SmoothStep(startEndTailTime_, lifetime_, points_[0].lifetime_);
        points_[0].position_ = Lerp(endTail_.position_, points_[1].position_, step);
        bufferDirty_ = true;
    }

    // Add starting points
    if (points_.Size() == 0 && path > M_LARGE_EPSILON && emitting_)
    {
        const Vector3 forwardMotion = (previousPosition_ - worldPosition).Normalized();

        TrailPoint startPoint{previousPosition_, forwardMotion};
        TrailPoint nextPoint{worldPosition, forwardMotion};

        if (node_->GetParent() != nullptr)
        {
            startPoint.parentPos_ = node_->GetParent()->GetWorldPosition();
            nextPoint.parentPos_ = node_->GetParent()->GetWorldPosition();
        }

        points_.Push(startPoint);
        points_.Push(nextPoint);

        // Update endTail
        endTail_.position_ = startPoint.position_;
        startEndTailTime_ = 0.0f;
    }

    // Add more points
    if (points_.Size() > 1 && emitting_)
    {
        const Vector3 forwardMotion = (previousPosition_ - worldPosition).Normalized();

        // Add more points if path exceeded tail length
        if (path > vertexDistance_)
        {
            TrailPoint newPoint{worldPosition, forwardMotion};
            if (node_->GetParent() != nullptr)
                newPoint.parentPos_ = node_->GetParent()->GetWorldPosition();

            points_.Push(newPoint);

            previousPosition_ = worldPosition;
        }
        else
        {
            // Update recent tail
            points_.Back().position_ = worldPosition;
            if (forwardMotion != Vector3::ZERO)
                points_.Back().forward_ = forwardMotion;
        }
    }

    // Update buffer size if size of points different with tail number
    if (points_.Size() != numPoints_)
        bufferSizeDirty_ = true;
}

void RibbonTrail::SetEndScale(float endScale)
{
    endScale_ = endScale;
    Commit();
}

void RibbonTrail::SetStartScale(float startScale)
{
    startScale_ = startScale;
    Commit();
}

void RibbonTrail::SetEmitting(bool emitting)
{
    if (emitting == emitting_)
        return;

    emitting_ = emitting;

    // Reset already available points
    if (emitting && points_.Size() > 0)
    {
        points_.Clear();
        bufferSizeDirty_ = true;
    }

    Drawable::OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void RibbonTrail::SetTailColumn(unsigned tailColumn)
{
    if (tailColumn > MAX_TAIL_COLUMN)
    {
        URHO3D_LOGWARNING("Max ribbon trail tail column is " + String(MAX_TAIL_COLUMN));
        tailColumn_ = MAX_TAIL_COLUMN;
    }
    else if (tailColumn < 1)
    {
        tailColumn_ = 1;
    }
    else
        tailColumn_ = tailColumn;

    Drawable::OnMarkedDirty(node_);
    bufferSizeDirty_ = true;
    MarkNetworkUpdate();
}

void RibbonTrail::UpdateBatches(const FrameInfo& frame)
{
    // Update information for renderer about this drawable
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());
    batches_[0].distance_ = distance_;

    // Calculate scaled distance for animation LOD
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    // If there are no trail, the size becomes zero, and LOD'ed updates no longer happen. Disable LOD in that case
    if (scale > M_EPSILON)
        lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    else
        lodDistance_ = 0.0f;

    Vector3 worldPos = node_->GetWorldPosition();
    Vector3 offset = (worldPos - frame.camera_->GetNode()->GetWorldPosition());
    if (sorted_ && offset != previousOffset_)
    {
        bufferDirty_ = true;
        previousOffset_ = offset;
    }
}

void RibbonTrail::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_ || indexBuffer_->IsDataLost())
        UpdateBufferSize();

    if (bufferDirty_ || vertexBuffer_->IsDataLost())
        UpdateVertexBuffer(frame);
}

UpdateGeometryType RibbonTrail::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

void RibbonTrail::SetMaterial(Material* material)
{
    batches_[0].material_ = material;
    MarkNetworkUpdate();
}

void RibbonTrail::OnSceneSet(Scene* scene)
{
    Drawable::OnSceneSet(scene);

    if (scene && IsEnabledEffective())
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(RibbonTrail, HandleScenePostUpdate));
    else if (!scene)
         UnsubscribeFromEvent(E_SCENEPOSTUPDATE);
}

void RibbonTrail::OnWorldBoundingBoxUpdate()
{
    BoundingBox worldBox;

    for (unsigned i = 0; i < points_.Size(); ++i)
    {
        Vector3 &p = points_[i].position_;
        Vector3 scale = width_ * Vector3::ONE;
        worldBox.Merge(BoundingBox(p - scale, p + scale));
    }

    worldBoundingBox_ = worldBox;
}

void RibbonTrail::UpdateBufferSize()
{
    numPoints_ = points_.Size();

    unsigned indexPerSegment = 6 + (tailColumn_ - 1) * 6;
    unsigned vertexPerSegment = 4 + (tailColumn_ - 1) * 2;

    unsigned mask = 0;

    if (trailType_ == TT_FACE_CAMERA)
    {
        batches_[0].geometryType_ = GEOM_TRAIL_FACE_CAMERA;
        mask =  MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TANGENT;
    }
    else if (trailType_ == TT_BONE)
    {
        batches_[0].geometryType_ = GEOM_TRAIL_BONE;
        mask =  MASK_POSITION | MASK_NORMAL | MASK_COLOR | MASK_TEXCOORD1 | MASK_TANGENT;
    }

    bufferSizeDirty_ = false;
    bufferDirty_ = true;
    forceUpdate_ = true;

    if (numPoints_ < 2)
    {
        indexBuffer_->SetSize(0, false);
        vertexBuffer_->SetSize(0, mask, true);
        return;
    }
    else
    {
        indexBuffer_->SetSize(((numPoints_ - 1) * indexPerSegment), false);
        vertexBuffer_->SetSize(numPoints_ * vertexPerSegment, mask, true);
    }

    // Indices do not change for a given tail generator capacity
    auto* dest = (unsigned short*)indexBuffer_->Lock(0, ((numPoints_ - 1) * indexPerSegment), true);
    if (!dest)
        return;

    unsigned vertexIndex = 0;
    unsigned stripsLen = numPoints_ - 1;

    while (stripsLen--)
    {
        dest[0] = (unsigned short)vertexIndex;
        dest[1] = (unsigned short)(vertexIndex + 2);
        dest[2] = (unsigned short)(vertexIndex + 1);

        dest[3] = (unsigned short)(vertexIndex + 1);
        dest[4] = (unsigned short)(vertexIndex + 2);
        dest[5] = (unsigned short)(vertexIndex + 3);

        dest += 6;
        vertexIndex += 2;

        for (unsigned i = 0; i < (tailColumn_ - 1); ++i)
        {
            dest[0] = (unsigned short)vertexIndex;
            dest[1] = (unsigned short)(vertexIndex + 2);
            dest[2] = (unsigned short)(vertexIndex + 1);

            dest[3] = (unsigned short)(vertexIndex + 1);
            dest[4] = (unsigned short)(vertexIndex + 2);
            dest[5] = (unsigned short)(vertexIndex + 3);

            dest += 6;
            vertexIndex += 2;
        }

       vertexIndex += 2;

    }

    indexBuffer_->Unlock();
    indexBuffer_->ClearDataLost();
}

void RibbonTrail::UpdateVertexBuffer(const FrameInfo& frame)
{
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

    // if tail path is short and nothing to draw, exit
    if (numPoints_ < 2)
    {
        batches_[0].geometry_->SetDrawRange(TRIANGLE_LIST, 0, 0, false);
        return;
    }

    unsigned indexPerSegment = 6 + (tailColumn_ - 1) * 6;
    unsigned vertexPerSegment = 4 + (tailColumn_ - 1) * 2;

    // Fill sorted points vector
    sortedPoints_.Resize(numPoints_);
    for (unsigned i = 0; i < numPoints_; ++i)
    {
        TrailPoint& point = points_[i];
        sortedPoints_[i] = &point;
        if (sorted_)
            point.sortDistance_ = frame.camera_->GetDistanceSquared(point.position_);
    }

    // Sort points
    if (sorted_)
        Sort(sortedPoints_.Begin(), sortedPoints_.End(), CompareTails);

    // Update individual trail elapsed length
    float trailLength = 0.0f;
    for(unsigned i = 0; i < numPoints_; ++i)
    {
        float length = i == 0 ? 0.0f : (points_[i].position_ - points_[i-1].position_).Length();
        trailLength += length;
        points_[i].elapsedLength_ = trailLength;
        if (i < numPoints_ - 1)
            points_[i].next_ = &points_[i+1];
    }

    batches_[0].geometry_->SetDrawRange(TRIANGLE_LIST, 0, (numPoints_ - 1) * indexPerSegment, false);
    bufferDirty_ = false;
    forceUpdate_ = false;

    auto* dest = (float*)vertexBuffer_->Lock(0, (numPoints_ - 1) * vertexPerSegment, true);
    if (!dest)
        return;

    // Generate trail mesh
    if (trailType_ == TT_FACE_CAMERA)
    {
        for (unsigned i = 0; i < numPoints_; ++i)
        {
            TrailPoint& point = *sortedPoints_[i];

            if (sortedPoints_[i] == &points_.Back()) continue;

            // This point
            float factor = SmoothStep(0.0f, trailLength, point.elapsedLength_);
            unsigned c = endColor_.Lerp(startColor_, factor).ToUInt();
            float width = Lerp(width_ * endScale_, width_ * startScale_, factor);

            // Next point
            float nextFactor = SmoothStep(0.0f, trailLength, point.next_->elapsedLength_);
            unsigned nextC = endColor_.Lerp(startColor_, nextFactor).ToUInt();
            float nextWidth = Lerp(width_ * endScale_, width_ * startScale_, nextFactor);

            // First row
            dest[0] = point.position_.x_;
            dest[1] = point.position_.y_;
            dest[2] = point.position_.z_;
            ((unsigned&)dest[3]) = c;
            dest[4] = factor;
            dest[5] = 0.0f;
            dest[6] = point.forward_.x_;
            dest[7] = point.forward_.y_;
            dest[8] = point.forward_.z_;
            dest[9] = width;

            dest[10] = point.next_->position_.x_;
            dest[11] = point.next_->position_.y_;
            dest[12] = point.next_->position_.z_;
            ((unsigned&)dest[13]) = nextC;
            dest[14] = nextFactor;
            dest[15] = 0.0f;
            dest[16] = point.next_->forward_.x_;
            dest[17] = point.next_->forward_.y_;
            dest[18] = point.next_->forward_.z_;
            dest[19] = nextWidth;

            dest += 20;

            // Middle rows
            for (unsigned j = 0; j < (tailColumn_ - 1); ++j)
            {
                float elapsed = 1.0f / tailColumn_ * (j + 1);
                float midWidth = width - elapsed * 2.0f * width;
                float nextMidWidth = nextWidth - elapsed * 2.0f * nextWidth;

                dest[0] = point.position_.x_;
                dest[1] = point.position_.y_;
                dest[2] = point.position_.z_;
                ((unsigned&)dest[3]) = c;
                dest[4] = factor;
                dest[5] = elapsed;
                dest[6] = point.forward_.x_;
                dest[7] = point.forward_.y_;
                dest[8] = point.forward_.z_;
                dest[9] = midWidth;

                dest[10] = point.next_->position_.x_;
                dest[11] = point.next_->position_.y_;
                dest[12] = point.next_->position_.z_;
                ((unsigned&)dest[13]) = nextC;
                dest[14] = nextFactor;
                dest[15] = elapsed;
                dest[16] = point.next_->forward_.x_;
                dest[17] = point.next_->forward_.y_;
                dest[18] = point.next_->forward_.z_;
                dest[19] = nextMidWidth;

                dest += 20;
            }

            // Last row
            dest[0] = point.position_.x_;
            dest[1] = point.position_.y_;
            dest[2] = point.position_.z_;
            ((unsigned&)dest[3]) = c;
            dest[4] = factor;
            dest[5] = 1.0f;
            dest[6] = point.forward_.x_;
            dest[7] = point.forward_.y_;
            dest[8] = point.forward_.z_;
            dest[9] = -width;

            dest[10] = point.next_->position_.x_;
            dest[11] = point.next_->position_.y_;
            dest[12] = point.next_->position_.z_;
            ((unsigned&)dest[13]) = nextC;
            dest[14] = nextFactor;
            dest[15] = 1.0f;
            dest[16] = point.next_->forward_.x_;
            dest[17] = point.next_->forward_.y_;
            dest[18] = point.next_->forward_.z_;
            dest[19] = -nextWidth;

            dest += 20;
        }
    }
    else if (trailType_ == TT_BONE)
    {
        for (unsigned i = 0; i < numPoints_; ++i)
        {
            TrailPoint& point = *sortedPoints_[i];

            if (sortedPoints_[i] == &points_.Back()) continue;

            // This point
            float factor = SmoothStep(0.0f, trailLength, point.elapsedLength_);
            unsigned c = endColor_.Lerp(startColor_, factor).ToUInt();

            float rightScale = Lerp(endScale_, startScale_, factor);
            float shift = (rightScale - 1.0f) / 2.0f;
            float leftScale = 0.0f - shift;

            // Next point
            float nextFactor = SmoothStep(0.0f, trailLength, point.next_->elapsedLength_);
            unsigned nextC = endColor_.Lerp(startColor_, nextFactor).ToUInt();

            float nextRightScale = Lerp(endScale_, startScale_, nextFactor);
            float nextShift = (nextRightScale - 1.0f) / 2.0f;
            float nextLeftScale = 0.0f - nextShift;

            // First row
            dest[0] = point.position_.x_;
            dest[1] = point.position_.y_;
            dest[2] = point.position_.z_;
            dest[3] = point.forward_.x_;
            dest[4] = point.forward_.y_;
            dest[5] = point.forward_.z_;
            ((unsigned&)dest[6]) = c;
            dest[7] = factor;
            dest[8] = 0.0f;
            dest[9] = point.parentPos_.x_;
            dest[10] = point.parentPos_.y_;
            dest[11] = point.parentPos_.z_;
            dest[12] = leftScale;

            dest[13] = point.next_->position_.x_;
            dest[14] = point.next_->position_.y_;
            dest[15] = point.next_->position_.z_;
            dest[16] = point.next_->forward_.x_;
            dest[17] = point.next_->forward_.y_;
            dest[18] = point.next_->forward_.z_;
            ((unsigned&)dest[19]) = nextC;
            dest[20] = nextFactor;
            dest[21] = 0.0f;
            dest[22] = point.next_->parentPos_.x_;
            dest[23] = point.next_->parentPos_.y_;
            dest[24] = point.next_->parentPos_.z_;
            dest[25] = nextLeftScale;

            dest += 26;

            // Middle row
            for (unsigned j = 0; j < (tailColumn_ - 1); ++j)
            {
                float elapsed = 1.0f / tailColumn_ * (j + 1);

                dest[0] = point.position_.x_;
                dest[1] = point.position_.y_;
                dest[2] = point.position_.z_;
                dest[3] = point.forward_.x_;
                dest[4] = point.forward_.y_;
                dest[5] = point.forward_.z_;
                ((unsigned&)dest[6]) = c;
                dest[7] = factor;
                dest[8] = elapsed;
                dest[9] = point.parentPos_.x_;
                dest[10] = point.parentPos_.y_;
                dest[11] = point.parentPos_.z_;
                dest[12] = Lerp(leftScale, rightScale, elapsed);

                dest[13] = point.next_->position_.x_;
                dest[14] = point.next_->position_.y_;
                dest[15] = point.next_->position_.z_;
                dest[16] = point.next_->forward_.x_;
                dest[17] = point.next_->forward_.y_;
                dest[18] = point.next_->forward_.z_;
                ((unsigned&)dest[19]) = nextC;
                dest[20] = nextFactor;
                dest[21] = elapsed;
                dest[22] = point.next_->parentPos_.x_;
                dest[23] = point.next_->parentPos_.y_;
                dest[24] = point.next_->parentPos_.z_;
                dest[25] = Lerp(nextLeftScale, nextRightScale, elapsed);

                dest += 26;
            }

            // Last row
            dest[0] = point.position_.x_;
            dest[1] = point.position_.y_;
            dest[2] = point.position_.z_;
            dest[3] = point.forward_.x_;
            dest[4] = point.forward_.y_;
            dest[5] = point.forward_.z_;
            ((unsigned&)dest[6]) = c;
            dest[7] = factor;
            dest[8] = 1.0f;
            dest[9] = point.parentPos_.x_;
            dest[10] = point.parentPos_.y_;
            dest[11] = point.parentPos_.z_;
            dest[12] = rightScale;

            dest[13] = point.next_->position_.x_;
            dest[14] = point.next_->position_.y_;
            dest[15] = point.next_->position_.z_;
            dest[16] = point.next_->forward_.x_;
            dest[17] = point.next_->forward_.y_;
            dest[18] = point.next_->forward_.z_;
            ((unsigned&)dest[19]) = nextC;
            dest[20] = nextFactor;
            dest[21] = 1.0f;
            dest[22] = point.next_->parentPos_.x_;
            dest[23] = point.next_->parentPos_.y_;
            dest[24] = point.next_->parentPos_.z_;
            dest[25] = nextRightScale;

            dest += 26;
        }
    }

    vertexBuffer_->Unlock();
    vertexBuffer_->ClearDataLost();
}

void RibbonTrail::SetLifetime(float time)
{
    lifetime_ = time;
    Commit();
}

void RibbonTrail::SetVertexDistance(float length)
{
    vertexDistance_ = length;
    Commit();
}

void RibbonTrail::SetEndColor(const Color& color)
{
    endColor_ = color;
    Commit();
}

void RibbonTrail::SetStartColor(const Color& color)
{
    startColor_ = color;
    Commit();
}

void RibbonTrail::SetSorted(bool enable)
{
    sorted_ = enable;
    Commit();
}

void RibbonTrail::SetTrailType(TrailType type)
{
    if (trailType_ == type)
        return;

    if (type == TT_BONE && (node_->GetParent() == nullptr || node_->GetParent() == node_->GetScene()))
    {
        URHO3D_LOGWARNING("No parent node found, revert back to Face Camera type");
        return;
    }

    trailType_ = type;
    Drawable::OnMarkedDirty(node_);
    bufferSizeDirty_ = true;
    MarkNetworkUpdate();
}

void RibbonTrail::SetBaseVelocity(const Vector3& baseVelocity)
{
    baseVelocity_ = baseVelocity;
}

void RibbonTrail::SetMaterialAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
    Commit();
}

void RibbonTrail::SetWidth(float width)
{
    width_ = width;
    Commit();
}

void RibbonTrail::SetAnimationLodBias(float bias)
{
    animationLodBias_ = Max(bias, 0.0f);
    MarkNetworkUpdate();
}

void RibbonTrail::SetUpdateInvisible(bool enable)
{
    updateInvisible_ = enable;
    MarkNetworkUpdate();
}

void RibbonTrail::Commit()
{
    MarkPositionsDirty();
    MarkNetworkUpdate();
}

void RibbonTrail::MarkPositionsDirty()
{
    Drawable::OnMarkedDirty(node_);
    bufferDirty_ = true;
}

Material* RibbonTrail::GetMaterial() const
{
    return batches_[0].material_;
}

ResourceRef RibbonTrail::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

}
