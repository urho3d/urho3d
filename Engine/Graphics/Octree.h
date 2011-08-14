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

#pragma once

#include "Drawable.h"
#include "HashSet.h"

class Drawable;
class Octree;
class OctreeQuery;
class RayOctreeQuery;

static const int NUM_OCTANTS = 8;

/// %Octree octant
class Octant
{
public:
    /// Construct.
    Octant(const BoundingBox& box, unsigned level, Octant* parent, Octree* root);
    /// Destruct. Move drawables to root if available (detach if not) and free child octants.
    virtual ~Octant();
    
    /// Return or create a child octant.
    Octant* GetOrCreateChild(unsigned index);
    /// Delete child octant.
    void DeleteChild(unsigned index);
    /// Delete child octant by pointer.
    void DeleteChild(Octant* octant);
    /// Insert a drawable object by checking for fit recursively.
    void InsertDrawable(Drawable* drawable);
    /// Check if a drawable object fits.
    bool CheckDrawableSize(Drawable* drawable) const;
    
    /// Add a drawable object to this octant.
    void AddDrawable(Drawable* drawable)
    {
        drawable->SetOctant(this);
        drawables_.Push(drawable);
        IncDrawableCount();
    }
    
    /// Remove a drawable object from this octant.
    void RemoveDrawable(Drawable* drawable, bool resetOctant = true)
    {
        PODVector<Drawable*>::Iterator i = drawables_.Find(drawable);
        if (i != drawables_.End())
        {
            if (resetOctant)
                drawable->SetOctant(0);
            drawables_.Erase(i);
            DecDrawableCount();
        }
    }
    
    /// Return world bounding box.
    const BoundingBox& GetWorldBoundingBox() const { return worldBoundingBox_; }
    /// Return bounding box used for fitting drawable objects.
    const BoundingBox& GetCullingBox() const { return cullingBox_; }
    /// Return subdivision level.
    unsigned GetLevel() const { return level_; }
    /// Return parent octant.
    Octant* GetParent() const { return parent_; }
    /// Return octree root.
    Octree* GetRoot() const { return root_; }
    /// Return true if there are no drawable objects in this octant and child octants.
    bool IsEmpty() { return numDrawables_ == 0; }
    
    /// Reset root pointer recursively. Called when the whole octree is being destroyed.
    void ResetRoot();
    /// Draw bounds to the debug graphics recursively.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
protected:
    /// Return drawable objects by a query, called internally.
    void GetDrawablesInternal(OctreeQuery& query, bool inside) const;
    /// Return drawable objects by a ray query, called internally.
    void GetDrawablesInternal(RayOctreeQuery& query) const;
    /// Free child octants. If drawable objects still exist, move them to root.
    void Release();
    
    /// Increase drawable object count recursively.
    void IncDrawableCount()
    {
        ++numDrawables_;
        if (parent_)
            parent_->IncDrawableCount();
    }
    
    /// Decrease drawable object count recursively and remove octant if it becomes empty.
    void DecDrawableCount()
    {
        Octant* parent = parent_;
        
        --numDrawables_;
        if (!numDrawables_)
        {
            if (parent)
                parent->DeleteChild(this);
        }
        
        if (parent)
            parent->DecDrawableCount();
    }
    
    /// World bounding box.
    BoundingBox worldBoundingBox_;
    /// Bounding box used for drawable object fitting.
    BoundingBox cullingBox_;
    /// Subdivision level.
    unsigned level_;
    /// Parent octant.
    Octant* parent_;
    /// Child octants.
    Octant* children_[NUM_OCTANTS];
    /// Octree root.
    Octree* root_;
    /// Drawable objects.
    PODVector<Drawable*> drawables_;
    /// Number of drawable objects in this octant and child octants.
    unsigned numDrawables_;
};

/// %Octree component. Should be added only to the root scene node
class Octree : public Component, public Octant
{
    OBJECT(Octree);
    
public:
    /// Construct.
    Octree(Context* context);
    /// Destruct.
    ~Octree();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Handle attribute change.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    
    /// Resize octree. If octree is not empty, drawable objects will be temporarily moved to the root.
    void Resize(const BoundingBox& box, unsigned numLevels);
    /// Update and reinsert drawable objects.
    void Update(const FrameInfo& frame);
    
    /// Return drawable objects by a query.
    void GetDrawables(OctreeQuery& query) const;
    /// Return drawable objects by a ray query.
    void GetDrawables(RayOctreeQuery& query) const;
    /// Return subdivision levels.
    unsigned GetNumLevels() const { return numLevels_; }
    
    /// Mark drawable object as requiring an update.
    void QueueUpdate(Drawable* drawable);
    /// Mark drawable object as requiring a reinsertion.
    void QueueReinsertion(Drawable* drawable);
    /// Remove drawable object from update list.
    void CancelUpdate(Drawable* drawable);
    /// Remove drawable object from reinsertion list.
    void CancelReinsertion(Drawable* drawable);
    /// Add debug geometry to the debug graphics.
    void DrawDebugGeometry(bool depthTest);
    
private:
    /// %Set of drawable objects that require update.
    HashSet<Drawable*> drawableUpdates_;
    /// %Set of drawable objects that require reinsertion.
    HashSet<Drawable*> drawableReinsertions_;
    /// Subdivision level.
    unsigned numLevels_;
};
