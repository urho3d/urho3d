//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include "../Core/CoreEvents.h"
#include "../Core/Profiler.h"
#include "../Core/Thread.h"
#include "../Core/WorkQueue.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Octree.h"
#include "../IO/Log.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include "../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

namespace Urho3D
{

static const float DEFAULT_OCTREE_SIZE = 1000.0f;
static const int DEFAULT_OCTREE_LEVELS = 8;

extern const char* SUBSYSTEM_CATEGORY;

void UpdateDrawablesWork(const WorkItem* item, unsigned threadIndex)
{
    const FrameInfo& frame = *(reinterpret_cast<FrameInfo*>(item->aux_));
    Drawable** start = reinterpret_cast<Drawable**>(item->start_);
    Drawable** end = reinterpret_cast<Drawable**>(item->end_);

    while (start != end)
    {
        Drawable* drawable = *start;
        if (drawable)
            drawable->Update(frame);
        ++start;
    }
}

inline bool CompareRayQueryResults(const RayQueryResult& lhs, const RayQueryResult& rhs)
{
    return lhs.distance_ < rhs.distance_;
}

Octant::Octant(const BoundingBox& box, unsigned level, Octant* parent, Octree* root, unsigned index) :
    level_(level),
    numDrawables_(0),
    parent_(parent),
    root_(root),
    index_(index)
{
    Initialize(box);

    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        children_[i] = 0;
}

Octant::~Octant()
{
    if (root_)
    {
        // Remove the drawables (if any) from this octant to the root octant
        for (PODVector<Drawable*>::Iterator i = drawables_.Begin(); i != drawables_.End(); ++i)
        {
            (*i)->SetOctant(root_);
            root_->drawables_.Push(*i);
            root_->QueueUpdate(*i);
        }
        drawables_.Clear();
        numDrawables_ = 0;
    }

    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        DeleteChild(i);
}

Octant* Octant::GetOrCreateChild(unsigned index)
{
    if (children_[index])
        return children_[index];

    Vector3 newMin = worldBoundingBox_.min_;
    Vector3 newMax = worldBoundingBox_.max_;
    Vector3 oldCenter = worldBoundingBox_.Center();

    if (index & 1)
        newMin.x_ = oldCenter.x_;
    else
        newMax.x_ = oldCenter.x_;

    if (index & 2)
        newMin.y_ = oldCenter.y_;
    else
        newMax.y_ = oldCenter.y_;

    if (index & 4)
        newMin.z_ = oldCenter.z_;
    else
        newMax.z_ = oldCenter.z_;

    children_[index] = new Octant(BoundingBox(newMin, newMax), level_ + 1, this, root_, index);
    return children_[index];
}

void Octant::DeleteChild(unsigned index)
{
    assert(index < NUM_OCTANTS);
    delete children_[index];
    children_[index] = 0;
}

void Octant::InsertDrawable(Drawable* drawable)
{
    const BoundingBox& box = drawable->GetWorldBoundingBox();

    // If root octant, insert all non-occludees here, so that octant occlusion does not hide the drawable.
    // Also if drawable is outside the root octant bounds, insert to root
    bool insertHere;
    if (this == root_)
        insertHere = !drawable->IsOccludee() || cullingBox_.IsInside(box) != INSIDE || CheckDrawableFit(box);
    else
        insertHere = CheckDrawableFit(box);

    if (insertHere)
    {
        Octant* oldOctant = drawable->octant_;
        if (oldOctant != this)
        {
            // Add first, then remove, because drawable count going to zero deletes the octree branch in question
            AddDrawable(drawable);
            if (oldOctant)
                oldOctant->RemoveDrawable(drawable, false);
        }
    }
    else
    {
        Vector3 boxCenter = box.Center();
        unsigned x = boxCenter.x_ < center_.x_ ? 0 : 1;
        unsigned y = boxCenter.y_ < center_.y_ ? 0 : 2;
        unsigned z = boxCenter.z_ < center_.z_ ? 0 : 4;

        GetOrCreateChild(x + y + z)->InsertDrawable(drawable);
    }
}

bool Octant::CheckDrawableFit(const BoundingBox& box) const
{
    Vector3 boxSize = box.Size();

    // If max split level, size always OK, otherwise check that box is at least half size of octant
    if (level_ >= root_->GetNumLevels() || boxSize.x_ >= halfSize_.x_ || boxSize.y_ >= halfSize_.y_ ||
        boxSize.z_ >= halfSize_.z_)
        return true;
    // Also check if the box can not fit a child octant's culling box, in that case size OK (must insert here)
    else
    {
        if (box.min_.x_ <= worldBoundingBox_.min_.x_ - 0.5f * halfSize_.x_ ||
            box.max_.x_ >= worldBoundingBox_.max_.x_ + 0.5f * halfSize_.x_ ||
            box.min_.y_ <= worldBoundingBox_.min_.y_ - 0.5f * halfSize_.y_ ||
            box.max_.y_ >= worldBoundingBox_.max_.y_ + 0.5f * halfSize_.y_ ||
            box.min_.z_ <= worldBoundingBox_.min_.z_ - 0.5f * halfSize_.z_ ||
            box.max_.z_ >= worldBoundingBox_.max_.z_ + 0.5f * halfSize_.z_)
            return true;
    }

    // Bounding box too small, should create a child octant
    return false;
}

void Octant::ResetRoot()
{
    root_ = 0;

    // The whole octree is being destroyed, just detach the drawables
    for (PODVector<Drawable*>::Iterator i = drawables_.Begin(); i != drawables_.End(); ++i)
        (*i)->SetOctant(0);

    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->ResetRoot();
    }
}

void Octant::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && debug->IsInside(worldBoundingBox_))
    {
        debug->AddBoundingBox(worldBoundingBox_, Color(0.25f, 0.25f, 0.25f), depthTest);

        for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        {
            if (children_[i])
                children_[i]->DrawDebugGeometry(debug, depthTest);
        }
    }
}

void Octant::Initialize(const BoundingBox& box)
{
    worldBoundingBox_ = box;
    center_ = box.Center();
    halfSize_ = 0.5f * box.Size();
    cullingBox_ = BoundingBox(worldBoundingBox_.min_ - halfSize_, worldBoundingBox_.max_ + halfSize_);
}

void Octant::GetDrawablesInternal(OctreeQuery& query, bool inside) const
{
    if (this != root_)
    {
        Intersection res = query.TestOctant(cullingBox_, inside);
        if (res == INSIDE)
            inside = true;
        else if (res == OUTSIDE)
        {
            // Fully outside, so cull this octant, its children & drawables
            return;
        }
    }

    if (drawables_.Size())
    {
        Drawable** start = const_cast<Drawable**>(&drawables_[0]);
        Drawable** end = start + drawables_.Size();
        query.TestDrawables(start, end, inside);
    }

    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->GetDrawablesInternal(query, inside);
    }
}

void Octant::GetDrawablesInternal(RayOctreeQuery& query) const
{
    float octantDist = query.ray_.HitDistance(cullingBox_);
    if (octantDist >= query.maxDistance_)
        return;

    if (drawables_.Size())
    {
        Drawable** start = const_cast<Drawable**>(&drawables_[0]);
        Drawable** end = start + drawables_.Size();

        while (start != end)
        {
            Drawable* drawable = *start++;

            if ((drawable->GetDrawableFlags() & query.drawableFlags_) && (drawable->GetViewMask() & query.viewMask_))
                drawable->ProcessRayQuery(query, query.result_);
        }
    }

    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->GetDrawablesInternal(query);
    }
}

void Octant::GetDrawablesOnlyInternal(RayOctreeQuery& query, PODVector<Drawable*>& drawables) const
{
    float octantDist = query.ray_.HitDistance(cullingBox_);
    if (octantDist >= query.maxDistance_)
        return;

    if (drawables_.Size())
    {
        Drawable** start = const_cast<Drawable**>(&drawables_[0]);
        Drawable** end = start + drawables_.Size();

        while (start != end)
        {
            Drawable* drawable = *start++;

            if ((drawable->GetDrawableFlags() & query.drawableFlags_) && (drawable->GetViewMask() & query.viewMask_))
                drawables.Push(drawable);
        }
    }

    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->GetDrawablesOnlyInternal(query, drawables);
    }
}

Octree::Octree(Context* context) :
    Component(context),
    Octant(BoundingBox(-DEFAULT_OCTREE_SIZE, DEFAULT_OCTREE_SIZE), 0, 0, this),
    numLevels_(DEFAULT_OCTREE_LEVELS)
{
    // If the engine is running headless, subscribe to RenderUpdate events for manually updating the octree
    // to allow raycasts and animation update
    if (!GetSubsystem<Graphics>())
        SubscribeToEvent(E_RENDERUPDATE, URHO3D_HANDLER(Octree, HandleRenderUpdate));
}

Octree::~Octree()
{
    // Reset root pointer from all child octants now so that they do not move their drawables to root
    drawableUpdates_.Clear();
    ResetRoot();
}

void Octree::RegisterObject(Context* context)
{
    context->RegisterFactory<Octree>(SUBSYSTEM_CATEGORY);

    Vector3 defaultBoundsMin = -Vector3::ONE * DEFAULT_OCTREE_SIZE;
    Vector3 defaultBoundsMax = Vector3::ONE * DEFAULT_OCTREE_SIZE;

    URHO3D_ATTRIBUTE("Bounding Box Min", Vector3, worldBoundingBox_.min_, defaultBoundsMin, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Bounding Box Max", Vector3, worldBoundingBox_.max_, defaultBoundsMax, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Number of Levels", int, numLevels_, DEFAULT_OCTREE_LEVELS, AM_DEFAULT);
}

void Octree::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    // If any of the (size) attributes change, resize the octree
    Serializable::OnSetAttribute(attr, src);
    SetSize(worldBoundingBox_, numLevels_);
}

void Octree::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug)
    {
        URHO3D_PROFILE(OctreeDrawDebug);

        Octant::DrawDebugGeometry(debug, depthTest);
    }
}

void Octree::SetSize(const BoundingBox& box, unsigned numLevels)
{
    URHO3D_PROFILE(ResizeOctree);

    // If drawables exist, they are temporarily moved to the root
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        DeleteChild(i);

    Initialize(box);
    numDrawables_ = drawables_.Size();
    numLevels_ = Max(numLevels, 1U);
}

void Octree::Update(const FrameInfo& frame)
{
    if (!Thread::IsMainThread())
    {
        URHO3D_LOGERROR("Octree::Update() can not be called from worker threads");
        return;
    }

    // Let drawables update themselves before reinsertion. This can be used for animation
    if (!drawableUpdates_.Empty())
    {
        URHO3D_PROFILE(UpdateDrawables);

        // Perform updates in worker threads. Notify the scene that a threaded update is going on and components
        // (for example physics objects) should not perform non-threadsafe work when marked dirty
        Scene* scene = GetScene();
        WorkQueue* queue = GetSubsystem<WorkQueue>();
        scene->BeginThreadedUpdate();

        int numWorkItems = queue->GetNumThreads() + 1; // Worker threads + main thread
        int drawablesPerItem = Max((int)(drawableUpdates_.Size() / numWorkItems), 1);

        PODVector<Drawable*>::Iterator start = drawableUpdates_.Begin();
        // Create a work item for each thread
        for (int i = 0; i < numWorkItems; ++i)
        {
            SharedPtr<WorkItem> item = queue->GetFreeItem();
            item->priority_ = M_MAX_UNSIGNED;
            item->workFunction_ = UpdateDrawablesWork;
            item->aux_ = const_cast<FrameInfo*>(&frame);

            PODVector<Drawable*>::Iterator end = drawableUpdates_.End();
            if (i < numWorkItems - 1 && end - start > drawablesPerItem)
                end = start + drawablesPerItem;

            item->start_ = &(*start);
            item->end_ = &(*end);
            queue->AddWorkItem(item);

            start = end;
        }

        queue->Complete(M_MAX_UNSIGNED);
        scene->EndThreadedUpdate();
    }

    // If any drawables were inserted during threaded update, update them now from the main thread
    if (!threadedDrawableUpdates_.Empty())
    {
        URHO3D_PROFILE(UpdateDrawablesQueuedDuringUpdate);

        for (PODVector<Drawable*>::ConstIterator i = threadedDrawableUpdates_.Begin(); i != threadedDrawableUpdates_.End(); ++i)
        {
            Drawable* drawable = *i;
            if (drawable)
            {
                drawable->Update(frame);
                drawableUpdates_.Push(drawable);
            }
        }

        threadedDrawableUpdates_.Clear();
    }

    // Notify drawable update being finished. Custom animation (eg. IK) can be done at this point
    Scene* scene = GetScene();
    if (scene)
    {
        using namespace SceneDrawableUpdateFinished;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_SCENE] = scene;
        eventData[P_TIMESTEP] = frame.timeStep_;
        scene->SendEvent(E_SCENEDRAWABLEUPDATEFINISHED, eventData);
    }

    // Reinsert drawables that have been moved or resized, or that have been newly added to the octree and do not sit inside
    // the proper octant yet
    if (!drawableUpdates_.Empty())
    {
        URHO3D_PROFILE(ReinsertToOctree);

        for (PODVector<Drawable*>::Iterator i = drawableUpdates_.Begin(); i != drawableUpdates_.End(); ++i)
        {
            Drawable* drawable = *i;
            drawable->updateQueued_ = false;
            Octant* octant = drawable->GetOctant();
            const BoundingBox& box = drawable->GetWorldBoundingBox();

            // Skip if no octant or does not belong to this octree anymore
            if (!octant || octant->GetRoot() != this)
                continue;
            // Skip if still fits the current octant
            if (drawable->IsOccludee() && octant->GetCullingBox().IsInside(box) == INSIDE && octant->CheckDrawableFit(box))
                continue;

            InsertDrawable(drawable);

#ifdef _DEBUG
            // Verify that the drawable will be culled correctly
            octant = drawable->GetOctant();
            if (octant != this && octant->GetCullingBox().IsInside(box) != INSIDE)
            {
                URHO3D_LOGERROR("Drawable is not fully inside its octant's culling bounds: drawable box " + box.ToString() +
                         " octant box " + octant->GetCullingBox().ToString());
            }
#endif
        }
    }

    drawableUpdates_.Clear();
}

void Octree::AddManualDrawable(Drawable* drawable)
{
    if (!drawable || drawable->GetOctant())
        return;

    AddDrawable(drawable);
}

void Octree::RemoveManualDrawable(Drawable* drawable)
{
    if (!drawable)
        return;

    Octant* octant = drawable->GetOctant();
    if (octant && octant->GetRoot() == this)
        octant->RemoveDrawable(drawable);
}

void Octree::GetDrawables(OctreeQuery& query) const
{
    query.result_.Clear();
    GetDrawablesInternal(query, false);
}

void Octree::Raycast(RayOctreeQuery& query) const
{
    URHO3D_PROFILE(Raycast);

    query.result_.Clear();
    GetDrawablesInternal(query);
    Sort(query.result_.Begin(), query.result_.End(), CompareRayQueryResults);
}

void Octree::RaycastSingle(RayOctreeQuery& query) const
{
    URHO3D_PROFILE(Raycast);

    query.result_.Clear();
    rayQueryDrawables_.Clear();
    GetDrawablesOnlyInternal(query, rayQueryDrawables_);

    // Sort by increasing hit distance to AABB
    for (PODVector<Drawable*>::Iterator i = rayQueryDrawables_.Begin(); i != rayQueryDrawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        drawable->SetSortValue(query.ray_.HitDistance(drawable->GetWorldBoundingBox()));
    }

    Sort(rayQueryDrawables_.Begin(), rayQueryDrawables_.End(), CompareDrawables);

    // Then do the actual test according to the query, and early-out as possible
    float closestHit = M_INFINITY;
    for (PODVector<Drawable*>::Iterator i = rayQueryDrawables_.Begin(); i != rayQueryDrawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        if (drawable->GetSortValue() < Min(closestHit, query.maxDistance_))
        {
            unsigned oldSize = query.result_.Size();
            drawable->ProcessRayQuery(query, query.result_);
            if (query.result_.Size() > oldSize)
                closestHit = Min(closestHit, query.result_.Back().distance_);
        }
        else
            break;
    }

    if (query.result_.Size() > 1)
    {
        Sort(query.result_.Begin(), query.result_.End(), CompareRayQueryResults);
        query.result_.Resize(1);
    }
}

void Octree::QueueUpdate(Drawable* drawable)
{
    Scene* scene = GetScene();
    if (scene && scene->IsThreadedUpdate())
    {
        MutexLock lock(octreeMutex_);
        threadedDrawableUpdates_.Push(drawable);
    }
    else
        drawableUpdates_.Push(drawable);

    drawable->updateQueued_ = true;
}

void Octree::CancelUpdate(Drawable* drawable)
{
    // This doesn't have to take into account scene being in threaded update, because it is called only
    // when removing a drawable from octree, which should only ever happen from the main thread.
    drawableUpdates_.Remove(drawable);
    drawable->updateQueued_ = false;
}

void Octree::DrawDebugGeometry(bool depthTest)
{
    DebugRenderer* debug = GetComponent<DebugRenderer>();
    DrawDebugGeometry(debug, depthTest);
}

void Octree::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // When running in headless mode, update the Octree manually during the RenderUpdate event
    Scene* scene = GetScene();
    if (!scene || !scene->IsUpdateEnabled())
        return;

    using namespace RenderUpdate;

    FrameInfo frame;
    frame.frameNumber_ = GetSubsystem<Time>()->GetFrameNumber();
    frame.timeStep_ = eventData[P_TIMESTEP].GetFloat();
    frame.camera_ = 0;

    Update(frame);
}

}
