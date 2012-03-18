//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Context.h"
#include "DebugRenderer.h"
#include "Profiler.h"
#include "Octree.h"
#include "Scene.h"
#include "Sort.h"
#include "WorkQueue.h"

#include "DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

static const float DEFAULT_OCTREE_SIZE = 1000.0f;
static const int DEFAULT_OCTREE_LEVELS = 8;
static const int RAYCASTS_PER_WORK_ITEM = 4;

void RaycastDrawablesWork(const WorkItem* item, unsigned threadIndex)
{
    Octree* octree = reinterpret_cast<Octree*>(item->aux_);
    Drawable** start = reinterpret_cast<Drawable**>(item->start_);
    Drawable** end = reinterpret_cast<Drawable**>(item->end_);
    const RayOctreeQuery& query = *octree->rayQuery_;
    PODVector<RayQueryResult>& results = octree->rayQueryResults_[threadIndex];
    
    while (start != end)
    {
        Drawable* drawable = *start;
        drawable->ProcessRayQuery(query, results);
        ++start;
    }
}

void UpdateDrawablesWork(const WorkItem* item, unsigned threadIndex)
{
    const FrameInfo& frame = *(reinterpret_cast<FrameInfo*>(item->aux_));
    Drawable** start = reinterpret_cast<Drawable**>(item->start_);
    Drawable** end = reinterpret_cast<Drawable**>(item->end_);
    
    while (start != end)
    {
        Drawable* drawable = *start;
        drawable->Update(frame);
        drawable->updateQueued_ = false;
        ++start;
    }
}

inline bool CompareRayQueryResults(const RayQueryResult& lhs, const RayQueryResult& rhs)
{
    return lhs.distance_ < rhs.distance_;
}

Octant::Octant(const BoundingBox& box, unsigned level, Octant* parent, Octree* root) :
    worldBoundingBox_(box),
    level_(level),
    parent_(parent),
    root_(root),
    numDrawables_(0)
{
    center_ = worldBoundingBox_.Center();
    halfSize_ = worldBoundingBox_.Size() * 0.5f;
    cullingBox_ = BoundingBox(worldBoundingBox_.min_ - halfSize_, worldBoundingBox_.max_ + halfSize_);
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        children_[i] = 0;
}

Octant::~Octant()
{
    Release();
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
    
    children_[index] = new Octant(BoundingBox(newMin, newMax), level_ + 1, this, root_);
    return children_[index];
}

void Octant::DeleteChild(unsigned index)
{
    delete children_[index];
    children_[index] = 0;
}

void Octant::DeleteChild(Octant* octant)
{
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i] == octant)
        {
            delete octant;
            children_[i] = 0;
            return;
        }
    }
}

void Octant::InsertDrawable(Drawable* drawable, const Vector3& boxCenter, const Vector3& boxSize)
{
    // If size OK or outside, stop recursion & insert here
    if (CheckDrawableSize(boxSize) || cullingBox_.IsInside(drawable->GetWorldBoundingBox()) != INSIDE)
    {
        Octant* oldOctant = drawable->octant_;
        if (oldOctant != this)
        {
            // Add first, then remove, because drawable count going to zero deletes the octree branch in question
            AddDrawable(drawable);
            if (oldOctant)
                oldOctant->RemoveDrawable(drawable, false);
        }
        return;
    }
    
    unsigned x = boxCenter.x_ < center_.x_ ? 0 : 1;
    unsigned y = boxCenter.y_ < center_.y_ ? 0 : 2;
    unsigned z = boxCenter.z_ < center_.z_ ? 0 : 4;
    GetOrCreateChild(x + y + z)->InsertDrawable(drawable, boxCenter, boxSize);
}

bool Octant::CheckDrawableSize(const Vector3& boxSize) const
{
    // If max split level, size always OK
    if (level_ != root_->GetNumLevels())
        return boxSize.x_ >= halfSize_.x_ || boxSize.y_ >= halfSize_.y_ || boxSize.z_ >= halfSize_.z_;
    else
        return true;
}

void Octant::ResetRoot()
{
    root_ = 0;
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->ResetRoot();
    }
}

void Octant::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!debug->IsInside(worldBoundingBox_))
        return;
    
    debug->AddBoundingBox(worldBoundingBox_, Color(0.25f, 0.25f, 0.25f), depthTest);
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->DrawDebugGeometry(debug, depthTest);
    }
}

void Octant::GetDrawablesInternal(OctreeQuery& query, bool inside) const
{
    if (this != root_)
    {
        Intersection res = query.TestOctant(cullingBox_, inside);
        if (res == OUTSIDE)
            // Fully outside, so cull this octant, its children & drawables
            return;
        if (res == INSIDE)
            inside = true;
    }
    
    for (PODVector<Drawable*>::ConstIterator i = drawables_.Begin(); i != drawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        
        if (!(drawable->GetDrawableFlags() & query.drawableFlags_) || !drawable->IsVisible() ||
            !(drawable->GetViewMask() & query.viewMask_))
            continue;
        
        if (query.TestDrawable(drawable, inside) != OUTSIDE)
            query.result_.Push(drawable);
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->GetDrawablesInternal(query, inside);
    }
}

void Octant::GetDrawablesInternal(RayOctreeQuery& query) const
{
    if (!numDrawables_)
        return;
    
    float octantDist = query.ray_.HitDistance(cullingBox_);
    if (octantDist > query.maxDistance_)
        return;
    
    for (PODVector<Drawable*>::ConstIterator i = drawables_.Begin(); i != drawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        unsigned drawableFlags = drawable->GetDrawableFlags();
        
        if (!(drawable->GetDrawableFlags() & query.drawableFlags_) || !drawable->IsVisible() ||
            !(drawable->GetViewMask() & query.viewMask_))
            continue;
        
        drawable->ProcessRayQuery(query, query.result_);
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->GetDrawablesInternal(query);
    }
}

void Octant::GetDrawablesOnlyInternal(RayOctreeQuery& query, PODVector<Drawable*>& drawables) const
{
    if (!numDrawables_)
        return;
    
    float octantDist = query.ray_.HitDistance(cullingBox_);
    if (octantDist > query.maxDistance_)
        return;
    
    for (PODVector<Drawable*>::ConstIterator i = drawables_.Begin(); i != drawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        unsigned drawableFlags = drawable->GetDrawableFlags();
        
        if (!(drawable->GetDrawableFlags() & query.drawableFlags_) || !drawable->IsVisible() ||
            !(drawable->GetViewMask() & query.viewMask_))
            continue;
        
        drawables.Push(drawable);
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->GetDrawablesOnlyInternal(query, drawables);
    }
}

void Octant::Release()
{
    if (root_ && this != root_)
    {
        // Remove the drawables (if any) from this octant to the root octant
        for (PODVector<Drawable*>::Iterator i = drawables_.Begin(); i != drawables_.End(); ++i)
        {
            (*i)->SetOctant(root_);
            root_->drawables_.Push(*i);
            root_->QueueReinsertion(*i);
        }
        drawables_.Clear();
        numDrawables_ = 0;
    }
    else if (!root_)
    {
        // If the whole octree is being destroyed, just detach the drawables
        for (PODVector<Drawable*>::Iterator i = drawables_.Begin(); i != drawables_.End(); ++i)
            (*i)->SetOctant(0);
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        DeleteChild(i);
}

OBJECTTYPESTATIC(Octree);

Octree::Octree(Context* context) :
    Component(context),
    Octant(BoundingBox(-DEFAULT_OCTREE_SIZE, DEFAULT_OCTREE_SIZE), 0, 0, this),
    scene_(0),
    numLevels_(DEFAULT_OCTREE_LEVELS)
{
    // Resize threaded ray query intermediate result vector according to number of worker threads
    rayQueryResults_.Resize(GetSubsystem<WorkQueue>()->GetNumThreads() + 1);
}

Octree::~Octree()
{
    // Reset root pointer from all child octants now so that they do not move their drawables to root
    ResetRoot();
}

void Octree::RegisterObject(Context* context)
{
    context->RegisterFactory<Octree>();
    
    Vector3 defaultBoundsMin = Vector3::ONE * DEFAULT_OCTREE_SIZE;
    Vector3 defaultBoundsMax = -Vector3::ONE * DEFAULT_OCTREE_SIZE;
    
    ATTRIBUTE(Octree, VAR_VECTOR3, "Bounding Box Min", worldBoundingBox_.min_, defaultBoundsMin, AM_DEFAULT);
    ATTRIBUTE(Octree, VAR_VECTOR3, "Bounding Box Max", worldBoundingBox_.max_, defaultBoundsMax, AM_DEFAULT);
    ATTRIBUTE(Octree, VAR_INT, "Number of Levels", numLevels_, DEFAULT_OCTREE_LEVELS, AM_DEFAULT);
}

void Octree::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    // If any of the (size) attributes change, resize the octree
    Serializable::OnSetAttribute(attr, src);
    Resize(worldBoundingBox_, numLevels_);
}

void Octree::Resize(const BoundingBox& box, unsigned numLevels)
{
    PROFILE(ResizeOctree);
    
    numLevels = Max((int)numLevels, 1);
    
    // If drawables exist, they are temporarily moved to the root
    Release();
    
    Vector3 halfSize = box.Size() * 0.5f;
    
    worldBoundingBox_ = box;
    cullingBox_ = BoundingBox(worldBoundingBox_.min_ - halfSize, worldBoundingBox_.max_ + halfSize);
    numDrawables_ = drawables_.Size();
    numLevels_ = numLevels;
}

void Octree::Update(const FrameInfo& frame)
{
    UpdateDrawables(frame);
    ReinsertDrawables(frame);
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
    {
        CancelUpdate(drawable);
        CancelReinsertion(drawable);
        octant->RemoveDrawable(drawable);
    }
}

void Octree::GetDrawables(OctreeQuery& query) const
{
    query.result_.Clear();
    GetDrawablesInternal(query, false);
}

void Octree::Raycast(RayOctreeQuery& query) const
{
    PROFILE(Raycast);
    
    query.result_.Clear();
    
    WorkQueue* queue = GetSubsystem<WorkQueue>();
    
    // If no worker threads or no triangle-level testing, do not create work items
    if (!queue->GetNumThreads() || query.level_ < RAY_TRIANGLE)
        GetDrawablesInternal(query);
    else
    {
        // Threaded ray query: first get the drawables
        rayQuery_ = &query;
        rayGetDrawables_.Clear();
        GetDrawablesOnlyInternal(query, rayGetDrawables_);
        
        // Check that amount of drawables is large enough to justify threading
        if (rayGetDrawables_.Size() > RAYCASTS_PER_WORK_ITEM)
        {
            for (unsigned i = 0; i < rayQueryResults_.Size(); ++i)
                rayQueryResults_[i].Clear();
            
            WorkItem item;
            item.workFunction_ = RaycastDrawablesWork;
            item.aux_ = const_cast<Octree*>(this);
            
            PODVector<Drawable*>::Iterator start = rayGetDrawables_.Begin();
            while (start != rayGetDrawables_.End())
            {
                PODVector<Drawable*>::Iterator end = rayGetDrawables_.End();
                if (end - start > RAYCASTS_PER_WORK_ITEM)
                    end = start + RAYCASTS_PER_WORK_ITEM;
                
                item.start_ = &(*start);
                item.end_ = &(*end);
                queue->AddWorkItem(item);
                
                start = end;
            }
            
            // Merge per-thread results
            queue->Complete();
            for (unsigned i = 0; i < rayQueryResults_.Size(); ++i)
                query.result_.Insert(query.result_.End(), rayQueryResults_[i].Begin(), rayQueryResults_[i].End());
        }
        else
        {
            for (PODVector<Drawable*>::Iterator i = rayGetDrawables_.Begin(); i != rayGetDrawables_.End(); ++i)
                (*i)->ProcessRayQuery(query, query.result_);
        }
    }
    
    Sort(query.result_.Begin(), query.result_.End(), CompareRayQueryResults);
}

void Octree::RaycastSingle(RayOctreeQuery& query) const
{
    PROFILE(Raycast);
    
    query.result_.Clear();
    rayGetDrawables_.Clear();
    GetDrawablesOnlyInternal(query, rayGetDrawables_);
    
    // Sort by increasing hit distance to AABB
    for (PODVector<Drawable*>::Iterator i = rayGetDrawables_.Begin(); i != rayGetDrawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        drawable->SetSortValue(query.ray_.HitDistance(drawable->GetWorldBoundingBox()));
    }
    
    Sort(rayGetDrawables_.Begin(), rayGetDrawables_.End(), CompareDrawables);
    
    // Then do the actual test according to the query, and early-out as possible
    float closestHit = M_INFINITY;
    for (PODVector<Drawable*>::Iterator i = rayGetDrawables_.Begin(); i != rayGetDrawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        if (drawable->GetSortValue() <= Min(closestHit, query.maxDistance_))
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
    drawableUpdates_.Push(drawable);
    drawable->updateQueued_ = true;
}

void Octree::QueueReinsertion(Drawable* drawable)
{
    if (scene_ && scene_->IsThreadedUpdate())
    {
        MutexLock lock(octreeMutex_);
        drawableReinsertions_.Push(drawable);
    }
    else
        drawableReinsertions_.Push(drawable);
    drawable->reinsertionQueued_ = true;
}

void Octree::CancelUpdate(Drawable* drawable)
{
    PODVector<Drawable*>::Iterator i = drawableUpdates_.Find(drawable);
    if (i != drawableUpdates_.End())
    {
        (*i)->updateQueued_ = false;
        drawableUpdates_.Erase(i);
    }
}

void Octree::CancelReinsertion(Drawable* drawable)
{
    PODVector<Drawable*>::Iterator i = drawableReinsertions_.Find(drawable);
    if (i != drawableReinsertions_.End())
    {
        (*i)->reinsertionQueued_ = false;
        drawableReinsertions_.Erase(i);
    }
}

void Octree::DrawDebugGeometry(bool depthTest)
{
    PROFILE(OctreeDrawDebug);
    
    DebugRenderer* debug = GetComponent<DebugRenderer>();
    if (!debug)
        return;
    
    Octant::DrawDebugGeometry(debug, depthTest);
}

void Octree::OnNodeSet(Node* node)
{
    scene_ = node ? node->GetScene() : 0;
}

void Octree::UpdateDrawables(const FrameInfo& frame)
{
    // Let drawables update themselves before reinsertion
    if (drawableUpdates_.Empty())
        return;
    
    PROFILE(UpdateDrawables);
    
    Scene* scene = node_->GetScene();
    WorkQueue* queue = GetSubsystem<WorkQueue>();
    scene->BeginThreadedUpdate();
    
    WorkItem item;
    item.workFunction_ = UpdateDrawablesWork;
    item.aux_ = const_cast<FrameInfo*>(&frame);
    
    PODVector<Drawable*>::Iterator start = drawableUpdates_.Begin();
    while (start != drawableUpdates_.End())
    {
        PODVector<Drawable*>::Iterator end = drawableUpdates_.End();
        if (end - start > DRAWABLES_PER_WORK_ITEM)
            end = start + DRAWABLES_PER_WORK_ITEM;
        
        item.start_ = &(*start);
        item.end_ = &(*end);
        queue->AddWorkItem(item);
        
        start = end;
    }
    
    queue->Complete();
    scene->EndThreadedUpdate();
    drawableUpdates_.Clear();
}

void Octree::ReinsertDrawables(const FrameInfo& frame)
{
    if (drawableReinsertions_.Empty())
        return;
    
    PROFILE(ReinsertDrawables);
    
    // Reinsert drawables into the octree
    for (PODVector<Drawable*>::Iterator i = drawableReinsertions_.Begin(); i != drawableReinsertions_.End(); ++i)
    {
        Drawable* drawable = *i;
        const BoundingBox& box = drawable->GetWorldBoundingBox();
        Vector3 boxCenter = box.Center();
        Vector3 boxSize = box.Size();
        
        Octant* octant = drawable->GetOctant();
        if (octant)
        {
            if (octant == this)
            {
                // Handle root octant as special case: if outside the root, do not reinsert
                if (GetCullingBox().IsInside(box) == INSIDE && !CheckDrawableSize(boxSize))
                    InsertDrawable(drawable, boxCenter, boxSize);
            }
            else
            {
                // Otherwise reinsert if outside current octant or if size does not fit octant size
                if (octant->GetCullingBox().IsInside(box) != INSIDE || !octant->CheckDrawableSize(boxSize))
                    InsertDrawable(drawable, boxCenter, boxSize);
            }
        }
        else
            InsertDrawable(drawable, boxCenter, boxSize);
        
        drawable->reinsertionQueued_ = false;
    }
    
    drawableReinsertions_.Clear();
}
