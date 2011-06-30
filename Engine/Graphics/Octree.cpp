//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "OctreeQuery.h"
#include "Sort.h"

#include "DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

static const float DEFAULT_OCTREE_SIZE = 1000.0f;
static const int DEFAULT_OCTREE_LEVELS = 8;

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
    Vector3 halfSize = worldBoundingBox_.Size() * 0.5f;
    cullingBox_ = BoundingBox(worldBoundingBox_.min_ - halfSize, worldBoundingBox_.max_ + halfSize);
    
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

void Octant::InsertDrawable(Drawable* drawable)
{
    // If size OK or outside, stop recursion & insert here
    if (CheckDrawableSize(drawable) || cullingBox_.IsInside(drawable->GetWorldBoundingBox()) != INSIDE)
    {
        if (drawable->octant_ != this)
        {
            // Add first, then remove, because drawable count going to zero deletes the octree branch in question
            Octant* oldOctant = drawable->octant_;
            AddDrawable(drawable);
            if (oldOctant)
                oldOctant->RemoveDrawable(drawable, false);
        }
        return;
    }
    
    Vector3 octantCenter = worldBoundingBox_.Center();
    Vector3 drawableCenter = drawable->GetWorldBoundingBox().Center();
    unsigned x = drawableCenter.x_ < octantCenter.x_ ? 0 : 1;
    unsigned y = drawableCenter.y_ < octantCenter.y_ ? 0 : 2;
    unsigned z = drawableCenter.z_ < octantCenter.z_ ? 0 : 4;
    GetOrCreateChild(x + y + z)->InsertDrawable(drawable);
}

bool Octant::CheckDrawableSize(Drawable* drawable) const
{
    // If max split level, size always OK
    if (level_ == root_->GetNumLevels())
        return true;
    
    Vector3 octantHalfSize = worldBoundingBox_.Size() * 0.5;
    Vector3 drawableSize = drawable->GetWorldBoundingBox().Size();
    
    return drawableSize.x_ >= octantHalfSize.x_ || drawableSize.y_ >= octantHalfSize.y_ || drawableSize.z_ >=
        octantHalfSize.z_;
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
    debug->AddBoundingBox(worldBoundingBox_, Color(0.25f, 0.25f, 0.25f), depthTest);
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->DrawDebugGeometry(debug, depthTest);
    }
}

void Octant::GetDrawablesInternal(OctreeQuery& query, bool inside) const
{
    if (!numDrawables_)
        return;
    
    Intersection res = query.TestOctant(cullingBox_, inside);
    if (res == OUTSIDE && this != root_)
        // Fully outside, so cull this octant, its children & drawables
        return;
    if (res == INSIDE)
        inside = true;
    
    for (PODVector<Drawable*>::ConstIterator i = drawables_.Begin(); i != drawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        unsigned flags = drawable->GetDrawableFlags();
        
        if (!(flags & query.drawableFlags_) || !drawable->IsVisible())
            continue;
        if (query.occludersOnly_ && !drawable->IsOccluder())
            continue;
        if (query.shadowCastersOnly_ && !drawable->GetCastShadows())
            continue;
        
        if (query.TestDrawable(drawable->GetWorldBoundingBox(), inside) != OUTSIDE)
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
    
    float octantDist = cullingBox_.Distance(query.ray_);
    if (octantDist >= query.maxDistance_)
        return;
    
    for (PODVector<Drawable*>::ConstIterator i = drawables_.Begin(); i != drawables_.End(); ++i)
    {
        Drawable* drawable = *i;
        unsigned drawableFlags = drawable->GetDrawableFlags();
        
        if (!(drawableFlags & query.drawableFlags_) || !drawable->IsVisible())
            continue;
        if (query.occludersOnly_ && !drawable->IsOccluder())
            continue;
        if (query.shadowCastersOnly_ && !drawable->GetCastShadows())
            continue;
        
        float drawableDist = drawable->GetWorldBoundingBox().Distance(query.ray_);
        // The drawable will possibly do more accurate collision testing, then store the result(s)
        if (drawableDist < query.maxDistance_)
            drawable->ProcessRayQuery(query, drawableDist);
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (children_[i])
            children_[i]->GetDrawablesInternal(query);
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
    numLevels_(DEFAULT_OCTREE_LEVELS)
{
}

Octree::~Octree()
{
    // Reset root pointer from all child octants now so that they do not move their drawables to root
    ResetRoot();
}

void Octree::RegisterObject(Context* context)
{
    context->RegisterFactory<Octree>();
    
    ATTRIBUTE(Octree, VAR_VECTOR3, "Bounding Box Min", worldBoundingBox_.min_, Vector3(-DEFAULT_OCTREE_SIZE, -DEFAULT_OCTREE_SIZE, -DEFAULT_OCTREE_SIZE));
    ATTRIBUTE(Octree, VAR_VECTOR3, "Bounding Box Max", worldBoundingBox_.max_, Vector3(DEFAULT_OCTREE_SIZE, DEFAULT_OCTREE_SIZE, DEFAULT_OCTREE_SIZE));
    ATTRIBUTE(Octree, VAR_INT, "Number of Levels", numLevels_, DEFAULT_OCTREE_LEVELS);
}

void Octree::OnSetAttribute(const AttributeInfo& attr, const Variant& value)
{
    Serializable::OnSetAttribute(attr, value);
    
    // If any of the size attributes changes, resize the octree
    /// \todo This may lead to unnecessary resizing, however it is fast once child nodes have been removed
    switch (attr.offset_)
    {
    case offsetof(Octree, worldBoundingBox_.min_):
    case offsetof(Octree, worldBoundingBox_.max_):
    case offsetof(Octree, numLevels_):
        Resize(worldBoundingBox_, numLevels_);
        break;
    }
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
    {
        PROFILE(UpdateDrawables);
        
        // Let drawables update themselves before reinsertion
        for (HashSet<Drawable*>::Iterator i = drawableUpdates_.Begin(); i != drawableUpdates_.End(); ++i)
            (*i)->Update(frame);
    }
    
    {
        PROFILE(ReinsertDrawables);
        
        // Reinsert drawables into the octree
        for (HashSet<Drawable*>::Iterator i = drawableReinsertions_.Begin(); i != drawableReinsertions_.End(); ++i)
        {
            Drawable* drawable = *i;
            Octant* octant = drawable->GetOctant();
            
            if (octant)
            {
                bool reinsert = false;
                
                if (octant == this)
                {
                    // Handle root octant as special case: if outside the root, do not reinsert
                    if (GetCullingBox().IsInside(drawable->GetWorldBoundingBox()) == INSIDE && !CheckDrawableSize(drawable))
                        reinsert = true;
                }
                else
                {
                    // Otherwise reinsert if outside current octant or if size does not fit octant size
                    if (octant->GetCullingBox().IsInside(drawable->GetWorldBoundingBox()) != INSIDE ||
                        !octant->CheckDrawableSize(drawable))
                        reinsert = true;
                }
                
                if (reinsert)
                    InsertDrawable(drawable);
            }
            else
                InsertDrawable(drawable);
        }
    }
    
    drawableUpdates_.Clear();
    drawableReinsertions_.Clear();
}

void Octree::GetDrawables(OctreeQuery& query) const
{
    PROFILE(OctreeQuery);
    
    query.result_.Clear();
    GetDrawablesInternal(query, false);
}

void Octree::GetDrawables(RayOctreeQuery& query) const
{
    PROFILE(Raycast);
    
    query.result_.Clear();
    GetDrawablesInternal(query);
    Sort(query.result_.Begin(), query.result_.End(), CompareRayQueryResults);
}

void Octree::QueueUpdate(Drawable* drawable)
{
    drawableUpdates_.Insert(drawable);
}

void Octree::QueueReinsertion(Drawable* drawable)
{
    drawableReinsertions_.Insert(drawable);
}

void Octree::CancelUpdate(Drawable* drawable)
{
    drawableUpdates_.Erase(drawable);
}

void Octree::CancelReinsertion(Drawable* drawable)
{
    drawableReinsertions_.Erase(drawable);
}

void Octree::DrawDebugGeometry(bool depthTest)
{
    PROFILE(OctreeDrawDebug);
    
    DebugRenderer* debug = GetComponent<DebugRenderer>();
    if (!debug)
        return;
    
    Octant::DrawDebugGeometry(debug, depthTest);
}
