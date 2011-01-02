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

#ifndef RENDERER_VOLUMENODE_H
#define RENDERER_VOLUMENODE_H

#include "BoundingBox.h"
#include "Node.h"

class Camera;
class DebugRenderer;
class Octant;
class Ray;
class Renderer;
class RayOctreeQuery;
class View;

//! Information of the frame being rendered
struct FrameInfo
{
    //! Rendering pipeline frame number
    unsigned mFrameNumber;
    //! Time elapsed since last frame
    float mTimeStep;
    //! Camera being used
    Camera* mCamera;
};

//! Abstract base class for scene nodes that can be stored in an octree
class VolumeNode : public Node
{
    friend class Octant;
    friend class Octree;
    
public:
    //! Destruct. Remove from the octree
    virtual ~VolumeNode();
    
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
    
    //! Process renderer raycast
    virtual void processRayQuery(RayOctreeQuery& query, float initialDistance);
    //! Pre-octree update step
    virtual void updateNode(const FrameInfo& frame);
    //! Calculate distance for rendering
    virtual void updateDistance(const FrameInfo& frame);
    //! Override model and view transforms for rendering
    virtual void overrideTransforms(unsigned batchIndex, Camera& camera, const Matrix4x3** model, const Matrix4x3** view);
    //! Draw debug geometry
    virtual void drawDebugGeometry(DebugRenderer* debug);
    
    //! Set whether casts shadows
    void setCastShadows(bool enable);
    //! Set whether should be rendered as an occluder
    void setOccluder(bool enable);
    //! Set whether should be rendered
    void setVisible(bool visible);
    //! Set draw distance, 0.0 for unlimited
    void setDrawDistance(float distance);
    //! Set shadow rendering distance, 0.0 for unlimited
    void setShadowDistance(float distance);
    //! Set view bitmask. ANDed with the camera's view mask to see whether the node should be rendered in a specific view
    void setViewMask(unsigned mask);
    //! Set light bitmask. A geometry's mask is ANDed with the light's mask to see if the light has effect (forward rendering only)
    void setLightMask(unsigned mask);
    //! Calculate draw distance for a specific camera and a desired screen size (1.0 = whole screen)
    float calculateDrawDistance(const Camera& camera, float minScreenSize);
    
    //! Return whether casts shadows
    bool getCastShadows() const { return mCastShadows; }
    //! Return whether should be rendered as an occluder
    bool isOccluder() const { return mOccluder; }
    //! Return whether should be rendered
    bool isVisible() const { return mVisible; }
    //! Return draw distance
    float getDrawDistance() const { return mDrawDistance; }
    //! Return shadow rendering distance
    float getShadowDistance() const { return mShadowDistance; }
    //! Return view msk
    unsigned getViewMask() const { return mViewMask; }
    //! Return light mask
    unsigned getLightMask() const { return mLightMask; }
    //! Return world-space bounding box
    const BoundingBox& getWorldBoundingBox();
    
    //! Return current octree octant
    Octant* getOctant() const { return mOctant; }
    //! Set sorting value. Called by View
    void setSortValue(float value);
    //! Mark in view this frame. Called by View
    void markInView(unsigned frameNumber, View* view);
    //! Return distance from camera
    float getDistance() const { return mDistance; }
    //! Return sorting value
    float getSortValue() const { return mSortValue; }
    //! Return whether is in view this frame
    bool isInView(unsigned frameNumber) const;
    //! Return whether is visible in a specific view this frame
    bool isInView(unsigned frameNumber, View* view) const;
    
protected:
    //! Construct with node flags, initial octree pointer and name
    VolumeNode(unsigned flags, Octant* octant, const std::string& name);
    //! Transform has changed. Mark for octree re-insertion
    virtual void onMarkedDirty();
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox) = 0;
    
    //! Current octree octant
    Octant* mOctant;
    //! Cast shadows flag
    bool mCastShadows;
    //! Render as occluder flag
    bool mOccluder;
    //! Visible flag
    bool mVisible;
    //! Draw distance
    float mDrawDistance;
    //! Shadow rendering distance
    float mShadowDistance;
    //! View bitmask
    unsigned mViewMask;
    //! Light bitmask
    unsigned mLightMask;
    //! Current distance to camera
    float mDistance;
    //! Current sort value
    float mSortValue;
    //! Last visible frame number
    unsigned mViewFrameNumber;
    //! Last visible view
    View* mView;
    
private:
    //! World-space bounding box
    BoundingBox mWorldBoundingBox;
    //! World-space bounding box needs update flag
    bool mWorldBoundingBoxDirty;
};

#endif // RENDERER_VOLUMENODE_H
