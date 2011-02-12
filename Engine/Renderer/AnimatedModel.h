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

#ifndef RENDERER_ANIMATEDMODEL_H
#define RENDERER_ANIMATEDMODEL_H

#include "Model.h"
#include "Skeleton.h"
#include "StaticModel.h"

#include <set>

class Animation;
class AnimationState;

//! Animated model scene node
class AnimatedModel : public StaticModel
{
    DEFINE_TYPE(AnimatedModel);
    
    friend class AnimationState;
    
public:
    //! Construct with initial octant pointer and name
    AnimatedModel(Octant* octant = 0, const std::string& name = std::string());
    //! Destruct. Free the animation states
    virtual ~AnimatedModel();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Perform client-side visual smoothing
    virtual void interpolate(bool snapToEnd);
    //! Return resource references
    virtual void getResourceRefs(std::vector<Resource*>& dest);
    
    //! Process renderer raycast
    virtual void processRayQuery(RayOctreeQuery& query, float initialDistance);
    //! Update before octree reinsertion. Animation is updated here
    virtual void updateNode(const FrameInfo& frame);
    //! Calculate distance for rendering
    virtual void updateDistance(const FrameInfo& frame);
    //! Prepare geometry for rendering
    virtual void updateGeometry(const FrameInfo& frame, Renderer* renderer);
    //! Return geometry type, determines vertex shader variation
    virtual GeometryType getGeometryType() { return GEOM_SKINNED; }
    //! Return vertex shader parameter
    virtual bool getVertexShaderParameter(unsigned batchIndex, VSParameter parameter, const float** data, unsigned* count);
    //! Draw debug geometry
    virtual void drawDebugGeometry(DebugRenderer* debug);
    
    //! Set model
    void setModel(Model* model);
    //! Add an animation
    AnimationState* addAnimationState(Animation* animation);
    //! Remove an animation by animation pointer
    void removeAnimationState(Animation* animation);
    //! Remove an animation by animation name
    void removeAnimationState(const std::string& animationName);
    //! Remove an animation by animation name hash
    void removeAnimationState(StringHash animationNameHash);
    //! Remove an animation by AnimationState pointer
    void removeAnimationState(AnimationState* state);
    //! Remove all animations
    void removeAllAnimationStates();
    //! Set animation LOD bias
    void setAnimationLodBias(float bias);
    //! Set animation LOD distance factor when not visible (default 0 = do not update at all when invisible)
    void setInvisibleLodFactor(float factor);
    //! Set animation & morphs local mode. If enabled, and client prediction is active, they will not be sent over network
    void setLocalAnimation(bool enable);
    //! Set vertex morph weight by index
    void setMorphWeight(unsigned index, float weight);
    //! Set vertex morph weight by name
    void setMorphWeight(const std::string& name, float weight);
    //! Set vertex morph weight by name hash
    void setMorphWeight(StringHash nameHash, float weight);
    //! Reset all vertex morphs to zero
    void resetMorphWeights();
    //! Sync animation from another animated model
    void syncAnimation(AnimatedModel* srcNode);
    //! Sync morphs from another animated model
    void syncMorphs(AnimatedModel* srcNode);
    
    //! Return skeleton
    const Skeleton& getSkeleton() const { return mSkeleton; }
    //! Return all animation states
    const std::vector<AnimationState*>& getAnimationStates() const { return mAnimationStates; }
    //! Return number of animation states
    unsigned getNumAnimationStates() const { return mAnimationStates.size(); }
    //! Return animation state by animation pointer
    AnimationState* getAnimationState(Animation* animation) const;
    //! Return animation state by animation name
    AnimationState* getAnimationState(const std::string& animationName) const;
    //! Return animation state by animation name hash
    AnimationState* getAnimationState(const StringHash animationNameHash) const;
    //! Return animation state by index
    AnimationState* getAnimationState(unsigned index) const;
    //! Return animation LOD bias
    float getAnimationLodBias() const { return mAnimationLodBias; }
    //! Return animation LOD distance factor when not visible
    float getInvisibleLodFactor() const { return mInvisibleLodFactor; }
    //! Return whether animation is local when client prediction is on
    bool getLocalAnimation() const { return mLocalAnimation; }
    //! Return all vertex morphs
    const std::vector<ModelMorph>& getMorphs() const { return mMorphs; }
    //! Return all morph vertex buffers
    const std::vector<SharedPtr<VertexBuffer> >& getMorphVertexBuffers() const { return mMorphVertexBuffers; }
    //! Return number of vertex morphs
    unsigned getNumMorphs() const { return mMorphs.size(); }
    //! Return vertex morph weight by index
    float getMorphWeight(unsigned index) const;
    //! Return vertex morph weight by name
    float getMorphWeight(const std::string& name) const;
    //! Return vertex morph weight by name hash
    float getMorphWeight(StringHash nameHash) const;
    
protected:
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
    
private:
    //! Mark animation and skinning to require an update
    void markAnimationDirty();
    //! Mark animation and skinning to require a forced update (blending order changed)
    void markAnimationOrderDirty();
    //! Mark morphs to require an update
    void markMorphsDirty();
    //! Set skeleton
    void setSkeleton(const Skeleton& skeleton);
    //! Refresh mapping of subgeometry bone indices
    void refreshGeometryBoneMappings();
    //! Clone geometries as required
    void cloneGeometries();
    //! Recalculate animations. Called from updateNode()
    void updateAnimation(const FrameInfo& frame);
    //! Recalculate skinning
    void updateSkinning();
    //! Reapply all vertex morphs
    void updateMorphs();
    //! Apply a vertex morph
    void applyMorph(VertexBuffer* buffer, void* lockedMorphRange, const VertexBufferMorph& morph, float weight);
    //! Remove unnecessary animations after a load or network update
    void removeExtraAnimations(const std::set<StringHash>& animations);
    
    //! Skeleton
    Skeleton mSkeleton;
    //! Morph vertex buffers
    std::vector<SharedPtr<VertexBuffer> > mMorphVertexBuffers;
    //! Vertex morphs
    std::vector<ModelMorph> mMorphs;
    //! Animation states
    std::vector<AnimationState*> mAnimationStates;
    //! Skinning matrices
    std::vector<Matrix4x3> mSkinMatrices;
    //! Mapping of subgeometry bone indices, used if more bones than skinning shader can manage
    std::vector<std::vector<unsigned> > mGeometryBoneMappings;
    //! Subgeometry skinning matrices, used if more bones than skinning shader can manage
    std::vector<std::vector<Matrix4x3> > mGeometrySkinMatrices;
    //! Subgeometry skinning matrix pointers, if more bones than skinning shader can manage
    std::vector<std::vector<Matrix4x3*> > mGeometrySkinMatrixPtrs;
    //! The frame number animation LOD distance was last calculated on
    unsigned mAnimationLodFrameNumber;
    //! Animation LOD bias
    float mAnimationLodBias;
    //! Animation LOD timer
    float mAnimationLodTimer;
    //! Animation LOD distance, the minimum of all LOD view distances last frame
    float mAnimationLodDistance;
    //! Animation LOD distance factor when not visible
    float mInvisibleLodFactor;
    //! Local animation flag
    bool mLocalAnimation;
    //! Animation dirty flag
    bool mAnimationDirty;
    //! Animation order dirty flag
    bool mAnimationOrderDirty;
    //! Vertex morphs dirty flag
    bool mMorphsDirty;
};

#endif // RENDERER_ANIMATEDMODEL_H
